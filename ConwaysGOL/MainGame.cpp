#include <ResourceManager.h>
#include <BasicLogger.h>
#include <RenderDraw.h>
#include <iostream>
#include "MainGame.h"
#include "Tile.h"

const int SCREEN_WIDTH = 800;
const int SCREEN_HEIGHT = 800;
const int UPDATE_FREQUENCY = 100; //Milliseconds


namespace ConwaysGoL
{
	MainGame::MainGame():
		_currentState(GameState::PLAYING),
		_screenWidth(SCREEN_WIDTH),
		_screenHeight(SCREEN_HEIGHT),
		_desiredFPS(60.0f),
		_lastUpdateTime(0)
	{
	}


	MainGame::~MainGame()
	{
	}
	void MainGame::Run()
	{
		Init();
		Loop();
	}
	void MainGame::Init()
	{


		_window.CreateSDLWindow("ConwaysGameOfLife", _screenWidth, _screenHeight, 0);		

		// load sample.png into image
		sprite = GameEngine::CreateSprite("Sprites\\Rammus.jpg");

		//Initiate Grid
		tileGrid = GenerateGrid(SCREEN_WIDTH, SCREEN_HEIGHT);

		LoadGridFromJSON("sun.json", tileGrid);

	}
	void MainGame::Loop()
	{
		while (_currentState != GameState::EXIT)
		{
			ProcessInput();
			if (SDL_GetTicks() - _lastUpdateTime >= UPDATE_FREQUENCY)
			{
				blog(Debug, "Updating Grid");
				tileGrid.UpdateCells();
				_lastUpdateTime = SDL_GetTicks();
			}
			Draw();
		}

		//Uninitialize
		FreeGrid(tileGrid);
		_window.Destroy();
	}
	void MainGame::ProcessInput()
	{
		while (SDL_PollEvent(&event))
		{
			switch (event.type)
			{
			case SDL_QUIT:
				_currentState = GameState::EXIT;
				break;
			case SDL_MOUSEBUTTONDOWN:
				_inputManager.KeyPress(event.button.button);
				tileGrid.ChangeStateOfTile(event.motion.x, event.motion.y);
				break;
			case SDL_MOUSEBUTTONUP:
				_inputManager.KeyRelease(event.button.button);
				break;
			case SDL_MOUSEMOTION:
				_inputManager.setMouseCoords(event.motion.x, event.motion.y);
				break;
			}
		}
	}
	void MainGame::Draw()
	{
		//Set Background color
		SDL_SetRenderDrawColor(_window.GetRenderer(), 0, 0, 0, 0);

		SDL_RenderClear(_window.GetRenderer());
		//sprite->Draw(0, 0, 0, _window.GetRenderer(), SDL_FLIP_NONE);
		//SDL_RenderCopy(_window.GetRenderer(),sprite->texture,NULL,NULL);
		
		DrawGrid(_window.GetRenderer(), tileGrid);

		SDL_RenderPresent(_window.GetRenderer());
	}
}
