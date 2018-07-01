#include "ResourceManager.h"
#include <BasicLogger.h>
#include <SDL2/SDL_image.h>
#include "Window.h"

namespace GameEngine
{
	TextureCache ResourceManager::_textureCache;
	SpriteCache ResourceManager::_spriteCache;

	ResourceManager::ResourceManager()
	{
	}


	ResourceManager::~ResourceManager()
	{
	}
	SDL_Texture* ResourceManager::GetTexture(std::string texturePath)
	{
		return _textureCache.GetTexture(texturePath);
	}
	Sprite * ResourceManager::GetSprite(std::string spritePath)
	{
		return 		_spriteCache.GetSprite(spritePath);
	}
	SDL_Texture* TextureCache::GetTexture(std::string texturePath)
	{
		SDL_Texture* texture = nullptr;
		auto it = _textureMap.find(texturePath);
		if (it == _textureMap.end())
		{
			SDL_Surface* temp = IMG_Load(texturePath.c_str());
			if (temp == NULL) 
			{
				blog(Error, "Failed to load image %s in resource manager", texturePath);
			}
			texture = SDL_CreateTextureFromSurface(Window::GetRenderer(), temp);
			SDL_FreeSurface(temp);
			_textureMap.insert(make_pair(texturePath, texture));
			return texture;
		}
		return texture;
	}
	Sprite * SpriteCache::GetSprite(std::string spritePath)
	{
		Sprite* sprite = nullptr;
		auto it = _spriteMap.find(spritePath);
		if (it == _spriteMap.end())
		{
			sprite = new Sprite();
			sprite->texture = ResourceManager::GetTexture(spritePath);
			_spriteMap.insert(make_pair(spritePath, sprite));
			return sprite;
		}
		return it->second;
	}
}