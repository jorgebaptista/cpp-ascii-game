#include "Equipment.h"

Equipment::Equipment(std::string name, int skill, int stamina, int luck)
{
	m_drawing = FileSystem::instance().ReadDrawing("graphics/chest.txt"); // set drawing

	m_name = name; // set current name
	m_skill = skill; // set bonus skill of this object
	m_stamina = stamina; // set bonus stamina of this object
	m_luck = luck; // set bonus luck of this object

	m_used = false; // currently not used when created
}

void Equipment::Interact(Player* pPlayer)
{
	Draw(); // draw this object drawing
	std::cout << "\nYou found a " << m_name << "!"; // print to screen this object name

	m_used = pPlayer->Equip(this); // ask player to equip this and assign answer to m_used
}

void Equipment::Stats()
{
	std::cout << "\n" << m_name << " bonus stats are -> Skill: " << m_skill << " Stamina: " << m_stamina << " Luck: " << m_luck; // print bonus stats
}

int Equipment::getSkill()
{
	return m_skill;
}

int Equipment::getStamina()
{
	return m_stamina;
}

int Equipment::getLuck()
{
	return m_luck;
}
