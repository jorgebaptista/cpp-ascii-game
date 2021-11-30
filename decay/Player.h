#pragma once
#ifndef PLAYER_H
#define PLAYER_H

#include "GameCharacter.h"

class Equipment; // forward declaration so can use pointer to it and avoid recursive includes

class Player : public GameCharacter
{
public:
	Player();
	std::pair<int, int> Update(bool isDay) override; // overrides base class function
	void Stats() override; // override to include luck
	bool Ask(); // ask yes or no question and return
	bool RollLuck(); // roll luck check and return if successful or unsuccessful
	int getLuck(); // get current luck value

	bool Equip(Equipment* equipment); // equip new item and return if player decided to equip or not

private:
	int m_maxLuck; // variables to store luck
	int m_currentLuck;
	Equipment* m_equipment; // current equipped item
};

#endif // !PLAYER_H