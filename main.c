#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <time.h>
#include <ctype.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_mixer.h>
#include <SDL2/SDL_ttf.h>
#include <GL/gl.h>
#include "constant.h"
#include "randomtext.h"
#include "server.h"
#include "variable.h"
#include "processinput.h"
#include "button.h"
#include "graph.h"
// Here write functions which works differently in linux and windows
// Linux
#ifdef linux

#include <fcntl.h>
#include <linux/input.h>
#include <X11/XKBlib.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>


bool isCapsLockOn(){
    Display *display = XOpenDisplay(NULL);
    if (display == NULL){
        fprintf(stderr, "Error opening display\n");
        return false;
    }

    unsigned int state;
    XkbGetIndicatorState(display, XkbUseCoreKbd, &state);
    XCloseDisplay(display);

    return (state & 1) != 0;  // Caps Lock is bit 1
}

#elif _WIN32

#include <winsock2.h>
#include <Windows.h>
#include <ws2tcpip.h>

bool isCapsLockOn(){
    return (GetKeyState(VK_CAPITAL) & 0x0001) != 0;
}
#endif

bool isCapsLockOn();
bool initialize();
void process_inputStart();
void process_inputFinished();
void renderFinished();
void setupPractice();
void process_inputPractice();
void updatePractice();
void renderPractice();
bool setupMultiPlayer();
void process_inputMultiPlayer();
void updateMultiPlayer();
void renderMultiPlayer();
void destroy_window();
void renderMultipleLines(SDL_Renderer* renderer, TTF_Font* font, const char* text, SDL_Color color, int textX, int textY);



void wait(){
    int wait = FRAME_TARGET_TIME - (SDL_GetTicks() - last_frame_time);
    if(wait > 0 && wait <= FRAME_TARGET_TIME){
        SDL_Delay(wait);
    }
    last_frame_time = SDL_GetTicks();
}


SDL_Window *usernameWin = NULL;
SDL_Renderer *usernameRenderer = NULL;
void initializeUsernameWindow(){

    usernameWin = SDL_CreateWindow(NULL, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 900, 400, SDL_WINDOW_SHOWN);
    if (usernameWin == NULL) {
        fprintf(stderr, "SDL_CreateWindow Error: %s\n", SDL_GetError());
        SDL_Quit();
    }

    usernameRenderer = SDL_CreateRenderer(usernameWin, -1, SDL_RENDERER_ACCELERATED);
    if(!usernameRenderer){
        fprintf(stderr, "Error creating SDL Renderer. \n");
    }
    loadImage(usernameRenderer, &Username, "username.jpg");
}


void gameStartWindow(){
    
    if (keyDown || mouseDown){
        windowState[0] = 0;
        if(usernameSaved)
            windowState[2] = 1;
        else{
            initializeUsernameWindow();
            username_index = 0;
            username[0] = '\0';
            windowState[1] = 1;
        }
    }
    wait();
    SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_BLEND);
    SDL_RenderCopy(renderer, preMenuImageTexture, NULL, NULL);
    SDL_RenderPresent(renderer);
}


void usernameWindow(){
    bool maxLim = 0, minLim = 0;
    
    if(keyDown){
        if(pressedKey == SDLK_RETURN){
            if(username_index){
                printf("%d", username_index);
                FILE *cache = fopen("cache.txt", "w");
                fprintf(cache,"%s",username);
                fclose(cache);
                windowState[1] = 0;
                windowState[2] = 1;
                
            }else{
                minLim = 1;
            }
        }else if(pressedKey == SDLK_BACKSPACE){
            if(username_index > 0){
                username_index--;
                username[username_index] = '\0';
            }
            maxLim = 0;
        }else if(pressedKey >= 32 && pressedKey <= 126){
            if(username_index < 10){
                username[username_index++] = pressedKey;
                username[username_index] = '\0';
            }else{
                maxLim = 1;
                minLim = 0;
            }
        }
    }else if(mouseDown){
        if(mouseInBox(yesBox)){
            if(username_index > 0){
                printf("%d", username_index);
                FILE *cache = fopen("cache.txt", "w");
                fprintf(cache,"%s",username);
                fclose(cache);
                user_name = 0;
                windowState[2] = 1;
                windowState[1] = 0;
                
            }else{
                minLim = 1;
            }
        }else if(mouseInBox(cancelBox)){
            user_name = 0;
            windowState[0] = 1;
            windowState[1] = 0;
            username[0] = '\0';
        }
    }
    wait();

    
    SDL_RenderCopy(usernameRenderer, Username, NULL, NULL);

    
    renderText(usernameRenderer, dejavu, username, Cyan, typingBox.x + 10, typingBox.y + 5);
    
    if(maxLim) renderText(usernameRenderer, dejavu, "Maximum limit reached! Please press Enter to proceed", Red, typingBox.x + 5, typingBox.y + typingBox.h + 5);
    if(minLim) renderText(usernameRenderer, dejavu, "Username too short!", Red, typingBox.x + 5, typingBox.y + typingBox.h + 5);

    SDL_RenderPresent(usernameRenderer);
}

bool zoomInLeft = 0, zoomInRight = 0;

Button *musicOnButton, *musicOffButton;


void call(){
    if(musicOn){
        Mix_HaltMusic();
        resetState(musicOnButton);
    }else{
        Mix_PlayMusic(music, -1);
        resetState(musicOffButton);
    }
    musicOn ^= 1;
}

void selectWindow(){
    
    if(mouseDown){
        if (mouseInBox(practiceBox)){
            windowState[2] = 0;
            windowState[4] = 1; //practice
        }else if (mouseInBox(multiplayerBox)){
            windowState[2] = 0;
            windowState[5] = 1; //multiplayer
        }else if(mouseInBox(profileBox)){
            windowState[1] = 1;
            windowState[2] = 0;
            username[0] = '\0';
            username_index = 0;
            usernameSaved = 0;
            initializeUsernameWindow();
        }
    }else if(keyDown){
        if(pressedKey == SDLK_LEFT){
            zoomInLeft = 1;
            zoomInRight = 0;
        }else if(pressedKey == SDLK_RIGHT){
            zoomInLeft = 0;
            zoomInRight = 1;
        }else if(pressedKey == SDLK_RETURN){
            if(zoomInLeft){
                windowState[2] = 0;
                windowState[4] = 1; //practice
                zoomInLeft = 0;
            }else if(zoomInRight){
                windowState[2] = 0;
                windowState[5] = 1; //multiplayer
                zoomInRight = 0;
            }
        }
    }
    wait();
    
    SDL_RenderCopy(renderer, Menu_selector, NULL, NULL);


    SDL_Rect box1 = {practiceBox.x - 10, practiceBox.y - 10, practiceBox.w + 20, practiceBox.h + 20};
    SDL_Rect box2 = {multiplayerBox.x - 10, multiplayerBox.y - 10, multiplayerBox.w + 20, multiplayerBox.h + 20};
    if(zoomInLeft){
        SDL_RenderCopy(renderer, practiceTexture, NULL, &box1);
    }else{
        SDL_RenderCopy(renderer, practiceTexture, NULL, &practiceBox);
    }

    if(zoomInRight){
        SDL_RenderCopy(renderer, multiplayerTexture, NULL, &box2);
    }else{
        SDL_RenderCopy(renderer, multiplayerTexture, NULL, &multiplayerBox);
    }

    if(musicOn){
        updateButton(musicOnButton);
        renderButton(musicOnButton);
    }else{
        updateButton(musicOffButton);
        renderButton(musicOffButton);
    }
    SDL_RenderCopy(renderer, profileTexture, NULL, &profileBox);
    renderText(renderer, dejavu, username, Aqua,  1550 + 60 + 5, 50);

    SDL_RenderPresent(renderer);
}

void practiceOptionWindow(){
    

}

int main(int argn, char *argv[]){
    game_is_running = initialize();
    FILE *cache = fopen("cache.txt","rb");
    if(cache){
        usernameSaved = 1;
        char tmp[100];
        fscanf(cache,"%s",tmp);
        strcpy(username, tmp);
        fclose(cache);
    }
    
    windowState[0] = 1;
    Mix_AllocateChannels(2);
    Mix_PlayMusic(music, -1);
    SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_BLEND);
    while(game_is_running){
        getMouseAndKeyboardState();
        if(windowState[0]){
            gameStartWindow();
        }else if(windowState[1]){
            // windowState[2] = 1;
            // continue;
            usernameWindow();
            if(!windowState[1]){
                SDL_DestroyRenderer(usernameRenderer);
                SDL_DestroyWindow(usernameWin);
            }
        }else if(windowState[2]){
            selectWindow();
            if(windowState[4]) setupPractice();
            if(windowState[5]) {
                if(!setupMultiPlayer()){
                    windowState[5] = 0;
                    windowState[2] = 1;
                }
                // else{
                //     char count[10];
                //     for(int i = 10; i >= 1; i--){
                        
                //         sprintf(count,"%d",i);
                //         SDL_RenderCopy(renderer, spaceImageTexture, NULL, NULL);
                //         renderText(renderer, dejavu, count, Black, 500, 500);
                //         SDL_RenderPresent(renderer);
                //         SDL_Delay(1000);
                //     }
                //     start = 1;
                //     last_frame_time = SDL_GetTicks();
                // }
            }
        }else if(windowState[3]){
            
        }else if(windowState[4]){
            process_inputPractice();
            updatePractice();
            renderPractice();
        }else if(windowState[5]){
            if(start){
                process_inputMultiPlayer();
                updateMultiPlayer();
                renderMultiPlayer();
            }else{
                if(mouseDown){
                    if (mouseX >= startTypingBox.x && mouseX <= (startTypingBox.x + startTypingBox.width) && mouseY >= startTypingBox.y && mouseY <= (startTypingBox.y + startTypingBox.height)) {
                        start = 1;
                        startTime = SDL_GetTicks();
                    }
                }
                wait();
                renderStart(&spaceImageTexture);
            }
            
        }
    }
    destroy_window();
    close_socket();
    
    return 0;
}


int correctTextx, correctTexty;

void renderMultipleLines(SDL_Renderer* renderer, TTF_Font* font, const char* text, SDL_Color color, int textX, int textY) {
    char* textCopy = strdup(text);
    char* line = strtok((char*)textCopy, "\n");
    int lineHeight = 1.5 * TTF_FontHeight(font);
    int x = textX, y = textY;
    bool flag = 0;
    while (line != NULL) {
        SDL_Surface* surface = TTF_RenderText_Solid(font, line, color);

        TTF_SizeText(font, line, &correctTextx, &correctTexty);
        correctTexty = y; correctTextx += textPosx;
        if (surface) {
            SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, surface);
            if (texture) {
                // Dimensions of the text surface
                int textWidth = surface->w;
                int textHeight = surface->h;
                if(flag){
                    x = textPosx;
                }
                flag = 1;
                SDL_Rect textRect = { x, y, textWidth, textHeight };

                SDL_RenderCopy(renderer, texture, NULL, &textRect);

                y += lineHeight;

                SDL_DestroyTexture(texture);
            } else {
                fprintf(stderr,"Failed to create texture from surface: %s\n", SDL_GetError());
            }

            SDL_FreeSurface(surface);
        } else {
            fprintf(stderr,"Failed to render text: %s\n", TTF_GetError());
        }
        // Move to the next line
        line = strtok(NULL, "\n");
    }
    char last_char = text[strlen(text)-1];
    if(last_char == '\n'){
        correctTextx = textPosx, correctTexty += lineHeight;
    }
}

bool initializeWindow(){
    if(SDL_Init(SDL_INIT_EVERYTHING) != 0){
        fprintf(stderr, "Error initializing SDL.\n");
        return false;
    }
    window = SDL_CreateWindow(NULL, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, WIDTH, HEIGHT, SDL_WINDOW_SHOWN);
    if(!window){
        fprintf(stderr, "Error creating SDL window. \n");
        return false;
    }
    return true;
}

bool initializeRenderer(){
    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    if(!renderer){
        fprintf(stderr, "Error creating SDL Renderer. \n");
        return false;
    }
    return true;
}

bool initializeFont(){
    TTF_Init();
    comic = TTF_OpenFont(Font_Style[0], 35);
    dejavu = TTF_OpenFont(Font_Style[1], 30);
    
    comicLarge = TTF_OpenFont(Font_Style[0], 45);
    for(char i = 0; i < 127; i++)
        fontWidth[i] = getWidth(i);
    fontHeight = TTF_FontHeight(comic);



    if(!comic || !dejavu){
        fprintf(stderr, "Error: %s\n", TTF_GetError());
        return false;
    }
    capsOn = isCapsLockOn();
    return true;
}

bool initializeMusic(){
    // initializes SDL_mixer with a 44.1 kHz sample rate, default audio format, stereo channels, and a 2048-byte chunk size.
    if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0){
        fprintf(stderr,"SDL_mixer could not initialize! SDL_mixer Error: %s\n", Mix_GetError());
        return false;
    }

    music = Mix_LoadMUS("Luke-Bergs-Bliss.mp3");
    if (!music){
        fprintf(stderr,"Failed to load music! SDL_mixer Error: %s\n", Mix_GetError());
        return false;
    }

    sfx = Mix_LoadWAV("click.wav");
    if (!sfx){
        fprintf(stderr,"Failed to load sfx! SDL_mixer Error: %s\n", Mix_GetError());
        return false;
    }
    return true;
}

bool initializeTexture(){
    loadImage(renderer, &practiceBackgroundTexture, Background[0]);

    loadImage(renderer, &preMenuImageTexture, "preMenu.png");

    loadImage(renderer, &Menu_selector, "MENU/menu_select.png");

    //loadImage(renderer, &Username, "username.jpg");

    //loadImage(renderer, &musicOnTexture, "sound.png");

    //loadImage(renderer, &musicOffTexture, "mute.png");

    //loadImage(renderer, &backTexture, "back.png");

    //loadImage(renderer, &retryTexture, Images[5]);

    loadImage(renderer, &profileTexture, Images[4]);  

    loadImage(renderer, &spaceImageTexture, Images[1]);

    loadImage(renderer, &player1ImageTexture, Images[2]);
    
    loadImage(renderer, &player2ImageTexture, Images[3]);

    loadImage(renderer, &practiceTexture, "practice.png");

    loadImage(renderer, &multiplayerTexture, "multiplayer.png");

    return 1;
}

Button *backButton;
void backButtonFun(){
    windowState[4] = 0;
    windowState[2] = 1;
}

Button *retryButton;

void retryButtonFun(){
    setupPractice();
}
bool initialize(){
    bool state = 1;
    state &= initializeWindow();
    state &= initializeRenderer();
    state &= initializeFont();
    state &= initializeTexture();
    state &= initializeMusic(); 
    musicOnButton = createButton(renderer, "sound.png", "sound1.png", "sound2.png", musicBox, 10, &call);
    musicOffButton = createButton(renderer, "mute.png", "mute1.png", "mute2.png", musicBox, 10, &call);
    backButton = createButton(renderer, "back.png", "back.png", "back.png", backBox, 6, &backButtonFun);
    retryButton = createButton(renderer, "retry.png", "retry.png", "retry.png", retryBox, 6, retryButtonFun);
    return state;
}

void process_inputStart(){
    
    if(mouseDown){
        if (mouseX >= startTypingBox.x && mouseX <= (startTypingBox.x + startTypingBox.width) && mouseY >= startTypingBox.y && mouseY <= (startTypingBox.y + startTypingBox.height)) {
            start = 1;
            startTime = SDL_GetTicks();
        }
    }
}

void renderStart(SDL_Texture** texture){
    SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_BLEND);

    SDL_RenderCopy(renderer, *texture, NULL, NULL); // Render the entire background

    SDL_Rect rectangle = {
        startTypingBox.x,
        startTypingBox.y,
        startTypingBox.width,
        startTypingBox.height
    };
    SDL_SetRenderDrawColor(renderer, startTypingBox.color.r, startTypingBox.color.g, startTypingBox.color.b, 130);
    SDL_RenderFillRect(renderer, &rectangle);

    char text[] = "START TYPING";
    renderText(renderer, dejavu, text, White, startTypingBox.x + 15, startTypingBox.y + 10);

    SDL_RenderPresent(renderer);
}

void process_inputFinished(){
    
    if (mouseX >= playAgainBox.x && mouseX <= (playAgainBox.x + playAgainBox.width) && mouseY >= playAgainBox.y && mouseY <= (playAgainBox.y + playAgainBox.height)) {
        playAgain = 0;
        windowState[2] = 1;
        finished = 0;
    }
}

void renderFinished(){
    SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_BLEND);

    SDL_RenderCopy(renderer, practiceBackgroundTexture, NULL, NULL); // Render the entire background

    
    // Render rectangle
    SDL_Rect rectangle = {
        playAgainBox.x,
        playAgainBox.y,
        playAgainBox.width,
        playAgainBox.height
    };
    SDL_SetRenderDrawColor(renderer, playAgainBox.color.r, playAgainBox.color.g, playAgainBox.color.b, 130);
    SDL_RenderFillRect(renderer, &rectangle);

    char text[] = "PLAY AGAIN";

    renderText(renderer, dejavu, text, White, startTypingBox.x + 15, startTypingBox.y + 10);

    SDL_RenderPresent(renderer);
}

// Use Comic.TTF for perfect character width


SDL_Point points[10000];
int pointGap = 5000; // 5s
int pointCount = 0;
int nextPointX = 0;

int CPM = 0;
int totalTypedChar = 0, correctTypedChar = 0;
int accuracy = 0;

void setupPractice(){
    correctTextx = textPosx, correctTexty = textPosy;
    currentText = generate_random_text();
    maxTextSize = strlen(currentText);
    currentCharIndex = 0;

    charCount = 0;
    for(int i = 0; i < maxTextSize; i++)
        if(currentText[i] != '\n') charCount++;

    //if(musicOn)
    //    Mix_PlayMusic(music, -1);
    
    curWidth = fontWidth[currentText[0]];
    rec.x = textPosx;
    rec.y = textPosy;
    rec.width = curWidth;
    rec.height = fontHeight;
    rec.color = White;
    start = 0;
    notMatch = 0;
    match = 0;
    wordCount = 0;
    finished = 0;
    pointCount = 0, nextPointX = 0;
    totalTypedChar = 0, correctTypedChar = 0;

}

void addPoint(currentPointX){
    
    if(currentPointX > nextPointX){
        points[pointCount].x = currentPointX;
        points[pointCount].y = WPM;
        pointCount++;
        nextPointX = currentPointX + pointGap;
    }
}

void process_inputPractice(){
    
    if(keyDown && !start){
        start = 1;
        startTime = SDL_GetTicks();
        addPoint(startTime);
    }
    match = false;

    if(pressedKey == SDLK_BACKSPACE){
        notMatch = false;
        return;
    }
    if(!notMatch && keyDown && pressedKey >= 32 && pressedKey <= 126){
        totalTypedChar++;
        if(pressedKey == currentText[currentCharIndex]) {
            correctTypedChar++;
            currentCharIndex++;
            match = true;
        }else{
            notMatch = true;
        }
    }  
}
SDL_Point center = {500, 800};
void updatePractice(){
    wait();
    
    updateButton(retryButton);
    updateButton(backButton);
    
    if(match){
        charCount++;
        if(pressedKey == ' ')
            wordCount++;
        rec.x += curWidth;
        if(currentText[currentCharIndex] == '\n'){
            rec.y += 1.5*fontHeight;
            rec.x = textPosx;
            currentCharIndex++;
        }
        curWidth = fontWidth[currentText[currentCharIndex]];


        if(currentCharIndex == maxTextSize){
            wordCount++;
            finished = 1;
            endTime = SDL_GetTicks();
            practice = 0;
            notMatch = 0;
            printf("%d\n", pointCount);

        }
        
    }
    int currentTime = SDL_GetTicks();
    if(!finished && start){
        addPoint(currentTime);
    }

    double time = currentTime - startTime + 1;
    time = time / (1000.0*60.0);
    if(!finished){
        WPM = start? ((double) wordCount / time) : 0;

        CPM = start? ((double) charCount / time) : 0;

        accuracy = totalTypedChar? ((100 * correctTypedChar )/ totalTypedChar) : 100;

    }

    rec.color = notMatch? Red:White;
    rec.width = curWidth;
}

void renderPerfomance(){
    char stats[20];
        
    sprintf(stats, "     WPM    :    %d",WPM);
    renderText(renderer, comicLarge, stats, Orange, 700, 100);

    sprintf(stats, "     CPM    :    %d",CPM);
    renderText(renderer, comicLarge, stats, Orange, 700, 100 + fontHeight);

    sprintf(stats, "Accuracy    :    %d%%",accuracy);
    renderText(renderer, comicLarge, stats, Orange, 700, 100 + fontHeight*2);

    drawGraph(renderer, points, pointCount, Orange, center, 800, 400);
}

void renderPractice() {
    //This allows the renderer to blend colors with the background based on the alpha value.
    SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_BLEND);

    SDL_RenderCopy(renderer, practiceBackgroundTexture, NULL, NULL); // Render the entire background

    renderButton(retryButton);
    renderButton(backButton);

    if(!finished){
        char buff[10];
        sprintf(buff,"%d",WPM);
        renderText(renderer, dejavu, buff, Cyan, 900, 60);

        char upper[400], lower[400];
        
        strncpy(upper, currentText, currentCharIndex);
        upper[currentCharIndex]='\0';
        renderMultipleLines(renderer, comic, upper, Green, textPosx, textPosy);
        if(!currentCharIndex){
            correctTextx = textPosx, correctTexty = textPosy;
        }
        SDL_Rect rectangle = {correctTextx, correctTexty, rec.width, rec.height};
        SDL_SetRenderDrawColor(renderer, rec.color.r, rec.color.g, rec.color.b, 130);
        SDL_RenderFillRect(renderer, &rectangle);
        
        strcpy(lower, currentText + currentCharIndex);
        renderMultipleLines(renderer, comic, lower , Yellow, correctTextx, correctTexty);
        retryBox.h = 70, retryBox.w = 70;
    }else{
        renderPerfomance();
    }

    
    SDL_RenderPresent(renderer);
}

int mulTexty = 500;

bool setupMultiPlayer(){
    bool status = serverConnect();

    if(!status) return 0;

    start = 0;
    currentText = receiveStr();
    maxTextSize = strlen(currentText);
    currentCharIndex = 0;

    capsOn = isCapsLockOn();

    //
    player1x = 20, player1y = 100;
    player1Height = 150, player1Width = 200;
    player1mx = 20, player1my = 100;

    player2x = 20, player2y = 250;
    player2Height = 100, player2Width = 220;
    player2mx = 20, player2my = 250;
    int charCount = 0;
    for(int i = 0; i < maxTextSize; i++)
        if(currentText[i] != '\n') charCount++;

    movementPerMatch = ((float)WIDTH - player1Width - 20) / charCount;
    //
    match = 0, notMatch = 0;
    curWidth = fontWidth[currentText[0]];

    rec.x = textPosx;
    rec.y = mulTexty;
    rec.width = curWidth;
    rec.height = fontHeight;
    rec.color = White;
    return 1;
}

void process_inputMultiPlayer(){
    
    match = false;

    if(pressedKey == SDLK_BACKSPACE){
        notMatch = false;
        return;
    }
    if(!notMatch && keyDown && pressedKey >= 32 && pressedKey <= 126){
        totalTypedChar++;
        if(pressedKey == currentText[currentCharIndex]) {
            correctTypedChar++;
            currentCharIndex++;
            match = true;
        }else{
            notMatch = true;
        }
    }  
}

void updateMultiPlayer(){
    int wait = FRAME_TARGET_TIME - (SDL_GetTicks() - last_frame_time);
    if(wait > 0 && wait <= FRAME_TARGET_TIME){
        SDL_Delay(wait);
    }

    float delta_time = (SDL_GetTicks() - last_frame_time) / 1000.0f;
    last_frame_time = SDL_GetTicks();

    sendToServer(player1mx);
    int tmp = receiveFromServer();
    if(tmp != 0) player2mx = tmp;

    if(player1mx>player1x){
        player1x += delta_time * 80.0;  // Adjust this as per current typing speed
    }

    if(player2mx>player2x){
        player2x += delta_time * 80.0;  // Adjust this as per current typing speed
    }

    if(back){
        notMatch = 0;
        rec.color = White;
        back = 0;
    }
    if(match){
        rec.x += curWidth;
        if(currentText[currentCharIndex] == '\n'){
            rec.y += 1.5*fontHeight;
            rec.x = textPosx;
            currentCharIndex++;
        }
        curWidth = fontWidth[currentText[currentCharIndex]];
        player1mx += movementPerMatch;

        if(currentCharIndex == maxTextSize){
            finished = 1;
            endTime = SDL_GetTicks();
            practice = 0;
        }
    }
    rec.color = notMatch? Red:White;
    rec.width = curWidth;
}

void renderMultiPlayer(){
    SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_BLEND);

    SDL_RenderCopy(renderer, spaceImageTexture, NULL, NULL);

    SDL_Rect player1Rect = {player1x, player1y, player1Width, player1Height};
    SDL_RenderCopy(renderer, player1ImageTexture, NULL, &player1Rect);

    SDL_Rect player2Rect = {player2x, player2y, player2Width, player2Height};
    SDL_RenderCopy(renderer, player2ImageTexture, NULL, &player2Rect);


    char upper[400], lower[400];
    
    strncpy(upper, currentText, currentCharIndex);
    upper[currentCharIndex]='\0';
    renderMultipleLines(renderer, comic, upper, Green, textPosx, mulTexty);
    if(!currentCharIndex){
        correctTextx = textPosx, correctTexty = mulTexty;
    }

    SDL_Rect rectangle = {rec.x, rec.y, rec.width, rec.height};
    SDL_SetRenderDrawColor(renderer, rec.color.r, rec.color.g, rec.color.b, 130);
    SDL_RenderFillRect(renderer, &rectangle);
    
    strcpy(lower, currentText + currentCharIndex);
    renderMultipleLines(renderer, comic, lower , Orange, correctTextx, correctTexty);

    SDL_RenderPresent(renderer);
}

void destroy_window(){

    destroyButton(musicOffButton);
    destroyButton(musicOnButton);
    destroyButton(retryButton);
    destroyButton(backButton);

    SDL_DestroyTexture(practiceBackgroundTexture);
    SDL_DestroyTexture(spaceImageTexture);
    SDL_DestroyTexture(player1ImageTexture);
    SDL_DestroyTexture(player2ImageTexture);

    TTF_CloseFont(comic);
    TTF_CloseFont(dejavu);
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    TTF_Quit();
    SDL_Quit();
}
