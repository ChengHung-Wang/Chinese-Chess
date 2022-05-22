#pragma once
#include "ColorEnum.h"
#include "Position.h"

class Board {

public:
	int board[10][9] = {
		{-5, -4, -3, -2, -1, -2, -3, -4, -5},
		{0, 0, 0, 0, 0, 0, 0, 0, 0},
		{0, -6, 0, 0, 0, 0, 0, -6, 0},
		{-7, 0, -7, 0, -7, 0, -7, 0, -7},
		{0, 0, 0, 0, 0, 0, 0, 0, 0},
		{0, 0, 0, 0, 0, 0, 0, 0, 0},
		{7, 0, 7, 0, 7, 0, 7, 0, 7},
		{0, 6, 0, 0, 0, 0, 0, 6, 0},
		{0, 0, 0, 0, 0, 0, 0, 0, 0},
		{5, 4, 3, 2, 1, 2, 3, 4, 5},
	};

public:
	bool applyMove(Position pos, ColorEnum color);
	bool applyEat(Position pos, ColorEnum color);

};