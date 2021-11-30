#pragma once
#ifndef GAMECHARACTER_H
#define GAMECHARACTER_H
#include <iostream>
#include <vector>
#include <utility>
#include "GameObject.h"

class GameCharacter : public GameObject
{
public:
	// Constructor
	GameCharacter();

	// create an enum of possible types of game character
	enum class type
	{
		PLAYER,
		ENEMY,
		BOSS
	};

	bool IsAlive(); // check if its alive (stam > 0)
	type getTypeID(); // get type if its player enemy or boss to draw on map

	virtual std::pair<int, int> Update(bool isDay) = 0; // pure virtual so that it can be overridden in derived classes, returns a pair (x and y)
	virtual void Stats(); // print stats

	void HitWall(); // hit a wall

	// battle functions
	int RollSkill(); // roll skill to get attack strength
	void Attack(GameCharacter* gameCharacter); // attack another character
	void TakeDamage(int damage); // take specific damage to current stamina

protected:
	// properties
	type m_typeID;
	bool m_alive;

	// stats
	int m_skill; // current
	int m_maxStamina;
	int m_currentStamina;
	int m_damage;
	int m_speed; // speed at which is moving when hitting walls
};

#endif // !GAMECHARACTER