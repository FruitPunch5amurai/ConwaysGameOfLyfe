#include "RenderDraw.h"

void DrawRect(SDL_Renderer* renderer, int x, int y, int w, int h, SDL_Color color)
{
	SDL_Rect rect;
	SDL_SetRenderDrawColor(renderer, color.r, color.b, color.g, color.a);
	rect.x = x;
	rect.y = y;
	rect.w = w;
	rect.h = h;

	SDL_RenderFillRect(renderer, &rect);
}

void DrawLine(SDL_Renderer* renderer, int x, int y, int x2, int y2, SDL_Color color)
{
	SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, SDL_ALPHA_OPAQUE);
	SDL_RenderDrawLine(renderer, x, y, x2, y2);
}