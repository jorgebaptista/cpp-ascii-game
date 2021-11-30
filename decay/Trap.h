#pragma once
#ifndef TRAP_H
#define TRAP_H
#include "Interactable.h"
class Trap : public Interactable
{
public:
	Trap(); // constructor to set drawing and other properties
	void Interact(Player* pPlayer) override; // override interact from interactable class

};
#endif // !TRAP
