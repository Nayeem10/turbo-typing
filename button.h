#ifndef BUTTON_H
#define BUTTON_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_mixer.h>
#include "processinput.h"
#include "utilis.h"

Mix_Chunk *sfx;

typedef struct Button{
    SDL_Renderer *renderer;
    SDL_Texture *texture[3];
    SDL_Rect rec;
    int zoomBorder;
    bool state[3];
	void (*handler)();
} Button;

void resetState(Button *button){
    button->state[0] = 1;
    button->state[1] = 0;
    button->state[2] = 0;
}

Button* createButton(SDL_Renderer *renderer, char *normal, char *hover, char *pressed, SDL_Rect rec, int zoomBorder, void (*handler)()){
    Button *button = malloc(sizeof(Button));
    button->renderer = renderer;
    SDL_Surface *surface = IMG_Load(normal);
    if (!surface) {
        fprintf(stderr, "Error loading image --> %s.\n",normal);
        return;
    }
    button->texture[0] = SDL_CreateTextureFromSurface(renderer, surface);

    surface = IMG_Load(hover);
    if (!surface) {
        fprintf(stderr, "Error loading image --> %s.\n",hover);
        return NULL;
    }
    button->texture[1] = SDL_CreateTextureFromSurface(renderer, surface);

    surface = IMG_Load(pressed);
    if (!surface) {
        fprintf(stderr, "Error loading image --> %s.\n",pressed);
        return NULL;
    }
    button->texture[2] = SDL_CreateTextureFromSurface(renderer, surface);
    button->rec = rec;
    button->zoomBorder = zoomBorder;
    button->state[0] = 1, button->state[1] = 0, button->state[2] = 0;
    button->handler = handler;

    SDL_FreeSurface(surface);
    return button;
}

void updateButton(Button *button){
    if(!mouseInBox(button->rec)){
        resetState(button);
        return;
    }

    if(mouseDown){
        Mix_PlayChannel(0, sfx, 0);
    }

    if(mousePressed){
        button->state[0] = 0;
        button->state[1] = 0;
        button->state[2] = 1;
    }else if(mouseUp){
        button->handler();
    }else{
        button->state[0] = 0;
        button->state[1] = 1;
        button->state[2] = 0;
    }
}

void renderButton(Button *button){
    if(button->state[0])
        SDL_RenderCopy(button->renderer, button->texture[0], NULL, &button->rec);
    else if(button->state[1]){
        SDL_RenderCopy(button->renderer, button->texture[1], NULL, &button->rec);
    }else{
        int border = button->zoomBorder;
        SDL_Rect tmp = {button->rec.x - border / 2, button->rec.y - border / 2, button->rec.w + border, button->rec.h + border};
        SDL_RenderCopy(button->renderer, button->texture[2], NULL, &tmp);
    }
}

void destroyButton(Button *button){
    for(int i = 0; i < 3; i++){
        SDL_DestroyTexture(button->texture[i]);
    }
    free(button);
}

#endif