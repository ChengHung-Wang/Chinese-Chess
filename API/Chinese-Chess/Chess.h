#pragma once 
#include <vector>
#include <string>
#include "Position.h"
#include "ChessEnum.h"
#include "ColorEnum.h"
#include "Board.h"

class Chess {

public:
	Position pos;
	ColorEnum color;
	ChessEnum id;
	std::string chessName;
	std::string enName;
	int uni;

public:
	Chess();
	Chess(Position pos, ColorEnum color, ChessEnum id, int uni);

	void move(Board& board, Position fromPos, Position toPos);

	virtual std::vector<Position> canMove(Board& board) = 0;
	virtual std::vector<Position> canEat(Board& board) = 0;

};

class  General :public Chess {

public:
	General(Position pos, ColorEnum color, int uni);

	std::vector<Position> canMove(Board& board);
	std::vector<Position> canEat(Board& board);

};

class Advisor :public Chess {

public:
	Advisor(Position pos, ColorEnum color, int uni);

	std::vector<Position> canMove(Board& board);
	std::vector<Position> canEat(Board& board);

};

class Elephant :public Chess {

public:
	Elephant(Position pos, ColorEnum color, int uni);

	std::vector<Position> canMove(Board& board);
	std::vector<Position> canEat(Board& board);

};

class Chariot :public Chess {

public:
	Chariot(Position pos, ColorEnum color, int uni);

	std::vector<Position> canMove(Board& board);
	std::vector<Position> canEat(Board& board);

};

class Horse :public Chess {

public:
	Horse(Position pos, ColorEnum color, int uni);

	std::vector<Position> canMove(Board& board);
	std::vector<Position> canEat(Board& board);

};

class Cannon :public Chess {

public:
	Cannon(Position pos, ColorEnum color, int uni);

	std::vector<Position> canMove(Board& board);
	std::vector<Position> canEat(Board& board);

};

class Soldier :public Chess {

public:
	Soldier(Position pos, ColorEnum color, int uni);

	std::vector<Position> canMove(Board& board);
	std::vector<Position> canEat(Board& board);

};