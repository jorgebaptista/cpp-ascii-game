#pragma once
#ifndef GAME_H
#define GAME_H

#include <iostream>
#include <fstream>
#include <sstream>
#include <list>
#include <vector>
#include <algorithm>

#include "FileSystem.h"
#include "Tile.h"
#include "World.h"
#include "GameCharacter.h"
#include "Player.h"
#include "Enemy.h"
#include "Equipment.h"
#include "Trap.h"

class Game
{
public:
	enum class difficulty { EASY, NORMAL, HARD}; // enum for difficulty

	Game();
	void init(difficulty diff); // difficulty of choice
	void Render(bool isDay); // render the map (draw the map)
	void Update(bool isDay); // update each character for movement and interaction
	void Battle(); // check if player is on same spot as any other character to battle it
	void Clean(); // clean all characters that are dead or interactables that were used

private:
	World* pWorld; // pointer for the world

	Player* pPlayer; // create pointer to player
	std::list<GameCharacter*> lpGameCharacters; // create a list of pointers to GameCharacters

	std::list<Interactable*> lpInteractables; // create a list of pointers to Interactables: Equipment and traps

	std::string deathScreen; // death drawing

	void GameOver(); // end game
};

#endif // !GAME