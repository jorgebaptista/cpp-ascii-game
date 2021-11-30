#include "Tile.h"

Tile::Tile(content initialContent)
{
	_currentContent = initialContent; // set initial content of the tile

	setCurrentChar(); // set current char based on tile content
}

void Tile::setContent(content contentTarget)
{
	_currentContent = contentTarget; // directly set current content of this tile

	setCurrentChar(); // set current char based on tile content
}

void Tile::setContent(GameCharacter* gameCharacter)
{
	// check the type of the game character and set its content accordingly
	switch (gameCharacter->getTypeID())
	{
	case GameCharacter::type::PLAYER:
		_currentContent = content::PLAYER;
		break;
	case GameCharacter::type::ENEMY:
		_currentContent = content::ENEMY;
		break;
	default:
		break;
	}

	setCurrentChar(); // set current char based on tile content
}

void Tile::setContent(Interactable* interactable)
{
	pInterectable = interactable; // set current interactable on this tile

	_currentContent = content::MYSTERY; // set content to mystery
	setCurrentChar(); // set current char based on tile content
}

Tile::content Tile::getContent()
{
	return _currentContent; // return the current content of this tile
}

void Tile::ClearContent()
{
	// if not a wall and not empty
	if (_currentContent != content::WALL && _currentContent != content::EMPTY)
	{
		_currentContent = content::EMPTY; // set to empty
		setCurrentChar(); // set current char based on tile content
	}

	if (pInterectable != nullptr) pInterectable = nullptr; // also clear interactable object that was in this tile
}

char Tile::DrawTile()
{
	//std::cout << m_currentChar << " ";
	return m_currentChar;
}

Interactable* Tile::getInteractable()
{
	return pInterectable;
}

void Tile::setCurrentChar()
{
	switch (_currentContent) // check which is the current content and draw accordingly
	{
	case content::EMPTY:
		m_currentChar = EMPTYCHAR;
		break;
	case content::WALL:
		m_currentChar = WALLCHAR;
		break;
	case content::PLAYER:
		m_currentChar = PLAYERCHAR;
		break;
	case content::ENEMY:
		m_currentChar = ENEMYCHAR;
		break;
	case content::NPC:
		m_currentChar = NPCCHAR;
		break;
	case content::MYSTERY:
		m_currentChar = TREASURECHAR;
		break;
	default:
		break;
	}
}
