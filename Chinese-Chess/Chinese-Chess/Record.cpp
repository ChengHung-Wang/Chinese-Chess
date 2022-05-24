#include "Record.h"

Record::Record(std::vector<Chess*> onBoard, Chess* chess, Chess* eatChess, Position from, Position to, int rTime, int bTime) {
	this->onBoard = onBoard;
	this->chess = chess;
	this->eatChess = eatChess;
	this->from = from;
	this->to = to;
	this->rTime = rTime;
	this->bTime = bTime;
}
