#pragma once
#ifndef EQUIPMENT_H
#define EQUIPMENT_H
#include "Interactable.h"
class Equipment : public Interactable
{
public:
	Equipment(std::string name, int skill, int stamina, int luck);
	void Interact(Player* pPlayer) override;
	void Stats(); // print stat bonuses of this equipment

	int getSkill(); // get the skill bonus
	int getStamina(); // get the stam bonus
	int getLuck(); // get the luck bonus

protected:
	int m_skill;
	int m_stamina;
	int m_luck;
};
#endif // !EQUIPMENT
