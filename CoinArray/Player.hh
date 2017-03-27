#pragma once
#include "Map.hh"
#include "CoinManager.hh"
#include "Input.hh"

class Player
{
private:

	// Attributes

	Map &map;
	CoinManager &coinManager;

	int posX, posY;
	int score;

	// Position Methods
	void updatePosition(int x, int y);
	void updatePositionBy(int x, int y);

public:

	// Constructors		
	Player(Map& map1, CoinManager& coinManager1);

	// Destructors
	~Player();

	// Setter

	// Getters
	int getPositionX();
	int getPositionY();
	int getScore();

	// Score Methods
	void move(Input::Key key);
};

