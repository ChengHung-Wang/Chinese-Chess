#pragma once
#include <vector>
#include <string>
#include "Chess.h"

class Record {

public:
	ColorEnum player;
	std::string chessName;
	Position from;
	Position to;
	std::string move;

public:
	Record(ColorEnum player, std::string chessName, Position from, Position to, std::string move);

};