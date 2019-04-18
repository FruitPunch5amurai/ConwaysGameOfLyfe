#include <stdio.h>      /* printf, scanf, NULL */
#include <stdlib.h>     /* malloc, free, rand */
#include <cstring>
#include <BasicLogger.h>
#include <RenderDraw.h>
#include <algorithm>    // std::copy
#include <vector>       // std::vector
#include <iostream>
#include <fstream>
#include <string>
#include "rapidjson/document.h"
#include "rapidjson/writer.h"
#include "rapidjson/stringbuffer.h"
#include "Grid.h"

const int PADDING_BETWEEN_TILES = 1; // pixels
using namespace std;
namespace ConwaysGoL
{
	Grid::Grid()
	{
	}


	Grid::~Grid()
	{
	}
	void Grid::ChangeStateOfTile(int posX, int posY)
	{
		int indexX = (posX - ((posX / tileWidth))*PADDING_BETWEEN_TILES) / tileWidth;
		int indexY = (posY - ((posY / tileHeight))*PADDING_BETWEEN_TILES) / tileHeight;
		int index = ((indexY + GRID_BORDER_OFFSET)*(DESIRED_NUMTILES_X + (GRID_BORDER_OFFSET * 2))) + (indexX + GRID_BORDER_OFFSET);
		cells[index].state = cells[index].state == 1 ? 0 : 1;
	}
	Grid GenerateGrid(const int screenWidth, const int screenHeight)
	{
		Grid tileGrid;
		tileGrid.width = DESIRED_NUMTILES_X;
		tileGrid.height = DESIRED_NUMTILES_Y;
		tileGrid.tileWidth = (screenWidth / DESIRED_NUMTILES_X) - PADDING_BETWEEN_TILES;
		tileGrid.tileHeight = (screenHeight / DESIRED_NUMTILES_Y) - PADDING_BETWEEN_TILES;
		int size = (tileGrid.width * tileGrid.height);
		return tileGrid;
	}
	void LoadGridFromJSON(std::string filePath, Grid &grid)
	{
		rapidjson::Document doc;
		ifstream file;
		string line;
		string output;
		int check = 0;
		int rowCount = GRID_BORDER_OFFSET;
		int counter = rowCount * (DESIRED_NUMTILES_X + (GRID_BORDER_OFFSET* 2)) + GRID_BORDER_OFFSET;  
		file.open(filePath);
		if (file.is_open())
		{
			while (getline(file, line))
			{
				output += line;
			};
			doc.Parse(output.c_str());

			assert(doc.IsObject());
			assert(doc.HasMember("Data"));
			assert(doc["Data"].IsArray());

			for (auto& v : doc["Data"].GetArray())
			{
				grid.cells[counter].state = v.GetInt();
				counter++;
				check++;
				if (check >= DESIRED_NUMTILES_X)
				{
					rowCount++;
					counter = rowCount * (DESIRED_NUMTILES_X + (GRID_BORDER_OFFSET * 2)) + GRID_BORDER_OFFSET;
					check = 0;
				}
			}
		}
		else
		{
			blog(Error, "Failed to read in JSON File");
		}
	}
	void Grid::UpdateCells()
	{
		Tile nCells[TRUE_NUMTILES_X * TRUE_NUMTILES_Y];
		for (int y = 0; y < TRUE_NUMTILES_X; y++)
		{
			for (int x = 0; x < TRUE_NUMTILES_Y; x++)
			{
				int p = (y*TRUE_NUMTILES_X) + x;
				Tile *tile = &cells[p];
				int tl, t, tr, r, br, b, bl, l;
				int i = (y*TRUE_NUMTILES_X) + x;
				int neighbors[8];
				//tl,t,tr,r,br,b,bl,l			
				neighbors[0] = (i - TRUE_NUMTILES_X) - 1 >= 0 && (i - TRUE_NUMTILES_X) - 1 >= TRUE_NUMTILES_X * (y - 1) ? (i - TRUE_NUMTILES_X) - 1 : -1;
				neighbors[1] = i - TRUE_NUMTILES_X >= 0 ? i - TRUE_NUMTILES_X : -1;
				neighbors[2] = (i - TRUE_NUMTILES_X) + 1 >= (y - 1) * TRUE_NUMTILES_X + 1 && (i - TRUE_NUMTILES_X) + 1 < y*TRUE_NUMTILES_X && (i - TRUE_NUMTILES_X) + 1 >= 0 ? (i - TRUE_NUMTILES_X) + 1 : -1;
				neighbors[3] = i + 1 < TRUE_NUMTILES_X * (y + 1) ? i + 1 : -1;
				neighbors[4] = i + TRUE_NUMTILES_X + 1 < TRUE_NUMTILES_X * (y + 1) + TRUE_NUMTILES_X && i + TRUE_NUMTILES_X + 1 < TRUE_NUMTILES_X*TRUE_NUMTILES_Y ? i + TRUE_NUMTILES_X + 1 : -1;
				neighbors[5] = i + TRUE_NUMTILES_X < TRUE_NUMTILES_X*TRUE_NUMTILES_Y ? TRUE_NUMTILES_X + i : -1;
				neighbors[6] = (i + TRUE_NUMTILES_X) - 1 >= (y + 1) * TRUE_NUMTILES_X && (i + TRUE_NUMTILES_X) - 1 < TRUE_NUMTILES_X*TRUE_NUMTILES_Y ? (i + TRUE_NUMTILES_X) - 1 : -1;
				neighbors[7] = i - 1 > (TRUE_NUMTILES_X * y) - 1 ? i - 1 : -1;
				int liveNeighbors = 0;
				for (int j = 0; j < 8; j++)
				{
					if (neighbors[j] == -1)
						continue;
					if (cells[neighbors[j]].state == 1)
						liveNeighbors++;
				}
				//Any live cell with fewer than two live neighbors dies, as if by under population.
				if (liveNeighbors < 2 && tile->state == 1)
					nCells[p].state = 0;
				else if ((liveNeighbors == 2 || liveNeighbors == 3) && tile->state == 1)
					nCells[p].state = 1;
				else if (liveNeighbors > 3 && tile->state == 1)
					nCells[p].state = 0;
				else if (tile->state == 0 && liveNeighbors == 3)
					nCells[p].state = 1;
			}
		}
		std::copy(nCells, nCells + TRUE_NUMTILES_X * TRUE_NUMTILES_Y, cells);
	}
	void FreeGrid(Grid grid)
	{
		/*if (grid.tiles != NULL)
		{
			free(grid.tiles);
		}*/
	}
	void DrawGrid(SDL_Renderer* renderer, Grid grid)
	{
		/*for (int y = 0; y < grid.height; y++)
		{
			for (int x = 0; x < grid.width; x++)
			{
				int indexIntoTileGrid = (y*grid.width) + x;
				int tileAlive = grid.tiles[indexIntoTileGrid].state;
				Uint8 color = 255 * tileAlive;
				int xLocal = x * grid.tileWidth + (x*PADDING_BETWEEN_TILES) + (PADDING_BETWEEN_TILES / 2);
				int yLocal = y * grid.tileHeight + (y * PADDING_BETWEEN_TILES) + (PADDING_BETWEEN_TILES / 2);
				DrawRect(renderer, xLocal, yLocal, grid.tileWidth, grid.tileHeight, SDL_Color{ color ,color,color });
			}
		}*/
		for (int y = 0; y < grid.height; y++)
		{
			for (int x = 0; x < grid.width; x++)
			{
				int indexIntoTileGrid = ((y + GRID_BORDER_OFFSET)*(DESIRED_NUMTILES_X + (GRID_BORDER_OFFSET * 2))) + (x + GRID_BORDER_OFFSET);
				int tileAlive = grid.cells[indexIntoTileGrid].state;
				Uint8 color = 255 * tileAlive;
				int xLocal = x * grid.tileWidth + (x*PADDING_BETWEEN_TILES) + (PADDING_BETWEEN_TILES / 2);
				int yLocal = y * grid.tileHeight + (y * PADDING_BETWEEN_TILES) + (PADDING_BETWEEN_TILES / 2);
				DrawRect(renderer, xLocal, yLocal, grid.tileWidth, grid.tileHeight, SDL_Color{ color ,color,color });
			}
		}
	}
}