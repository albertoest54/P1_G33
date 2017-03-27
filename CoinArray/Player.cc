#include "stdafx.h"
#include "Player.hh"
#include "Input.hh"

void Player::updatePosition(int x, int y)
{
	// Restrinct movement

	if (x >= 0 && x < map.getNumColumns() && y >= 0 && y < map.getNumRows())
	{
		// Set background cell with background sking

		map.setCell(posY, posX, Map::skin::empty);

		// Update position

		posX = x;
		posY = y;

		// Check if coin

		if (map.getCell(posY, posX) == Map::skin::coin)
		{
			// Coin recollection sound
			Beep(6000, 5);
			Beep(4000, 10);

			coinManager.decreaseCoinCounter();

			score++;
		}

		// Set new cell with player skin

		map.setCell(posY, posX, Map::skin::player);	
	}
}

void Player::updatePositionBy(int x, int y)
{
	updatePosition(posX + x, posY + y);
}

Player::Player(Map& map1, CoinManager& coinManager1) : map( map1 ), coinManager( coinManager1 ), score(0)
{
	do
	{
		posX = rand() % map.getNumColumns();
		posY = rand() % map.getNumRows();
	} 
	while (map.getCell(posY, posX) == Map::skin::coin);

	map.setCell(posY, posX, Map::skin::player);
};

Player::~Player()
{

}

int Player::getPositionX()
{
	return posX;
}

int Player::getPositionY()
{
	return posY;
}

int Player::getScore()
{
	return score;
}

void Player::move(Input::Key key)
{
	switch (key)
	{
	case Input::Key::W:

		updatePositionBy(0, -1);

		break;

	case Input::Key::S:

		updatePositionBy(0, 1);

		break;

	case Input::Key::A:

		updatePositionBy(-1, 0);

		break;

	case Input::Key::D:

		updatePositionBy(1, 0);

		break;
	}
}
