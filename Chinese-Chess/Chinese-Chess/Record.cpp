#include "Record.h"

Record::Record(Board board, ColorEnum player, std::string chessName, Position from, Position to, std::string move) {
	this->onBoard = onBoard;
	this->board = board;
	this->player = player;
	this->chessName = chessName;
	this->from = from;
	this->to = to;
	this->move = move;
}