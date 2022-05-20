#pragma once
#include "Chess.h"
#include "Board.h"
#include "Viewer.h"

class GameManager {

public:
	std::vector<Chess> onBoard;
	ChessEnum currentPlayer;
	Board board;
	Viewer viewer;
};