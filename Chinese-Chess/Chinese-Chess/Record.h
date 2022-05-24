#pragma once
#include <vector>
#include <string>
#include "Chess.h"

class Record {

public:
	std::vector<Chess*> onBoard;
	Board board;
	Chess* chess;
	Chess* eatChess = NULL;
	Position from;
	Position to;
	int rTime;
	int bTime;


public:
	Record(std::vector<Chess*> onBoard, Board board, Chess* chess, Chess* eatChess, Position from, Position to, int rTime, int bTime);

};