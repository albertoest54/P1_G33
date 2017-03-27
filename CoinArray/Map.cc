#include <iostream>

#include "stdafx.h"
#include "Map.hh"

void Map::initialize()
{
	mapCells = new char*[numRows];

	for (int i = 0; i < numRows; i++)
	{
		mapCells[i] = new char[numColumns];
	}
}

void Map::fill()
{
	for (int i = 0; i < numRows; i++)
	{
		for (int j = 0; j < numColumns; j++)
		{
			mapCells[i][j] = skin::empty;
		}
	}
}

Map::Map(const int difficulty) : h (GetStdHandle(STD_OUTPUT_HANDLE))
{
	int min{ 5 * difficulty };
	int max{ 5 * difficulty * 2 };

	int random{ (rand() % (max-min)) + min };

	numRows = random;
	numColumns = random;

	initialize();
	fill();
}

Map::~Map()
{
	/*
	for (int i{ 0 }; i < numRows; i++)
	{
		delete[] mapCells[i];
	}
	mapCells = nullptr;
	*/
}

void Map::setCell(const int &row, const int &column, const char &value)
{
	mapCells[row][column] = value;
}

int Map::getNumRows()
{
	return numRows;
}

int Map::getNumColumns()
{
	return numColumns;
}

int Map::getMapSize()
{
	return numRows * numColumns;
}

char Map::getCell(const int &row, const int &column)
{
	return mapCells[row][column];
}

void Map::draw()
{
	for (int i = 0; i < numRows; i++)
	{
		for (int j = 0; j < numColumns; j++)
		{
			if (mapCells[i][j] == skin::empty)
			{
				SetConsoleTextAttribute(h, 1);     // Set color font to GRAY
				std::cout << mapCells[i][j] << " ";
			}
			else if (mapCells[i][j] == skin::coin)
			{
				SetConsoleTextAttribute(h, 6);   // Set color font to YELLOW_BRIGHT
				std::cout << mapCells[i][j] << " ";
			}
			else if (mapCells[i][j] == skin::player)
			{
				SetConsoleTextAttribute(h, 10);   // Set color font to GREEN_BRIGHT
				std::cout << mapCells[i][j] << " ";
			}
		}
		std::cout << std::endl;
	}
}

