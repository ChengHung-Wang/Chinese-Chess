#pragma once
#include <iostream>
#include <string>
#include <vector>
#include "Chess.h"
#include "Viewer.h"
#include "Record.h"

class GameManager {

public:
	std::vector<Chess*> onBoard;
	ColorEnum currentPlayer = ColorEnum::Red;
	Board board;
	Viewer viewer;
	int rime = 600;
	int bTime = 600;
	std::vector<Record> record;

public:
	GameManager() {
		// 這樣測試
		General g(Position(4, 0), ColorEnum::Black);
		std::vector<Position> move = g.canMove(this->board);
	}

	void readFile();

};