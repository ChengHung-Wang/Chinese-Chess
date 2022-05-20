#pragma once 
#include <vector>
#include <string>
#include "Position.h"

enum class ColorEnum : int {
	Red = 1,
	Black = 2
};

enum class ChessEnum : int {
	General = 1, //將/帥
	Advisor = 2, //士/仕
	Elephant = 3, //象/相
	Horse = 4, //馬/傌
	Chariot = 5, //車/俥
	Cannon = 6, //砲/炮
	Soldier = 7 //卒/兵
};

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

class Chess {

public:
	Position pos;
	ColorEnum color;
	ChessEnum id;
	std::string chessName;
	std::string enName;

public:
	Chess();
	Chess(Position pos, ColorEnum color, ChessEnum id);

	std::string move(Board& board, Position& fromPos, Position& toPos);

	virtual std::vector<Position> canMove(Board& board) = 0;
	virtual std::vector<Position> canEat(Board& board) = 0;

};

class  General :public Chess {

public:
	General(Position pos, ColorEnum color);

	std::vector<Position> canMove(Board& board);
	std::vector<Position> canEat(Board& board);

};

class Advisor :public Chess {

public:
	Advisor(Position pos, ColorEnum color);

	std::vector<Position> canMove(Board& board);
	std::vector<Position> canEat(Board& board);

};

class Elephant :public Chess {

public:
	Elephant(Position pos, ColorEnum color);

	std::vector<Position> canMove(Board& board);
	std::vector<Position> canEat(Board& board);

};

class Chariot :public Chess {

public:
	Chariot(Position pos, ColorEnum color);

	std::vector<Position> canMove(Board& board);
	std::vector<Position> canEat(Board& board);

};

class Horse :public Chess {

public:
	Horse(Position pos, ColorEnum color);

	std::vector<Position> canMove(Board& board);
	std::vector<Position> canEat(Board& board);

};

class Cannon :public Chess {

public:
	Cannon(Position pos, ColorEnum color);

	std::vector<Position> canMove(Board& board);
	std::vector<Position> canEat(Board& board);

};

class Soldier :public Chess {

public:
	Soldier(Position pos, ColorEnum color);

	std::vector<Position> canMove(Board& board);
	std::vector<Position> canEat(Board& board);

};