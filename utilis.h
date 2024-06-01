#ifndef UTILIS_H
#define UTILIS_H

int max(int a, int b){
    return(a > b) ? a : b;
}

int min(int a, int b){
    return(a < b) ? a : b;
}

void arrayCopy(bool *a, const bool *b, int n){
    for(int i=0; i<n; i++)
        a[i] = b[i];
}

int getWidth(char ch){
    char str[1]; str[0]=ch;
    int width;
    TTF_SizeText(comic, str , &width, NULL);
    return width;
}

void renderText(SDL_Renderer* renderer, TTF_Font* font, const char* text, SDL_Color color, int textX, int textY) {
    if(strlen(text) == 0) return;
    
    SDL_Surface* surface = TTF_RenderText_Solid(font, text, color);
    SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, surface);

    int textWidth = surface->w;
    int textHeight = surface->h;
    
    SDL_Rect textRect = { textX, textY, textWidth, textHeight };
    SDL_RenderCopy(renderer, texture, NULL, &textRect);
}

void loadImage(SDL_Renderer* renderer, SDL_Texture** texture, const char* img) {
    SDL_Surface* imageSurface = IMG_Load(img);
    if (!imageSurface) {
        fprintf(stderr, "Error loading image --> %s.\n",img);
        return;
    }

    *texture = SDL_CreateTextureFromSurface(renderer, imageSurface);
    SDL_FreeSurface(imageSurface);
    if (!texture) {
        fprintf(stderr,"Error initializing texture.\n");
        return;
    }
}
#endif