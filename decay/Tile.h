#pragma once
#ifndef TILE_H
#define TILE_H

#include "GameCharacter.h"
#include "Equipment.h"
#include <iostream>

class Tile
{
public:
	// create an enum of possible objects occupying this tile
	enum class content { EMPTY, WALL, PLAYER, ENEMY, NPC, MYSTERY };
	// constructor with empty as default
	Tile(content initialContent = content::EMPTY);

	// function to change content of tile
	void setContent(content contentTarget); // directly set current content of this cell
	void setContent(GameCharacter* gameCharacter); // set current content based on object passed
	void setContent(Interactable* equipment);

	content getContent(); // get current content

	void ClearContent(); // clear all contents that are not wall or empty
	// function to draw this Tile
	char DrawTile(); // draw this tile on the screen

	Interactable* getInteractable(); // get current intractable occupying this tile

	content _currentContent; // current content in this tile

private:

	Interactable* pInterectable; //current intractable occupying this tile

	// set the char for each of the contents
	char const EMPTYCHAR = '.';
	char const WALLCHAR = '#';
	char const PLAYERCHAR = 'P';
	char const ENEMYCHAR = '@';
	char const NPCCHAR = 'N';
	char const TREASURECHAR = '?';

	char m_currentChar; // current char of this tile

	void setCurrentChar(); // set current char based on current content
};
#endif // !TILE_H