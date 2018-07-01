#include "Window.h"
#include <BasicLogger.h>
#include <SDL2/SDL_image.h>
namespace GameEngine
{
	//Initialize static renderer
	SDL_Renderer* Window::_sdlRenderer;

	Window::Window()
	{
	}


	Window::~Window()
	{
	}
	int Window::CreateSDLWindow(std::string windowName, int screenWidth, int screenHeight, unsigned int flags)
	{
		//Set Flags
		Uint32 currentFlags = SDL_WINDOW_OPENGL;
		if (flags & INVISIBLE)
		{
			currentFlags |= SDL_WINDOW_HIDDEN;
		}
		if (flags & FULLSCREEN)
		{
			currentFlags |= SDL_WINDOW_FULLSCREEN_DESKTOP;
		}
		if (flags & BORDERLESS)
		{
			currentFlags |= SDL_WINDOW_BORDERLESS;
		}
		// load support for the JPG and PNG image formats
		int img_flags = IMG_INIT_JPG | IMG_INIT_PNG;
		int initted = IMG_Init(img_flags);
		if ((initted&img_flags) != img_flags) {
			blog(Error, "IMG_Init: Failed to init required jpg and png support!\n");
			blog(Error, "IMG_Init: %s\n", IMG_GetError());
		}
		_screenHeight = screenHeight;
		_screenWidth = screenWidth;
		_sdlWindow = SDL_CreateWindow(windowName.c_str(), SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
			_screenWidth, _screenHeight, currentFlags);

		_sdlRenderer = SDL_CreateRenderer(_sdlWindow, -0, currentFlags);
		SDL_SetRenderDrawColor(_sdlRenderer, 0, 0, 0, 255);
		
		SDL_RenderClear(_sdlRenderer);

		SDL_RenderPresent(_sdlRenderer);

		SDL_GLContext glContex = SDL_GL_CreateContext(_sdlWindow);
		if (glContex == nullptr)
		{
			blog(Error, "SDL_GL context could not be created");
		}
		blog(Debug, "SDL_Window Created Successfully!");
		//Enable/Disable VSYNC
		SDL_GL_SetSwapInterval(0);

		return 0;
	}
	void Window::Destroy()
	{
		IMG_Quit();
		SDL_DestroyWindow(_sdlWindow);
		SDL_DestroyRenderer(_sdlRenderer);
		SDL_Quit();
	}
	void Window::SwapOpenGLBuffer()
	{
		SDL_GL_SwapWindow(_sdlWindow);
	}
}