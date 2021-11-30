#include "Enemy.h"

Enemy::Enemy()
{
	m_typeID = GameCharacter::type::ENEMY; // set this type of character as an enemy so tile can draw accordingly
	m_name = "Goblin"; // set name

	m_drawing = FileSystem::instance().ReadDrawing("graphics/enemy.txt"); // set drawing of this enemy

	m_skill -= 3; // decrement skill by 3 to make it easier for player
}

std::pair<int, int> Enemy::Update(bool isDay)
{
	int x = m_x; // set pretended x to current x
	int y = m_y; // set pretended y to current y

	int chance = rand() % 2; // get a random number between 0 and 1, 50% chance
	int direction = chance == 1 ? 1 : -1; // ternary operator, if chance variable is 1 direction will be 1 (north), else it will be -1 (south)

	// generates a random value between 1 and 10
	int chanceToMove = ((rand() % 10) + 1);

	if (isDay)
	{
		// if its day then there is a low chance of the enemy moving
		if (chanceToMove <= 3) y += direction; // increment y position by the direction		
	}
	else
	{
		// if it's night there is a very high chance enemy will move
		if (chanceToMove <= 9) y += direction;
	}

	return {x, y}; // return a pair, pretended x and y
}
