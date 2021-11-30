#include "Trap.h"

Trap::Trap()
{
	m_drawing = FileSystem::instance().ReadDrawing("graphics/trap.txt"); // get the trap drawing from the text file

	m_used = false; // initially not used
}

void Trap::Interact(Player* pPlayer)
{
	Draw(); // draw trap
	std::cout << "\n\nOh no! It was a trap!";

	pPlayer->TakeDamage(4); // player takes 4 damage from this trap

	std::cout << "\nPlayer received 4 damage... ";
	std::cout << "\nDo you wanna roll a luck check?";

	// ask player if he wants to roll a luck check
	if (pPlayer->Ask())
	{
		bool luckSuccess = pPlayer->RollLuck(); // roll luck

		if (luckSuccess) // if player is lucky
		{
			std::cout << "\nLuck check successful!\n" << pPlayer->getName() << " recovered 2 stamina...";
			pPlayer->TakeDamage(-2); // player recovers 2 point
		}
		else
		{
			std::cout << "\nLuck check unsuccessful.\n" << pPlayer->getName() << " received an additional 1 damage...";
			pPlayer->TakeDamage(1); // player takes 1 additional damage
		}

		(void)getchar();
		(void)getchar();
	}

	m_used = true;
}
