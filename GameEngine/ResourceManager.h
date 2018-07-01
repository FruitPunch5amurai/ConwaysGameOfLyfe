#pragma once
#include "Sprite.h"
#include <string>
#include <map>
namespace GameEngine
{
	class TextureCache
	{
	public:
		SDL_Texture* GetTexture(std::string texturePath);
	private:
		std::map<std::string, SDL_Texture*> _textureMap;
	};

	class SpriteCache
	{
	public:
		Sprite* GetSprite(std::string spritePath);
	private:
		std::map<std::string, Sprite*> _spriteMap;
	};

	class ResourceManager
	{
	public:
		ResourceManager();
		~ResourceManager();
	public:
		static SDL_Texture* GetTexture(std::string texturePath);
		static Sprite* GetSprite(std::string spritePath);
	private:
		static TextureCache _textureCache;
		static SpriteCache _spriteCache;
	};
}
