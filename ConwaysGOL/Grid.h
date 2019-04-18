#pragma once
#include <SDL2\SDL.h>
#include "Tile.h"
namespace ConwaysGoL
{
	const int DESIRED_NUMTILES_X = 40;
	const int DESIRED_NUMTILES_Y = 40;
	const int GRID_BORDER_OFFSET = 5;
	const int TRUE_NUMTILES_X = DESIRED_NUMTILES_X + GRID_BORDER_OFFSET * 2;
	const int TRUE_NUMTILES_Y = DESIRED_NUMTILES_Y + GRID_BORDER_OFFSET * 2;

	class Grid
	{
	public:
		Grid();
		~Grid();


		Tile cells[TRUE_NUMTILES_X*TRUE_NUMTILES_Y];
		int width,height;
		int tileWidth, tileHeight;

		void ChangeStateOfTile(int posX,int posY);
		void UpdateCells();
	};
	Grid GenerateGrid(int screenWidth, int screenHeight);
	void LoadGridFromJSON(std::string filePath, Grid &grid);
	void FreeGrid(Grid grid);
	void DrawGrid(SDL_Renderer* renderer, Grid grid);
}
