#ifndef GRAPH_H
#define GRAPH_H

#include "utilis.h"

SDL_Point pointsInPixel[100000];

void resizePoints(SDL_Point points[], int n, SDL_Point center,int width, int height){
	center.x += 10, center.y -= 10;
    int mn_w = 1e7, mx_w = 0;
    for(int i = 0; i < n; i++){
        mn_w = min(mn_w, points[i].x);
        mx_w = max(mx_w, points[i].x);
    }

    int W = mx_w - mn_w + 1, H = 100;

    for(int i = 0; i < n; i++){
        pointsInPixel[i].x = center.x + (width * (points[i].x - mn_w)) / W;
        pointsInPixel[i].y = center.y - (height * (points[i].y)) / H;
    }
}

void drawGraph(SDL_Renderer *renderer, SDL_Point points[], int pointCount,SDL_Color color,SDL_Point center,int width, int height){

    resizePoints(points, pointCount, center, width, height);

    SDL_Rect x_coordinate = {center.x, center.y, width + 10, 5};
    SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b,200);
    SDL_RenderFillRect(renderer, &x_coordinate);

    SDL_Rect y_coordinate = {center.x, center.y - height - 10, 5, height + 10};
    SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b,200);
    SDL_RenderFillRect(renderer, &y_coordinate);

    SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, 200);

    SDL_RenderDrawLines(renderer, pointsInPixel, pointCount);

	for(int i = 0; i < pointCount; i++){
		SDL_Rect rectangle = {pointsInPixel[i].x - 3, pointsInPixel[i].y - 3, 6, 6};
    	SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, 255);
    	SDL_RenderFillRect(renderer, &rectangle);
        rectangle.x -= 10, rectangle.y -= 10, rectangle.w += 20, rectangle.h += 20;
        if(mouseInBox(rectangle)){
            char wpm[5];
            sprintf(wpm,"%d", points[i].y);
            renderText(renderer, dejavu, wpm, color, pointsInPixel[i].x + 5, pointsInPixel[i].y);
        }
	}
}

#endif