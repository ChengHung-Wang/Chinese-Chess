#pragma once 
#include <vector>
#include <string>
#include "Position.h"
#include "Board.h"

enum class ColorEnum : int {
	Red = 1,
	Black = 2
};

enum class ChessEnum : int {
	General = 1, //將/帥
	Advisor = 2, //士/仕
	Elephant = 3, //象/相
	Chariot = 4, //車/俥
	Horse = 5, //馬/傌
	Cannon = 6, //砲/炮
	Soldier = 7 //卒/兵
};

class Chess {

public:
	Position pos;
	ColorEnum color;
	ChessEnum id;
	std::string chessName;

public:
	Chess();
	Chess(Position pos, ColorEnum color, ChessEnum id);

	void move(Board& board, Position& fromPos, Position& toPos);

	virtual std::vector<Position> canMove() = 0;
	virtual std::vector<Position> canEat() = 0;

};

class  General :public Chess {

public:
	General(Position pos, ColorEnum color);

	std::vector<Position> canMove();
	std::vector<Position> canEat();

};

class Advisor :public Chess {

public:
	Advisor(Position pos, ColorEnum color);

	std::vector<Position> canMove();
	std::vector<Position> canEat();

};

class Elephant :public Chess {

public:
	Elephant(Position pos, ColorEnum color);

	std::vector<Position> canMove();
	std::vector<Position> canEat();

};

class Chariot :public Chess {

public:
	Chariot(Position pos, ColorEnum color);

	std::vector<Position> canMove();
	std::vector<Position> canEat();

};

class Horse :public Chess {

public:
	Horse(Position pos, ColorEnum color);

	std::vector<Position> canMove();
	std::vector<Position> canEat();

};

class Cannon :public Chess {

public:
	Cannon(Position pos, ColorEnum color);

	std::vector<Position> canMove();
	std::vector<Position> canEat();

};

class Soldier :public Chess {

public:
	Soldier(Position pos, ColorEnum color);

	std::vector<Position> canMove();
	std::vector<Position> canEat();

};