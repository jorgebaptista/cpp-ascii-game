#include "Game.h"

Game::Game()
{
	// prevent warnings by initializing as empty pointers
	pWorld = nullptr;
	pPlayer = nullptr;

	deathScreen = FileSystem::instance().ReadDrawing("graphics/gameover.txt"); // get drawing from file
}

void Game::init(difficulty diff)
{
	// Default properties of game
	int minEnemies = 5;
	int maxEnemies = 10;
	int minRows = 13;
	int maxRows = 25;
	int minCols = 13;
	int maxCols = 25;
	int dayVisionRadius = 7;
	int nightVisionRadius = 4;
	int traps = 3;

	// change this properties depending on what difficulty player chose
	switch (diff)
	{
	case Game::difficulty::EASY:
		minEnemies = 4;
		maxEnemies = 7;
		minRows = 10;
		maxRows = 17;
		minCols = 13;
		maxCols = 20;
		dayVisionRadius = 8;
		nightVisionRadius = 5;
		traps = 2;
		break;
	case Game::difficulty::NORMAL:
		minEnemies = 7;
		maxEnemies = 12;
		minRows = 17;
		maxRows = 27;
		minCols = 17;
		maxCols = 27;
		dayVisionRadius = 7;
		nightVisionRadius = 4;
		traps = 4;
		break;
	case Game::difficulty::HARD:
		minEnemies = 15;
		maxEnemies = 25;
		minRows = 30;
		maxRows = 45;
		minCols = 30;
		maxCols = 45;
		dayVisionRadius = 6;
		nightVisionRadius = 3;
		traps = 7;
		break;
	default:
		break;
	}

	int totalEnemies = minEnemies + (rand() % (maxEnemies - minEnemies + 1)); // create a random total number of enemies
	int rows = minRows + (rand() % (maxRows - minRows + 1)); // get a random number between minRows and maxRows
	int cols = minCols + (rand() % (maxCols - minCols + 1)); // get a random number between minCols and maxCols

	pWorld = new World(rows, cols, dayVisionRadius, nightVisionRadius); // create world and pass the properties into it

	pPlayer = new Player(); // create new player
	pPlayer->setPosition(1, 1); // spawn it at row and column 1 (1, 1)
	lpGameCharacters.push_back(pPlayer); // push it into the game characters list
	pWorld->setTile(pPlayer);

	// get sizes of current world map - 1 because of walls on the bounds of the map
	int xMapSize = pWorld->getColTotal() - 2;
	int yMapSize = pWorld->getRowTotal() - 2;

	int rng = rand(); // generate random number

	std::vector<int> randomCols; // create a vector to store random unique numbers

	for (int i = 1; i < xMapSize; i++) // store numbers from 1 until total cols of map
	{
		randomCols.push_back(i); // push each number into the vector
	}

	std::random_shuffle(begin(randomCols), end(randomCols)); // randomize it

	for (int i = 0; i < totalEnemies; i++) // for each enemy number
	{
		GameCharacter* pEnemy = new Enemy(); // create a new enemy

		int x = randomCols[i]; // col will be random and unique for each enemy
		int y = 1 + rand() % (yMapSize); // get a random y depending on map size + 1 because of wall

		// while the tile at x and y is not empty, keep getting another random number
		while (pWorld->getTile(x, y)->getContent() != Tile::content::EMPTY)
		{
			// generate a new random col
			y = 1 + rand() % (yMapSize);
		}

		pEnemy->setPosition(x, y); // spawn enemy in those coordinates
		lpGameCharacters.push_back(pEnemy); // push enemy inside game character list
		pWorld->setTile(pEnemy); // set the tile this enemy is occupying to draw it
	}

	// create some equipment that will be randomly spawned around the map
	lpInteractables.push_back(new Equipment("Simple Sword", 2, 0, 0));
	lpInteractables.push_back(new Equipment("Lucky Necklace", 0, 0, 2));
	lpInteractables.push_back(new Equipment("Axe", 4, -2, 0));
	lpInteractables.push_back(new Equipment("Bulwark", -2, 15, -2));
	lpInteractables.push_back(new Equipment("Magic Sword", 10, -5, -3));
	lpInteractables.push_back(new Equipment("Magic Wand", 5, -1, -1));

	// create i traps based on player difficulty
	for (int i = 0; i < traps; i++)
	{
		lpInteractables.push_back(new Trap);
	}

	// creates iterator for Interactable list
	std::list<Interactable*>::const_iterator iter;
	// iterate through each element
	for (iter = lpInteractables.begin(); iter != lpInteractables.end(); iter++)
	{
		int x = 1 + rand() % (xMapSize); // get a random x depending on map size + 1 because of wall
		int y = 1 + rand() % (yMapSize); // get a random y depending on map size + 1 because of wall

		// while pretended position is not empty
		while (pWorld->getTile(x, y)->getContent() != Tile::content::EMPTY)
		{
			// generate a new random position
			x = 1 + rand() % (xMapSize);
			y = 1 + rand() % (yMapSize);
		}

		(*iter)->setPosition(x, y); // set this object position to the pretended position
		pWorld->setTile((*iter)); // set the tile this object is occupying to draw it
	}
}

void Game::Render(bool isDay)
{
	// add a blank line
	std::cout << "\n";

	pWorld->ClearTiles(); // clear all tiles of objects

	// creates an iterator for the list of characters
	std::list<GameCharacter*>::const_iterator iter;
	// iterate through each element
	for (iter = lpGameCharacters.begin(); iter != lpGameCharacters.end(); iter++)
	{
		pWorld->setTile((*iter)); // add character to its respective tile
	}

	// if list of interactables is not empty
	if (!lpInteractables.empty())
	{
		// creates an iterator for the list
		std::list<Interactable*>::const_iterator interactableIter;
		// iterate through each element
		for (interactableIter = lpInteractables.begin(); interactableIter != lpInteractables.end(); interactableIter++)
		{
			pWorld->setTile((*interactableIter)); // add object to its respective tile
		}
	}

	pWorld->DrawWorld(pPlayer, isDay); // redraw world and pass if its day or night

	std::cout << "\n"; // empty line

	pPlayer->Renderer(); // render player position
	pPlayer->Stats(); // show player current stats
}

void Game::Update(bool isDay)
{
	// create an iter for the list of game characters
	std::list<GameCharacter*>::const_iterator iter;

	// for each game character
	for (iter = lpGameCharacters.begin(); iter != lpGameCharacters.end(); iter++)
	{
		std::pair<int, int> position = (*iter)->Update(isDay); // call its update function and get the pretended position from it
		Tile* tile = pWorld->getTile(position.first, position.second); // get the tile at that position

		if (tile->getContent() == Tile::content::WALL) // check if that tile is a wall
		{
			(*iter)->HitWall(); // if it is then hit the wall receive damage
		}
		else if (tile->getContent() == Tile::content::MYSTERY) // if there is an Interactable here
		{
			if ((*iter) == pPlayer) // and current iter is player: means enemies wont move here
			{
				tile->getInteractable()->Interact(pPlayer); // interact with it
			}
		}
		else
		{
			(*iter)->setPosition(position.first, position.second); // means that tile is free to move in so put character at that tile
		}
	}

	if (!pPlayer->IsAlive())
	{
		GameOver(); // check if player is alive and if not calls GameOver
	}
}

void Game::Battle()
{
	std::list<GameCharacter*>::const_iterator iter; // iterator for the list of characters
	iter = lpGameCharacters.begin(); // set it to beginning of list

	// start the iteration skip the player
	for (advance(iter, 1); iter != lpGameCharacters.end(); iter++)
	{
		// if player position is same as current character
		if (pPlayer->getX() == (*iter)->getX() && pPlayer->getY() == (*iter)->getY())
		{
			// start battle
			std::cout << "\n\n================================";
			std::cout << "\n    BATTLE! " << pPlayer->getName() << " VS " << (*iter)->getName() << "\n";
			std::cout << "================================";

			int round = 1; // create round variable and set it to 1 initially

			(void)getchar(); // wait for player input

			while (pPlayer->IsAlive() && (*iter)->IsAlive())
			{
				// Prints current round
				std::cout << "\n\nRound " << round++ << "\n"; // print current round AND THEN increment

				(*iter)->Draw(); // draw enemy drawing

				std::cout << "\n";
				pPlayer->Stats(); // print player stats
				std::cout << "\n";
				(*iter)->Stats(); // print enemy stats

				std::cout << "\n\nPress enter to roll a dice..." << "\n";

				(void)getchar();

				int playerAttack = pPlayer->RollSkill(); // roll attack strength
				int enemyAttack = (*iter)->RollSkill();

				(void)getchar();

				// Check who gets the highest attack strength
				if (playerAttack > enemyAttack)
				{
					// Calls the function attack and passes the other game character object as an argument
					pPlayer->Attack(*iter);

					// if player has luck left and enemy is alive
					if (pPlayer->getLuck() > 0 && (*iter)->IsAlive())
					{
						std::cout << "\nDo you want to roll a luck check?";
						if (pPlayer->Ask()) // ask player yes or no question
						{
							bool luckSuccess = pPlayer->RollLuck(); // create a bool to store if luck was successful and roll luck from player

							if (luckSuccess) // if player is lucky
							{
								std::cout << "\nLuck check successful!\n" << (*iter)->getName() << " received an additional 2 damage...";
								(*iter)->TakeDamage(2); // enemy takes additional 2 damage
							}
							else
							{
								std::cout << "\nLuck check unsuccessful.\n" << (*iter)->getName() << " recovered 1 stamina...";
								(*iter)->TakeDamage(-1); // enemy recovers 1 point
							}

							(void)getchar();
						}
					}
				}
				// same thing but if enemy attacks player instead
				else if (playerAttack < enemyAttack)
				{
					(*iter)->Attack(pPlayer);

					if (pPlayer->getLuck() > 0)
					{
						std::cout << "\nDo you want to roll a luck check?";
						if (pPlayer->Ask())
						{
							bool luckSuccess = pPlayer->RollLuck();

							if (luckSuccess) // if player is lucky
							{
								std::cout << "\nLuck check successful!\n" << pPlayer->getName() << " recovered 1 stamina...";
								pPlayer->TakeDamage(-1); // player recovers 1 point
							}
							else
							{
								std::cout << "\nLuck check unsuccessful.\n" << pPlayer->getName() << " received an additional 1 damage...";
								pPlayer->TakeDamage(1); // player takes 1 additional damage
							}

							(void)getchar();
						}
					}
				}
				else // if both rolled same attack strength skip turn
				{
					std::cout << "It's a draw! Skip turn...";
				}

				(void)getchar();

				std::cout << "\n================================";
			}

			// check if player is alive
			if (pPlayer->IsAlive())
			{
				pPlayer->Draw(); // if victorious draw player drawing
				std::cout << "\n\n" << pPlayer->getName() << " is victorious!";
				(void)getchar();
			}
			else
			{
				GameOver(); // if died on battle show gameover screen and end game
			}

			break;
		}
	}
}

void Game::Clean()
{
	std::list<GameCharacter*>::const_iterator iter;
	for (iter = lpGameCharacters.begin(); iter != lpGameCharacters.end(); iter++)
	{
		// check if its alive
		if (!(*iter)->IsAlive())
		{
			// erase this element from the list
			lpGameCharacters.erase(iter);
			// restart the iterator
			iter = lpGameCharacters.begin();
		}
	}

	// if list of interactables is not empty
	if (!lpInteractables.empty())
	{
		// creates an iterator for the list
		std::list<Interactable*>::const_iterator interactableIter;
		// iterate through each element
		for (interactableIter = lpInteractables.begin(); interactableIter != lpInteractables.end(); interactableIter++)
		{
			// if this object was used
			if ((*interactableIter)->wasUsed())
			{
				lpInteractables.erase(interactableIter); // erase it from list
				if (!lpInteractables.empty()) interactableIter = lpInteractables.begin(); // restart the iterator
			}
		}
	}
}

void Game::GameOver()
{
	std::cout << "\n\n==============================================================";
	std::cout << "\n\n" << deathScreen << "\n\n\n\nGAME OVER........"; // show death screen
	std::cout << "\n\n==============================================================\n\n";
	exit(0); // exits game
}
