#include "Record.h"

Record::Record(ColorEnum player, std::string chessName, Position from, Position to, std::string move) {
	this->player = player;
	this->chessName = chessName;
	this->from = from;
	this->to = to;
	this->move = move;
}