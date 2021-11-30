#include "Player.h"
#include "Equipment.h"

Player::Player()
{
	m_typeID = GameCharacter::type::PLAYER; // set type of this character as a player for tile drawing purposes
	m_name = "Player"; // set its name as Player

	m_maxLuck = ((rand() % 6) + 1) + 6; // roll 1 to 6 and add 6
	m_currentLuck = m_maxLuck; // assign current luck as max luck initially

	m_equipment = nullptr; // initially nothing is equipped so make this pointer empty

	std::cout << "\n\n";
	m_drawing = FileSystem::instance().ReadDrawing("graphics/player.txt"); // get player drawing from file
	Draw(); // draw the player

	std::cout << "\n\nPlayer created with Skill: " << m_skill << " Stamina: " << m_currentStamina << " Luck: " << m_currentLuck; // and print its stats

	(void)getchar(); // wait for player input
}

std::pair<int, int> Player::Update(bool isDay)
{
	int x = m_x; // set pretended x to current x
	int y = m_y; // set pretended y to current y

	// ask player for input
	std::cout << "\n\nPlease type one of the following characters to move:";

	// create a bool variable to check if user has given input
	bool inputGiven = false;

	while (!inputGiven) // input not given
	{
		// explanation
		std::cout << "\nN - North, S - South, E - East or W - West: ";

		// create local variable for user input
		std::string input;
		std::cin >> input;
		// convert it to lowercase for shorter switch statement
		input = std::tolower(input[0]);

		// check player input and increment x or y depending if player choose north, south, east or west
		switch (input[0])
		{
		case 'n':
			y--;
			inputGiven = true;
			break;
		case 's':
			y++;
			inputGiven = true;
			break;
		case 'e':
			x++;
			inputGiven = true;
			break;
		case 'w':
			x--;
			inputGiven = true;
			break;
		default:
			// wrong input check, loop again
			std::cout << "\nInput invalid. Please reply with one of these characters: ";
			break;
		}
	}

	return { x, y }; // return a pair, pretended x and y
}

void Player::Stats()
{
	// call base class Stats()
	GameCharacter::Stats();

	// also print the luck stats
	std::cout << " Luck: " << m_currentLuck << "/" << m_maxLuck;
}

bool Player::Ask()
{
	bool inputGiven = false; // create variable to check if input was given
	bool want = false; // create variable to store if player wants to roll luck or not

	while (!inputGiven) // input not given
	{
		// explanation
		std::cout << "\nY - Yes, N - No: ";

		// create local variable for user input
		std::string input;
		std::cin >> input;
		// convert it to lowercase for shorter switch statement
		input = std::tolower(input[0]);

		// check player input and increment x or y depending if player choose north, south, east or west
		switch (input[0])
		{
		case 'n':
			want = false;
			inputGiven = true;
			break;
		case 'y':
			want = true;
			inputGiven = true;
			break;
		default:
			// wrong input check, loop again
			std::cout << "\nInput invalid. Please reply with one of these characters: ";
			break;
		}
	}

	return want; // return if answer was yes or no
}

bool Player::RollLuck()
{
	int luck = (rand() % 12) + 2; // roll 2 dices
	bool isLucky = luck <= m_currentLuck; // if current luck greater than rolled luck it was lucky!

	m_currentLuck--; // decrement current luck

	return isLucky;
}

int Player::getLuck()
{
	return m_currentLuck;
}

bool Player::Equip(Equipment* equipment)
{
	if (m_equipment == nullptr) // if nothing is equipped
	{
		equipment->Stats();
		std::cout << "\nDo you wish to equip it?";
	}
	else // if there is something equipped
	{
		std::cout << "\nYou already have " << m_equipment->getName() << " equipped.";
		equipment->Stats();
		m_equipment->Stats(); // print stats to compare

		std::cout << "\nDo you wish to replace " << m_equipment->getName() << " with " << equipment->getName() << "? (" << m_equipment->getName() << " will be destroyed)"; // ask player if he wanted to replace
	}

	bool equipped = Ask(); // ask yes or no question

	if (equipped) // if answer was yes
	{
		if (m_equipment != nullptr) // if something was equipped
		{
			// remove the bonus stats
			m_skill -= m_equipment->getSkill();
			m_maxStamina -= m_equipment->getStamina();
			m_maxLuck -= m_equipment->getLuck();
		}

		// add new bonus stats
		m_skill += equipment->getSkill();
		m_maxStamina += equipment->getStamina();
		m_maxLuck += equipment->getLuck();

		if (equipment->getStamina() > 0) m_currentStamina += equipment->getStamina(); // only increment current by bonus if its not a negative number
		if (equipment->getLuck() > 0) m_currentLuck += equipment->getLuck();

		// make sure current stats are not over the limit
		if (m_currentStamina > m_maxStamina)
		{
			m_currentStamina = m_maxStamina;
		}
		if (m_currentLuck > m_maxLuck)
		{
			m_currentLuck = m_maxLuck;
		}

		m_equipment = equipment; // assign the new equipment to current equipment
	}

	return equipped; // return if player decided to equip or not
}
