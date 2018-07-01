#pragma once
#include <SDL2\SDL.h>
#include <string>
namespace GameEngine
{
	enum  WindowFlags {
		INVISIBLE = 0x0,
		FULLSCREEN = 0x2,
		BORDERLESS = 0x4
	};
	class Window
	{
	public:
		Window();
		~Window();
		int CreateSDLWindow(std::string windowName, int screenWidth, int screenHeight, unsigned int flags);
		void Destroy();
		static SDL_Renderer * GetRenderer() { return _sdlRenderer; };
		void SwapOpenGLBuffer();

		int getScreenWidth() { return _screenWidth; }
		int getScreenHeight() { return _screenHeight; }
	private:
		int _screenWidth;
		int _screenHeight;
		SDL_Window * _sdlWindow;
		static SDL_Renderer *_sdlRenderer;
	};
}

