#pragma once

#include <SDL2/SDL.h>

void DrawRect(SDL_Renderer* renderer, int x, int y, int w, int h, SDL_Color color);
void DrawLine(SDL_Renderer* renderer, int x, int y, int x2, int y2, SDL_Color color);
