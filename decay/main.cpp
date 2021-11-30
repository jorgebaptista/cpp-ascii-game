
#include <cstdlib>
#include <ctime>
#include <random>
#include "Game.h"

int main()
{
	srand(static_cast<unsigned int>(time(0)));

	std::string titleDrawing = FileSystem::instance().ReadDrawing("graphics/title.txt"); // get title drawing from text file

	Game game; // create game object

	std::cout << titleDrawing; // draw the title
	
	std::cout << "\n\n\n\nPress Enter to start game!";
	(void)getchar();

	std::cout << "\n\nWhat difficulty do you want to play?";

	bool inputGiven = false; // create variable to store if player wants to roll luck or not
	Game::difficulty diff = Game::difficulty::NORMAL;

	while (!inputGiven) // input not given
	{
		// explanation
		std::cout << "\nE - Easy, N - Normal, H - Hard: ";

		// create local variable for user input
		std::string input;
		std::cin >> input;
		// convert it to lowercase for shorter switch statement
		input = std::tolower(input[0]);

		// check player input and increment x or y depending if player choose north, south, east or west
		switch (input[0])
		{
		case 'e':
			inputGiven = true;
			diff = Game::difficulty::EASY;
			break;
		case 'n':
			inputGiven = true;
			diff = Game::difficulty::NORMAL;
			break;
		case 'h':
			inputGiven = true;
			diff = Game::difficulty::HARD;
			break;
		default:
			// wrong input check, loop again
			std::cout << "\nInput invalid. Please reply with one of these characters: ";
			break;
		}
	}

	// initial story of the game
	std::cout << "\n\nOnce upon a time there was a village ridden with foul creatures.";
	(void)getchar();
	std::cout << "These creatures have tormented the good people of this world for too long.";
	(void)getchar();
	std::cout << "One day a hero made a oath to the king that he would rid this village of evil.";
	(void)getchar();
	std::cout << "And finally bring peace.";
	(void)getchar();
	std::cout << "\nThat's when you arrive...";
	(void)getchar();

	// initiate game and pass the player chosen difficulty
	game.init(diff);

	// create variables for day and hour and initialize as 0
	int day = 0;
	int currentHour = 0;
	int hoursPerDay = 12; // how many hours from day to night

	bool isDay = true; // start the game as day

	while (true)
	{
		// print current day, hour and day or night enemy settings depending if its day or night
		std::cout << std::endl;
		std::cout << " ======================================";
		std::cout << "\n             " << (isDay? "Day": "Night") << " " << day << " Hour " << currentHour;
		std::cout << "\n ======================================";
		game.Render(isDay); // render map and pass if it's currently day or not
		std::cout << "\n\n" << (isDay ? "It's day time... Enemies are weaker and move slower." : "It's night time... Enemies are stronger and move faster.");
		game.Update(isDay); // update all characters and pass if it's currently day or not
		game.Battle(); // call battle function to check if player is in same position as an enemy
		game.Clean(); // clean all dead of used objects

		// check if current hour is over 12 AND THEN increment it
		if (currentHour++ == hoursPerDay)
		{
			isDay = !isDay; // day toggle

			if (isDay)
			{
				day++; // increment day if it's day time
			}

			currentHour = 0; // set current hour back to 0, restart it
		}
	}

	(void)getchar();
	return 0;
}