#pragma once
#include <vector>
#include <string>
#include "Chess.h"

class Record {

public:
	std::vector<Chess*> onBoard;
	Chess* chess;
	Position from;
	Position to;
	int rTime;
	int bTime;


public:
	Record(std::vector<Chess*> onBoard, Chess* chess, Position from, Position to, int rTime, int bTime);

};