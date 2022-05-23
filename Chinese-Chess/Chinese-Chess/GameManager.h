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
	int rTime = 600;
	int bTime = 600;
	std::vector<Record> record;

public:
	GameManager() {
		onBoard.push_back(new General(Position(4, 0), ColorEnum::Black));
		onBoard.push_back(new Advisor(Position(3, 0), ColorEnum::Black));
		onBoard.push_back(new Advisor(Position(5, 0), ColorEnum::Black));
		onBoard.push_back(new Elephant(Position(2, 0), ColorEnum::Black));
		onBoard.push_back(new Elephant(Position(6, 0), ColorEnum::Black));
		onBoard.push_back(new Horse(Position(1, 0), ColorEnum::Black));
		onBoard.push_back(new Horse(Position(7, 0), ColorEnum::Black));
		onBoard.push_back(new Chariot(Position(0, 0), ColorEnum::Black));
		onBoard.push_back(new Chariot(Position(8, 0), ColorEnum::Black));
		onBoard.push_back(new Cannon(Position(1, 2), ColorEnum::Black));
		onBoard.push_back(new Cannon(Position(7, 2), ColorEnum::Black));
		onBoard.push_back(new Soldier(Position(0, 3), ColorEnum::Black));
		onBoard.push_back(new Soldier(Position(2, 3), ColorEnum::Black));
		onBoard.push_back(new Soldier(Position(4, 3), ColorEnum::Black));
		onBoard.push_back(new Soldier(Position(6, 3), ColorEnum::Black));
		onBoard.push_back(new Soldier(Position(8, 3), ColorEnum::Black));

		onBoard.push_back(new General(Position(4, 9), ColorEnum::Red));
		onBoard.push_back(new Advisor(Position(3, 9), ColorEnum::Red));
		onBoard.push_back(new Advisor(Position(5, 9), ColorEnum::Red));
		onBoard.push_back(new Elephant(Position(2, 9), ColorEnum::Red));
		onBoard.push_back(new Elephant(Position(6, 9), ColorEnum::Red));
		onBoard.push_back(new Horse(Position(1, 9), ColorEnum::Red));
		onBoard.push_back(new Horse(Position(7, 9), ColorEnum::Red));
		onBoard.push_back(new Chariot(Position(0, 9), ColorEnum::Red));
		onBoard.push_back(new Chariot(Position(8, 9), ColorEnum::Red));
		onBoard.push_back(new Cannon(Position(1, 7), ColorEnum::Red));
		onBoard.push_back(new Cannon(Position(7, 7), ColorEnum::Red));
		onBoard.push_back(new Soldier(Position(0, 6), ColorEnum::Red));
		onBoard.push_back(new Soldier(Position(2, 6), ColorEnum::Red));
		onBoard.push_back(new Soldier(Position(4, 6), ColorEnum::Red));
		onBoard.push_back(new Soldier(Position(6, 6), ColorEnum::Red));
		onBoard.push_back(new Soldier(Position(8, 6), ColorEnum::Red));
	}

	std::string setFile(std::string hash);
	std::string setNew(std::string hash);
	std::string getRound();
	std::string getMove(ColorEnum color, ChessEnum chessId, int x, int y, std::string hash);
	std::string getTime(int color, std::string hash);
	std::string save(std::string hash);
	void move(ColorEnum color, ChessEnum chessId, int fromX, int fromY, int toX, int toY, std::string hash);

};