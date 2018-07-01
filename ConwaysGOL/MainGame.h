#pragma once
#include <Sprite.h>
#include <Window.h>
#include <InputManager.h>
#include "Grid.h"
namespace ConwaysGoL
{

	enum class GameState {
		PLAYING,
		EXIT
	};
	class MainGame
	{
	public:
		MainGame();
		~MainGame();

		void Run();

	private:
		SDL_Event		event;
		GameState		_currentState;

		GameEngine::Window			_window;
		GameEngine::InputManager _inputManager;
		int				_screenWidth;
		int				_screenHeight;
		int				_desiredFPS;
		Uint32			_lastUpdateTime;
		GameEngine::Sprite*			sprite;

		Grid tileGrid;

		void			Init();
		void			Loop();
		void			ProcessInput();
		void			Draw();
	};
}