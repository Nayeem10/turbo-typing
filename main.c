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
void setupPractice();
void process_inputPractice();
void updatePractice();
void renderPractice();
void cleanUpPractice();
bool setupMultiPlayer();
void process_inputMultiPlayer();
void updateMultiPlayer();
void renderMultiPlayer();
void cleanUpMultiplayer();
void destroy_window();
void renderMultipleLines(SDL_Renderer* renderer, TTF_Font* font, const char* text, SDL_Color color, int textX, int textY);

Button *musicOnButton, *musicOffButton;
void musicButtonHandler(){
    if(musicOn){
        Mix_HaltMusic();
        resetState(musicOnButton);
    }else{
        Mix_PlayMusic(music, -1);
        resetState(musicOffButton);
    }
    musicOn ^= 1;
}



Button *retryButton;
void retryButtonHandler(){
    setupPractice();
}


int difficulty = 1, randomTextSize = 100;
Button *easyButton;
void easyButtonHandler(){
    difficulty = 0;
    randomTextSize = 100;
    setupPractice();
    windowState[3] = 0;
    windowState[4] = 1;
}

Button *mediumButton;
void mediumButtonHandler(){
    difficulty = 1;
    randomTextSize = 200;
    setupPractice();
    windowState[3] = 0;
    windowState[4] = 1;
}

Button *hardButton;
void hardButtonHandler(){
    difficulty = 2;
    randomTextSize = 300;
    setupPractice();
    windowState[3] = 0;
    windowState[4] = 1;
}

Button *backButton;
void backButtonHandler(){
    if(windowState[4]){
        windowState[4] = 0;
        windowState[3] = 1;
    }else if(windowState[5]){
        windowState[5] = 0;
        windowState[2] = 1;
        cleanUpMultiplayer();
    }else if(windowState[3]){
        windowState[3] = 0;
        windowState[2] = 1;
        resetState(easyButton);
        resetState(mediumButton);
        resetState(mediumButton);
    }
}

void wait(){
    int wait = FRAME_TARGET_TIME - (SDL_GetTicks() - last_frame_time);
    if(wait > 0 && wait <= FRAME_TARGET_TIME){
        SDL_Delay(wait);
    }
    last_frame_time = SDL_GetTicks();
}

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
    loadImage(usernameRenderer, &usernameTexture, "Images/username.jpg");
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
    SDL_RenderCopy(renderer, gameStartTexture, NULL, NULL);
    SDL_RenderPresent(renderer);
}

bool maxLim = 0, minLim = 0;
void usernameWindow(){
    if (event.type == SDL_WINDOWEVENT && event.window.event == SDL_WINDOWEVENT_CLOSE) {
        if (event.window.windowID == SDL_GetWindowID(usernameWin)) {
            maxLim = 0, minLim = 0;
            windowState[0] = 1;
            windowState[1] = 0;
            username[0] = '\0';
        }
    }

    if(keyDown){
        if(pressedKey == SDLK_RETURN){
            if(username_index){
                FILE *cache = fopen("cache.txt", "w");
                fprintf(cache,"%s",username);
                fclose(cache);
                windowState[1] = 0;
                windowState[2] = 1;
                maxLim = 0, minLim = 0;
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
            minLim = 0;
            if(username_index < 10){
                username[username_index++] = pressedKey;
                username[username_index] = '\0';
            }else{
                maxLim = 1;
            }
        }
    }else if(mouseDown){
        if(mouseInBox(yesBox)){
            if(username_index > 0){
                printf("%d", username_index);
                FILE *cache = fopen("cache.txt", "w");
                fprintf(cache,"%s",username);
                fclose(cache);
                windowState[2] = 1;
                windowState[1] = 0;
                
            }else{
                minLim = 1;
            }
        }else if(mouseInBox(cancelBox)){
            maxLim = 0; minLim = 0;
            windowState[0] = 1;
            windowState[1] = 0;
            username[0] = '\0';
        }
    }
    wait();

    SDL_RenderCopy(usernameRenderer, usernameTexture, NULL, NULL);
    
    renderText(usernameRenderer, dejavu, username, Cyan, typingBox.x + 10, typingBox.y + 5);
    
    if(maxLim) renderText(usernameRenderer, dejavu, "Maximum limit reached! Please press Enter to proceed", Red, typingBox.x - 60, typingBox.y + typingBox.h + 5);
    if(minLim) renderText(usernameRenderer, dejavu, "usernameTexture too short!", Red, typingBox.x + 5, typingBox.y + typingBox.h + 5);

    SDL_RenderPresent(usernameRenderer);
}

bool zoomInLeft = 0, zoomInRight = 0;

void selectWindow(){
    
    if(mouseDown){
        if (mouseInBox(practiceBox)){
            windowState[2] = 0;
            windowState[3] = 1; //practice
        }else if (mouseInBox(multiplayerBox)){
            windowState[2] = 0;
            windowState[5] = 1; //multiplayer
        }else if(mouseInBox(profileBox)){
            windowState[1] = 1;
            windowState[2] = 0;
            //username[0] = '\0';
            username_index = strlen(username);
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
                windowState[3] = 1; //practice
                zoomInLeft = 0;
            }else if(zoomInRight){
                windowState[2] = 0;
                windowState[5] = 1; //multiplayer
                zoomInRight = 0;
            }
        }
    }
    wait();
    
    SDL_RenderCopy(renderer, selectorTexture, NULL, NULL);


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
    wait();

    updateButton(easyButton);
    updateButton(mediumButton);
    updateButton(hardButton);
    updateButton(backButton);

    SDL_RenderCopy(renderer, selectorTexture, NULL, NULL);
    renderButton(easyButton);
    renderButton(mediumButton);
    renderButton(hardButton);
    renderButton(backButton);
    SDL_RenderPresent(renderer);
}

void countdown(int start) {
    for (int i = start; i >= 0; i--) {
        char sec[100];
        sprintf(sec, "%d", i);
        SDL_RenderCopy(renderer, boardTexture, NULL, NULL);
        renderText(renderer, comicLarge, sec, Orange, 800, 400);
        SDL_RenderPresent(renderer);
        sleep(1);
    }
    last_frame_time = SDL_GetTicks();
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
            usernameWindow();
            if(!windowState[1]){
                SDL_DestroyRenderer(usernameRenderer);
                SDL_DestroyWindow(usernameWin);
            }
        }else if(windowState[2]){
            selectWindow();
            //if(windowState[4]) setupPractice();
            if(windowState[5]) {
                if(!setupMultiPlayer()){
                    windowState[5] = 0;
                    windowState[2] = 1;
                }
            }
        }else if(windowState[3]){
            practiceOptionWindow();
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
                countdown(3);
                start = 1;
                startTime = SDL_GetTicks();
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
        fontWidth[(int)i] = getWidth(i);
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
    loadImage(renderer, &boardTexture, "Images/board.jpg");

    loadImage(renderer, &gameStartTexture, "Images/gamestart.png");

    loadImage(renderer, &selectorTexture, "Images/selector.jpg"); 

    loadImage(renderer, &player1ImageTexture, "Images/player1.png");
    
    loadImage(renderer, &player2ImageTexture, "Images/player2.png");

    loadImage(renderer, &profileTexture, "Images/profile.png"); 

    loadImage(renderer, &practiceTexture, "Images/practice.png");

    loadImage(renderer, &multiplayerTexture, "Images/multiplayer.png");

    loadImage(renderer, &winnerTexture, "Images/winner.png");

    loadImage(renderer, &loserTexture, "Images/loser.png");

    return 1;
}

bool initialize(){
    bool state = 1;
    state &= initializeWindow();
    state &= initializeRenderer();
    state &= initializeFont();
    state &= initializeTexture();
    state &= initializeMusic(); 

    musicOnButton = createButton(renderer, "Images/sound.png", "Images/sound1.png", "Images/sound2.png", musicBox, 10, &musicButtonHandler);
    musicOffButton = createButton(renderer, "Images/mute.png", "Images/mute1.png", "Images/mute2.png", musicBox, 10, &musicButtonHandler);
    backButton = createButton(renderer, "Images/back.png", "Images/back1.png", "Images/back2.png", backBox, 6, &backButtonHandler);
    retryButton = createButton(renderer, "Images/retry.png", "Images/retry1.png", "Images/retry1.png", retryBox, 6, &retryButtonHandler);
    easyButton = createButton(renderer, "Images/easy.png", "Images/easy1.png", "Images/easy1.png", easyBox, 10, &easyButtonHandler);
    mediumButton = createButton(renderer, "Images/medium.png", "Images/medium1.png", "Images/medium1.png", mediumBox, 10, &mediumButtonHandler);
    hardButton = createButton(renderer, "Images/hard.png", "Images/hard1.png", "Images/hard1.png", hardBox, 10, &hardButtonHandler);
    
    return state;
}

int cursorTimer = 0;
bool cursorVisible = 1;

void renderTextAndCursor(int X, int Y){
    if (SDL_GetTicks() - cursorTimer >= 400) {
        cursorTimer = SDL_GetTicks();
        //cursorVisible ^= 1;
    }

    char upper[400], lower[400];
        
    strncpy(upper, currentText, currentCharIndex);
    upper[currentCharIndex]='\0';
    renderMultipleLines(renderer, comic, upper, Green, X, Y);
    if(!currentCharIndex){
        correctTextx = X, correctTexty = Y;
    }

    if(cursorVisible){
        SDL_Rect rectangle = {correctTextx, correctTexty, rec.width, rec.height};
        SDL_SetRenderDrawColor(renderer, rec.color.r, rec.color.g, rec.color.b, 130);
        SDL_RenderFillRect(renderer, &rectangle);
    }

    strcpy(lower, currentText + currentCharIndex);
    renderMultipleLines(renderer, comic, lower , Yellow, correctTextx, correctTexty);
}

void renderPerfomance(){
    char stats[20];
        
    sprintf(stats, "     WPM    :    %d",WPM);
    renderText(renderer, comicLarge, stats, Orange, 200, 400);

    sprintf(stats, "     CPM    :    %d",CPM);
    renderText(renderer, comicLarge, stats, Orange, 200, 400 + fontHeight);

    sprintf(stats, "Accuracy    :    %d%%",accuracy);
    renderText(renderer, comicLarge, stats, Orange, 200, 400 + fontHeight*2);

    drawGraph(renderer, points, pointCount, Orange, center, 800, 400);

    if(windowState[5]){
        
        if(win) SDL_RenderCopy(renderer, winnerTexture, NULL, &winnerBox);
        else if(loss) SDL_RenderCopy(renderer, loserTexture, NULL, &loserBox);
        else renderText(renderer, comicLarge, "DRAW!!", Orange, 1000, 300);
    }
}

void calculatePerformance(){
    int currentTime = SDL_GetTicks();
    double time = currentTime - startTime + 1;
    time = time / (1000.0*60.0);
    WPM = start? ((double) wordCount / time) : 0;
    CPM = start? ((double) charCount / time) : 0;
    accuracy = totalTypedChar? ((100 * correctTypedChar )/ totalTypedChar) : 100;
}

void addPoint(){
    int currentPointX = SDL_GetTicks();
    if(currentPointX > nextPointX){
        points[pointCount].x = currentPointX;
        points[pointCount].y = WPM;
        pointCount++;
        nextPointX = currentPointX + pointGap;
    }
}


void setupPractice(){
    cleanUpPractice();
    correctTextx = textPosx, correctTexty = textPosy;
    currentText = generate_random_text(difficulty, randomTextSize);
    maxTextSize = strlen(currentText);
    currentCharIndex = 0;

    charCount = 0;
    for(int i = 0; i < maxTextSize; i++)
        if(currentText[i] != '\n') charCount++;
    
    rec.x = textPosx, rec.y = textPosy, rec.width = fontWidth[(int)currentText[0]], rec.height = fontHeight, rec.color = White;
    start = 0, finished = 0;
    notMatch = 0, match = 0;
    WPM = 0;
    wordCount = 0;
    pointCount = 0, nextPointX = 0;
    totalTypedChar = 0, correctTypedChar = 0;
}

void process_inputPractice(){
    if(keyDown && !start){
        start = 1;
        startTime = SDL_GetTicks();
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

void updatePractice(){
    wait();
    
    updateButton(retryButton);
    updateButton(backButton);
    
    if(match){
        charCount++;
        if(pressedKey == ' '){
            wordCount++;
        }

        if(currentText[currentCharIndex] == '\n'){
            rec.y += 1.5*fontHeight;
            rec.x = textPosx;
            currentCharIndex++;
        }

        if(currentCharIndex == maxTextSize){
            wordCount++;
            cleanUpPractice();
        }
    }
    
    if(!finished && start){
        calculatePerformance();
        addPoint();
    }

    rec.color = notMatch? Red:White;
    rec.width = fontWidth[(int) currentText[currentCharIndex]];
}

void renderPractice() {
    SDL_RenderCopy(renderer, boardTexture, NULL, NULL);

    renderButton(retryButton);
    renderButton(backButton);

    if(!finished){
        char buff[10];
        sprintf(buff,"%d",WPM);
        renderText(renderer, dejavu, buff, Cyan, 900, 60);
        renderTextAndCursor(textPosx, textPosy);
    }else{
        renderPerfomance();
    }

    SDL_RenderPresent(renderer);
}

void cleanUpPractice(){
    if(!currentText)
        free(currentText);
    finished = 1;
    notMatch = 0;
    calculatePerformance();

    points[pointCount].x = SDL_GetTicks();
    points[pointCount].y = WPM;
    pointCount++;
    
    endTime = SDL_GetTicks();
    resizePoints(points, pointCount, center, 800, 400);
}

void assignAvatar(char *buffer){
    char opponentName[64];
    int i = 1, j = 0;
    while(buffer[i]){
        opponentName[j] = buffer[i];
        j++, i++;
    }
    opponentName[j] = '\0';

    myAvatar = first;
    oppAvatar = second;

    myAvatar.texture = player1ImageTexture;
    oppAvatar.texture = player2ImageTexture;
    if(buffer[0] == '1'){
        Avatar tmp = myAvatar;
        myAvatar = oppAvatar;
        oppAvatar = tmp;
    }

    strcpy(myAvatar.name, username);
    strcpy(oppAvatar.name, opponentName);
    
    free(buffer);
}

bool setupMultiPlayer(){
    bool status = serverConnect();
    if(!status) return 0;

    currentText = receiveStr();
    sendStr(username);
    maxTextSize = strlen(currentText);
    currentCharIndex = 0;

    int charCount = 0;
    for(int i = 0; i < maxTextSize; i++)
        if(currentText[i] != '\n') charCount++;
    movementPerMatch = ((float)WIDTH - myAvatar.w - 20) / charCount;

    rec.x = textPosx, rec.y = mulTexty, rec.width = fontWidth[(int) currentText[0]], rec.height = fontHeight, rec.color = White;

    capsOn = isCapsLockOn();
    win = 0, loss = 0;
    start = 0;
    notMatch = 0;
    match = 0;
    wordCount = 0;
    finished = 0;
    pointCount = 0, nextPointX = 0;
    totalTypedChar = 0, correctTypedChar = 0;
    assignAvatar(gameData());
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

void updateObjects(){
    charCount++;
    if(pressedKey == ' ')
        wordCount++;
    rec.x += curWidth;
    if(currentText[currentCharIndex] == '\n'){
        rec.y += 1.5*fontHeight;
        rec.x = textPosx;
        currentCharIndex++;
    }
    rec.width = fontWidth[(int) currentText[currentCharIndex]];

    if(currentCharIndex == maxTextSize){
        sendToServer(myAvatar.x + movementPerMatch);
        float tmp = receiveFromServer();
        if(tmp != 0) oppAvatar.x = tmp;
        wordCount++;
        resizePoints(points, pointCount, center, 800, 400);
        cleanUpMultiplayer();
    }
    myAvatar.x += movementPerMatch;
}

void updateMultiPlayer(){
    int wait = FRAME_TARGET_TIME - (SDL_GetTicks() - last_frame_time);
    if(wait > 0 && wait <= FRAME_TARGET_TIME){
        SDL_Delay(wait);
    }

    float delta_time = (SDL_GetTicks() - last_frame_time) / 1000.0f;
    last_frame_time = SDL_GetTicks();

    if(!finished){
        sendToServer(myAvatar.x);
        float tmp = receiveFromServer();
        if(tmp != 0) oppAvatar.x = tmp;
    }

    if(myAvatar.x>myAvatar.curx){
        myAvatar.curx += delta_time * 80.0;  // Adjust this as per current typing speed
    }

    if(oppAvatar.x>oppAvatar.curx){
        oppAvatar.curx += delta_time * 80.0;  // Adjust this as per current typing speed
    }

    updateButton(backButton);

    if(match) updateObjects();

    if(start && !finished){
        calculatePerformance();
        addPoint();
    }

    rec.color = notMatch? Red:White;
}

void renderMultiPlayer(){
    SDL_RenderCopy(renderer, boardTexture, NULL, NULL);

    renderButton(backButton);
    
    if(!finished){
        renderText(renderer, comic, myAvatar.name, Orange, myAvatar.curx + 10, myAvatar.y - 20);
        SDL_Rect player1Rect = {myAvatar.curx, myAvatar.y, myAvatar.w, myAvatar.h};
        SDL_RenderCopy(renderer, myAvatar.texture, NULL, &player1Rect);

        renderText(renderer, comic, oppAvatar.name, Orange, oppAvatar.curx + 10, oppAvatar.y - 20);
        SDL_Rect player2Rect = {oppAvatar.curx, oppAvatar.y, oppAvatar.w, oppAvatar.h};
        SDL_RenderCopy(renderer, oppAvatar.texture, NULL, &player2Rect);
        
        renderTextAndCursor(textPosx, mulTexty);
    }else{
        renderPerfomance();
    }
    SDL_RenderPresent(renderer);
}

void cleanUpMultiplayer(){
    if(!currentText)
    free(currentText);
    finished = 1;
    notMatch = 0;
    if(myAvatar.x > oppAvatar.x) win = 1;
    else if(myAvatar.x < oppAvatar.x) loss = 1;
    endTime = SDL_GetTicks();
    close_socket();
}

void destroy_window(){

    destroyButton(musicOffButton);
    destroyButton(musicOnButton);
    destroyButton(retryButton);
    destroyButton(backButton);
    destroyButton(easyButton);
    destroyButton(mediumButton);
    destroyButton(hardButton);

    SDL_DestroyTexture(boardTexture);
    SDL_DestroyTexture(player1ImageTexture);
    SDL_DestroyTexture(player2ImageTexture);

    TTF_CloseFont(comic);
    TTF_CloseFont(dejavu);
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    TTF_Quit();
    SDL_Quit();
}
