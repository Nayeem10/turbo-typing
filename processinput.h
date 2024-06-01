#ifndef PROCESS_INPUT_H
#define PROCESS_INPUT_H

bool shiftPressed = 0, mousePressed = 0;
bool capsOn = 0;

int pressedKey, mouseX, mouseY;
bool keyUp = 0, keyDown = 0, mouseUp = 0, mouseDown = 0;

void getMouseAndKeyboardState(){
    keyUp = 0, keyDown = 0, mouseUp = 0, mouseDown = 0;
    SDL_Event event;
    SDL_PollEvent(&event);
    switch(event.type){

    case SDL_QUIT:
        game_is_running = false;
        break;

    case SDL_KEYDOWN:
        pressedKey = event.key.keysym.sym;
        keyDown = true;
        if(pressedKey == SDLK_ESCAPE){
            game_is_running = false;
            break;
        }
        if(pressedKey == SDLK_LSHIFT || pressedKey == SDLK_RSHIFT){
            shiftPressed = true;
            capsOn ^= 1;
            break;
        }
        if(pressedKey == SDLK_CAPSLOCK){
            capsOn ^= 1;
            break;
        }
        
        if(capsOn && pressedKey >= 'a' && pressedKey <= 'z'){
            pressedKey = (pressedKey - 'a' + 'A');
        }else if(shiftPressed && (pressedKey < 'a' || pressedKey > 'z')){
            pressedKey = shift_map[pressedKey];
        }
        break;
    case SDL_KEYUP:
        keyUp = true;
        if (event.key.keysym.sym == SDLK_LSHIFT || event.key.keysym.sym == SDLK_RSHIFT) {
            shiftPressed = false;
            capsOn ^= 1;
        }
        break;
        
    case SDL_MOUSEBUTTONDOWN:
        mousePressed = 1;
        mouseDown = true;
        break;
    case SDL_MOUSEBUTTONUP:
        mousePressed = 0;
        mouseUp = true;
        break;
    }
    SDL_GetMouseState(&mouseX, &mouseY);
}

bool mouseInBox(SDL_Rect box){
    return mouseX >= box.x && mouseX <= box.x + box.w && mouseY >= box.y && mouseY <= box.y + box.h;
}

#endif