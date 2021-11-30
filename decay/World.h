#pragma once
#ifndef WORLD_H
#define WORLD_H
#include "GameCharacter.h"
#include "Player.h"
#include "Tile.h"
#include <iostream>

class World
{
public:
	World(int rows = 20, int cols = 30, int dayVisionRadius = 5, int nightVisionRadius = 2); // constructor

	Tile* getTile(int x, int y); // get tile of x and y position
	void setTile(int x, int y, Tile::content content); // set tile of x and y position directly with new content
	void setTile (GameCharacter* gameCharacter); // set based on object passed
	void setTile (Interactable* interactable);

	void ClearTiles(); // clear all tiles of objects before redrawing
	void DrawWorld(Player* pPlayer, bool isDay); // draw tiles on screen

	int getColTotal(); // get total cols
	int getRowTotal(); // get total rows

private:
	// size of the grid (rows and columns)
	int m_gridRowSize; // row
	int m_gridColSize; // col
	int m_dayVisionRadius; // how many tiles can player see at day
	int m_nightVisionRadius; // how many tiles can player see at night
	// create a vector of vectors where each cell of the map will be stored
	std::vector<std::vector<Tile*>> gameMap; // rows of cols

};
#endif // !WORLD_H