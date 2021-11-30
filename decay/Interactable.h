#pragma once
#ifndef INTERACTABLE_H
#define INTERACTABLE_H

#include "GameObject.h"
#include "Player.h"
#include <iostream>

class Interactable : public GameObject
{
public:
	virtual void Interact(Player* pPlayer) = 0; // pure virtual so that it can be overridden in derived classes

	bool wasUsed(); // check if this was already used to delete from list

protected:
	bool m_used;
};
#endif // !INTERACTABLE