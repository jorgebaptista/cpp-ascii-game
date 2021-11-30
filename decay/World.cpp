#include "World.h"

World::World(int rows, int cols, int dayVisionRadius, int nightVisionRadius)
{
	// get properties passed
	m_gridRowSize = rows;
	m_gridColSize = cols;
	m_dayVisionRadius = dayVisionRadius;
	m_nightVisionRadius = nightVisionRadius;

	// create the tiles of the map
	// for each row
	for (int i = 0; i < m_gridRowSize; i++)
	{
		// push back a new vector of tile
		gameMap.push_back(std::vector<Tile*>());
		// for each cow (each vector of tiles)
		for (int j = 0; j < m_gridColSize; j++)
		{
			Tile::content tileContent; // store tile content

			// if the tile is at the bottom, top right most or left most, turn into a wall
			if (i == 0 || i == m_gridRowSize - 1 || j == 0 || j == m_gridColSize - 1)
			{
				tileContent = Tile::content::WALL; // set to wall
			}
			else if (((rand() % 100) + 1) >= 95) // 5% chance to turn into a wall
			{
				tileContent = Tile::content::WALL;
			}
			else
			{
				tileContent = Tile::content::EMPTY; // set to empty
			}

			Tile* tile = new Tile(tileContent); // create tile with predefined content
			gameMap[i].push_back(tile); // push tile into the tile vector
		}
	}
}

void World::DrawWorld(Player* pPlayer, bool isDay)
{
	int visionRadius = isDay ? m_dayVisionRadius : m_nightVisionRadius; // if its daytime set vision radius to...

	// set minimum vision to player current row - vision radius
	int iMin = pPlayer->getY() - visionRadius;
	if (iMin < 0) iMin = 0; // don't let iMin be negative
	// set maximum vision to player current row + vision radius
	int iMax = pPlayer->getY() + visionRadius;
	if (iMax > m_gridRowSize) iMax = m_gridRowSize;
	// set minimum vision to player current col - vision radius
	int jMin = pPlayer->getX() - visionRadius;
	if (jMin < 0) jMin = 0;
	// set maximum vision to player current col + vision radius
	int jMax = pPlayer->getX() + visionRadius;
	if (jMax > m_gridColSize) jMax = m_gridColSize;

	// for each row tile the player can see
	for (int i = iMin; i < iMax; i++)
	{
		std::cout << "\n"; // create a new line

		std::string row; // create a string to store the whole row and then print it later

		// to make camera center on player always
		if (!isDay) // if it's night
		{
			for (int diff = visionRadius; diff < m_dayVisionRadius; diff++) // for each number that vision radius is less than day vision radius
			{
				row += "   "; // add 3 empty spaces 1 for each tile and 2 because each tile has 2 characters
			}
		}
		if (pPlayer->getX() <= visionRadius) // if player current col is less than day radius
		{
			for (int diff = pPlayer->getX(); diff <= visionRadius - 1; diff++) // for each col
			{
				row += "   "; // add 3 empty spaces.
			}
		}
		// for each col tile player can see
		for (int j = jMin; j < jMax; j++)
		{
			row += gameMap[i][j]->DrawTile(); // draw the tile
			row += "  "; // add 2 empty spaces between tiles to make map more readable
		}

		std::cout << row; // print whole row
	}

	// to make the camera center on player always
	if (!isDay) // if it's night
	{
		for (int diff = visionRadius; diff < m_dayVisionRadius; diff++) // for each number that vision radius is less than day vision radius
		{
			std::cout << "\n"; // add a new line
		}
	}
	if (pPlayer->getY() >= m_gridRowSize - visionRadius) // if player current row position is more than total rows - day vision radius
	{
		// for each row
		for (int diff = pPlayer->getY(); diff >= m_gridRowSize - visionRadius + 1; diff--)
		{
			std::cout << "\n"; // write a new line
		}
	}

	std::cout << "\n"; // print new line
}

Tile* World::getTile(int col, int row)
{
	return gameMap[row][col]; // return tile of row, col
}

void World::setTile(int col, int row, Tile::content content)
{
	getTile(row, col)->setContent(content); // get tile at row and col and set its new content
}

void World::setTile(GameCharacter* gameCharacter)
{
	getTile(gameCharacter->getX(), gameCharacter->getY())->setContent(gameCharacter); // get tile at x and y positions of character and pass the character into it
}

void World::setTile(Interactable* interactable)
{
	getTile(interactable->getX(), interactable->getY())->setContent(interactable); // get tile at x and y positions of object and pass the equipment into it
}

void World::ClearTiles()
{
	// for each row
	for (int i = 0; i < m_gridRowSize; i++)
	{
		// for each col
		for (int j = 0; j < m_gridColSize; j++)
		{
			gameMap[i][j]->ClearContent(); // clear content of this tile
		}
	}
}

int World::getColTotal()
{
	return m_gridColSize; // get the size in x of current map
}

int World::getRowTotal()
{
	return m_gridRowSize; // get size in y of current map
}
