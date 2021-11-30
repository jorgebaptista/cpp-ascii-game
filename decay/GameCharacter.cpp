#include "GameCharacter.h"

// use for creating character
GameCharacter::GameCharacter()
{
	// roll default stats for a character
	m_skill = ((rand() % 6) + 1) + 6; // roll 1 to 6 and add 6 (1 dice)
	m_maxStamina = ((rand() % 12) + 2) + 12; // roll 2 to 12 and add 12 (2 dice)
	m_currentStamina = m_maxStamina; // set current stamina as max stamina initially
	m_damage = 2;

	m_speed = 2;
	m_alive = true;

	// prevent warning
	m_typeID = type::ENEMY;
}

void GameCharacter::Stats()
{
	// print all stats to the screen
	std::cout << m_name << " current stats are -> Skill: " << m_skill << " Stamina: " << m_currentStamina << "/" << m_maxStamina;
}

void GameCharacter::HitWall()
{
	std::cout << "\n" << m_name << " has hit a wall and received: " << m_speed << " damage"; // print to screen
	m_currentStamina -= m_speed; // apply damage
}

bool GameCharacter::IsAlive()
{
	return m_currentStamina > 0; // return if current stamina is greater than 0
}

GameCharacter::type GameCharacter::getTypeID()
{
	return m_typeID; // return the type of this character for tile drawing purposes
}

int GameCharacter::RollSkill()
{
	int attackStrength = (rand() % 12) + 2; // get a number between 2 and 12 (2 dices)
	attackStrength += m_skill; // increment that number with current skill

	// print and return that number
	std::cout << m_name << " rolled an attack strength of " << attackStrength << "\n";
	return attackStrength;
}

void GameCharacter::Attack(GameCharacter* gameCharacter)
{
	std::cout << m_name << " has dealt " << m_damage << " damage to " << gameCharacter->getName() << "...\n"; // print that other character was attacked
	gameCharacter->TakeDamage(m_damage); // apply that damage
}

void GameCharacter::TakeDamage(int damage)
{
	// Reduce health by incoming damage
	m_currentStamina -= damage;

	// Check if health is 0 or negative
	if (m_currentStamina <= 0)
	{
		m_currentStamina = 0; // make sure current stamina does not drop below 0

		std::cout << m_name << " has been defeated!"; // print that this object was defeated
	}
}