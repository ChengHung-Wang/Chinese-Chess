#pragma once
#include <vector>
#include <string>
#include "Chess.h"

class Record {

public:
	std::vector<Chess*> onBoard;
	Board board;
	ColorEnum player;
	std::string chessName;
	Position from;
	Position to;
	std::string move;

public:
	Record(Board board, ColorEnum player, std::string chessName, Position from, Position to, std::string move);

};