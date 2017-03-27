#pragma once

#include <iostream>

#include "stdafx.h"

class Map
{
private:

	// Attributes
	char **mapCells;
	int numRows;
	int numColumns;

	// Colors
	HANDLE h;	

	// Methods
	void initialize();
	void fill();

public:

	// Struct with static skins

	struct skin
	{
		static const char empty = '.';
		static const char coin = '$';
		static const char player = '@';
	};

	// Constructors
	Map(const int difficulty);

	// Destructors
	~Map();

	// Setter
	void setCell(const int &row, const int &column, const char &value);

	// Getter
	int getNumRows();
	int getNumColumns();
	int getMapSize();
	char getCell(const int &row, const int &column);

	// Methods
	void draw();
};

