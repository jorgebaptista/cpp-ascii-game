#pragma once
#ifndef ENEMY_H
#define ENEMY_H

#include "GameCharacter.h"

class Enemy : public GameCharacter
{
public:
	Enemy();
	std::pair<int, int> Update(bool isDay) override; // overrides base class function
};

#endif // !ENEMY_H