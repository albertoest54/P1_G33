#include <stdlib.h>
#include <time.h>

#include "stdafx.h"
#include "CoinManager.hh"


void CoinManager::fill()
{
	int percentage = (rand() % 10) + 3;

	coinCounter = (map.getMapSize() / 100.0f) * percentage;
	if (coinCounter < 1)
		coinCounter = 1;

	for (int i = 0; i < coinCounter; i++)
	{
		int row = rand() % map.getNumRows();
		int column = rand() % map.getNumColumns();

		if (map.getCell(row, column) == Map::skin::empty)
		{
			map.setCell(row, column, Map::skin::coin);
		}
		else
		{
			i--;
		}
	}
}

CoinManager::CoinManager(Map& map1) : map( map1 )
{
	fill();
}

CoinManager::~CoinManager()
{

}

void CoinManager::setCointCounter(int coinCounter1)
{
	coinCounter = coinCounter1;
}

void CoinManager::decreaseCoinCounter()
{
	if (coinCounter > 0)
	{
		coinCounter--;
		if(coinCounter == 0)
			fill();
	}
}
