#pragma once

#include "Map.hh"

class CoinManager
{
private:

	// Attributes
	Map &map;
	int coinCounter;

	// Methods
	void fill();

public:

	// Constructors
	CoinManager(Map& map1);

	// Destructors
	~CoinManager();

	// Getter

	// Setter
	void setCointCounter(const int coinCounter);

	// Methods
	void decreaseCoinCounter();
};

