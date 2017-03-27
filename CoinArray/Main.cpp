// CoinArray.cpp : Defines the entry point for the console application.
//

#include <iostream>

#include "stdafx.h"
#include "Input.hh"
#include "Map.hh"
#include "CoinManager.hh"
#include "Player.hh"


int difficulty;
int coinsToWin;
Input::Key key = Input::Key::NONE;

// Color
HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);
enum class Color
{
	BLACK,
	LOW_BLUE,
	GREEN,
	HIGH_BLUE,
	RED,
	PURPLE,
	YELLOW,
	WHITE,
	GRAY,
	LOW_BLUE_BRIGHT,
	GREEN_BRIGHT,
	HIGH_BLUE_BRIGHT,
	RED_BRIGHT,
	PURPLE_BRIGHT,
	YELLOW_BRIGHT,
	WHITE_BRIGHT,
};

// Prints a string / int with the desired color.
void printWithColor(const Color &_color, std::string _text, bool _endl)
{
	SetConsoleTextAttribute(h, (int)_color);	// Sets new color
	std::cout << _text;							// Prints string
	SetConsoleTextAttribute(h, 7);				// Sets default color

	if (_endl)
	{
		std::cout << std::endl;
	}
}
void printWithColor(const Color &_color, int _text, bool _endl)
{
	SetConsoleTextAttribute(h, (int)_color);	// Sets new color
	std::cout << _text;							// Prints string
	SetConsoleTextAttribute(h, 7);				// Sets default color

	if (_endl)
	{
		std::cout << std::endl;
	}
}

// Draws the Starting Menu Header.
void drawMenuHeader()
{
	printWithColor(Color::YELLOW, "///////////////////////////", true);
	printWithColor(Color::WHITE_BRIGHT, "         COIN RACE", true);
	printWithColor(Color::YELLOW, "///////////////////////////", true);
	std::cout << std::endl;
}

// Clamps difficulty between 1 and 3.
void setDifficulty(int _difficulty)
{
	if (_difficulty < 1)
	{
		difficulty = 1;
	}
	else if (_difficulty > 3)
	{
		difficulty = 3;
	}
	else
	{
		difficulty = _difficulty;
	}
}

// Calculates the amount of coins needed to win.
void calculateCoinsToWin(const int &_difficulty)
{
	int min{ 30 * _difficulty };
	int max{ 30 * _difficulty * 2 };

	int random{ (rand() % (max - min)) + min };

	coinsToWin = random;
}

// Asks the user to introduce the difficulty value.
void askDifficulty()
{
	printWithColor(Color::WHITE, "Chose a difficulty:", true);
	std::cout << std::endl;
	printWithColor(Color::GREEN_BRIGHT, "1 - EASY", true);
	printWithColor(Color::YELLOW_BRIGHT, "2 - MEDIUM", true);
	printWithColor(Color::RED_BRIGHT, "3 - HARD", true);
	std::cout << std::endl;
	
	// Difficulty input.
	int var;
	std::cin >> var;
	setDifficulty(var);
	calculateCoinsToWin(difficulty);

	// Objective coins print

	std::cout << std::endl;
	printWithColor(Color::WHITE_BRIGHT, "Controls: ", false);
	printWithColor(Color::GRAY, "Use ", false);
	printWithColor(Color::HIGH_BLUE_BRIGHT, "WASD ", false);
	printWithColor(Color::GRAY, "to move the player!", true);

	std::cout << std::endl;
	printWithColor(Color::WHITE_BRIGHT, "Objective: ", false);
	printWithColor(Color::GRAY, "You have to pick up ", false);
	printWithColor(Color::HIGH_BLUE_BRIGHT, coinsToWin, false);
	printWithColor(Color::GRAY, " coins!", true);
	std::cout << std::endl;
	printWithColor(Color::GRAY, "Press ", false);
	printWithColor(Color::HIGH_BLUE_BRIGHT, "ENTER", false);
	printWithColor(Color::GRAY, " to ", false);
	printWithColor(Color::WHITE_BRIGHT, "start!", true);
	do
	{
		key = Input::getKey();
	} while (key != Input::Key::ENTER);
}

// Draws a "////" spacer with the map size.
void drawSpacer(Map map)
{
	for (int i = 0; i < map.getNumColumns(); i++)
	{
		if (i == map.getNumColumns() - 1)
		{
			printWithColor(Color::YELLOW, "/", false);
		}
		else
		{
			printWithColor(Color::YELLOW, "//", false);
		}
	}

	std::cout << std::endl;
}

// Draws a Game Header with the map size.
void drawGameHeader(Map map)
{
	drawSpacer(map);

	// Title "COIN RACE" centered depending on map size.
	int titleOffset = 2;
	for (int i = 0; i < (map.getNumColumns() / 2 - titleOffset); i++)
	{
		if(map.getNumColumns() % 2 != 0)
			std::cout << "  ";
		else
		{
			if (i < (map.getNumColumns() / 2 - titleOffset) - 1)
				std::cout << "  ";
			else
				std::cout << " ";
		}
	}

	printWithColor(Color::WHITE_BRIGHT, "COIN RACE", true);
	
	drawSpacer(map);
}

// Draws the Game Header, the Map and the Player Score.
void drawGame(Map& map, Player& player)
{
	system("cls");

	drawGameHeader(map);

	map.draw();

	drawSpacer(map);

	std::cout << std::endl;
	printWithColor(Color::PURPLE_BRIGHT, "Score: ", false);
	printWithColor(Color::HIGH_BLUE_BRIGHT, player.getScore(), false);
	printWithColor(Color::PURPLE_BRIGHT, " / ", false);
	printWithColor(Color::HIGH_BLUE_BRIGHT, coinsToWin, true);
	std::cout << std::endl;

	drawSpacer(map);
}


// ----- MAIN -----
void main()
{	
	// Seed
	srand(time(nullptr));

	// Initial header draw
	drawMenuHeader();

	// Difficulty selection logic / draw
	askDifficulty();
	
	// Class instances
	Map map(difficulty);
	CoinManager coinManager(map);
	Player player(map, coinManager);

	// Initial game draw
	drawGame(map, player);
	
	// Game loop
	bool mainLoop = true;
	bool gameLoop = true;
	bool resultPrinted = false;

	bool startTimeBool = false;
	clock_t clockTime; 
	int startTime = 0;
	
	while (mainLoop)
	{
		while (gameLoop)
		{
			if (!startTimeBool)
			{
				startTime = clock();
				startTimeBool = true;
			}

			clockTime = clock();

			gameLoop = (key == Input::Key::ESC || player.getScore() >= coinsToWin) ? false : true;
			mainLoop = (key == Input::Key::ESC) ? false : true;

			do
			{
				key = Input::getKey();
			} 
			while (key == Input::Key::NONE && gameLoop);

			player.move(key);

			drawGame(map, player);		
		}

		if (mainLoop)
		{
			if (!resultPrinted)
			{
				std::cout << std::endl;
				printWithColor(Color::WHITE, "You've picked up ", false);
				printWithColor(Color::HIGH_BLUE_BRIGHT, coinsToWin, false);
				printWithColor(Color::WHITE, " coins in ", false);
				printWithColor(Color::HIGH_BLUE_BRIGHT, (clockTime - startTime) / 1000.0f, false);
				printWithColor(Color::WHITE, " seconds!", true);
				resultPrinted = true;


				Beep(300, 100);
				Beep(400, 100);
				Beep(500, 100);
				Beep(600, 100);
				Beep(0, 70);
				Beep(540, 100);
				Beep(600, 700);
			}

			do
			{
				key = Input::getKey();
			} 
			while (key == Input::Key::NONE);

			mainLoop = (key == Input::Key::ESC) ? false : true;
		}
	}
}