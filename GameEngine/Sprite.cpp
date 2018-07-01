#include <GLM\glm.hpp>
#include "ResourceManager.h"
#include "Sprite.h"

namespace GameEngine
{
	Sprite::Sprite()
	{
	}


	Sprite::~Sprite()
	{
	}

	Sprite* CreateSprite(int sizeX, int sizeY,int framesPerLine, std::string pathName)
	{
		Sprite* sprite = ResourceManager::GetSprite(pathName);
		if (sprite != nullptr)
		{
			sprite->height = sizeY;
			sprite->width = sizeX;
			sprite->framesPerLine = framesPerLine;
		}
		return sprite;
	}
	Sprite* CreateSprite(std::string pathName)
	{
		Sprite* sprite = ResourceManager::GetSprite(pathName);
		if (sprite != nullptr)
		{
			SDL_QueryTexture(sprite->texture, NULL, NULL, &sprite->width, &sprite->height);
			sprite->framesPerLine = 0;
		}
		return sprite;
	}
	void Sprite::Draw(int sx,int sy, int frame,SDL_Renderer *renderer,SDL_RendererFlip flip)
	{
		SDL_Rect dest, src;
		src.x = frame % framesPerLine * width;
		src.y = frame / framesPerLine * height;
		src.w = width;
		src.h = height;
		dest.x = sx;// -game->camera->x;
		dest.y = sy;// -game->camera->y;
		dest.w = width;
		dest.h = height;
		SDL_RenderCopyEx(renderer, texture, &src, &dest, 0, 0, flip);
	}
}