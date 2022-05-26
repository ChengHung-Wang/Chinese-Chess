#include "Board.h"

bool Board::applyMove(Position pos, ColorEnum color) {
	return color == ColorEnum::Red ? this->board[pos.y][pos.x] <= 0 : this->board[pos.y][pos.x] >= 0; // black chess < 0 : red chess > 0
}

bool Board::applyEat(Position pos, ColorEnum color) {
	return color == ColorEnum::Red ? this->board[pos.y][pos.x] < 0 : this->board[pos.y][pos.x] > 0; // black chess < 0 : red chess > 0
}
