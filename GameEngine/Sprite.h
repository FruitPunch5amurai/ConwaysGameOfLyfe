#ifndef __SPRITE_H_
#define __SPRITE_H_

#include <SDL2/SDL.h>
#include <string>
namespace GameEngine
{
class Sprite
{
public:
	SDL_Texture *texture;
	SDL_Surface *surfaceImage;
	std::string filename;
	
	int width, height;
	int widthPerFrame, heightPerFrame;
	int framesPerLine;

	Sprite();
	~Sprite();

	void Draw(int sx, int sy, int frame, SDL_Renderer *renderer, SDL_RendererFlip flip);
};
Sprite* CreateSprite(int sizeX, int sizeY, int framesPerLine, std::string pathName);
Sprite* CreateSprite(std::string pathName);
}
#endif

