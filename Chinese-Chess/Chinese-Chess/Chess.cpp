﻿#include "Chess.h" 

Chess::Chess() {}
Chess::Chess(Position pos, ColorEnum color, ChessEnum id) {
	this->pos = pos;
	this->color = color;
	this->id = id;
	switch (id)
	{
	case ChessEnum::General:
		this->chessName = color == ColorEnum::Red ? "帥" : "將";
		this->enName = "General";
		break;
	case ChessEnum::Advisor:
		this->chessName = color == ColorEnum::Red ? "仕" : "士";
		this->enName = "Advisor";
		break;
	case ChessEnum::Elephant:
		this->chessName = color == ColorEnum::Red ? "相" : "象";
		this->enName = "Elephant";
		break;
	case ChessEnum::Chariot:
		this->chessName = color == ColorEnum::Red ? "俥" : "車";
		this->enName = "Chariot";
		break;
	case ChessEnum::Horse:
		this->chessName = color == ColorEnum::Red ? "傌" : "馬";
		this->enName = "Horse";
		break;
	case ChessEnum::Cannon:
		this->chessName = color == ColorEnum::Red ? "炮" : "砲";
		this->enName = "Cannon";
		break;
	case ChessEnum::Soldier:
		this->chessName = color == ColorEnum::Red ? "兵" : "卒";
		this->enName = "Soldier";
		break;
	}
}

General::General(Position pos, ColorEnum color) : Chess(pos, color, ChessEnum::General) {}
Advisor::Advisor(Position pos, ColorEnum color) : Chess(pos, color, ChessEnum::Advisor) {}
Elephant::Elephant(Position pos, ColorEnum color) : Chess(pos, color, ChessEnum::Elephant) {}
Chariot::Chariot(Position pos, ColorEnum color) : Chess(pos, color, ChessEnum::Chariot) {}
Horse::Horse(Position pos, ColorEnum color) : Chess(pos, color, ChessEnum::Horse) {}
Cannon::Cannon(Position pos, ColorEnum color) : Chess(pos, color, ChessEnum::Cannon) {}
Soldier::Soldier(Position pos, ColorEnum color) : Chess(pos, color, ChessEnum::Soldier) {}


std::string Chess::move(Board& board, Position& fromPos, Position& toPos) {
	return "";
}

bool Board::applyMove(Position pos, ColorEnum color) {
	return color == ColorEnum::Red ? this->board[pos.y][pos.x] <= 0 : this->board[pos.y][pos.x] >= 0; // black chess < 0 : red chess > 0
}

bool Board::applyEat(Position pos, ColorEnum color) {
	return color == ColorEnum::Red ? this->board[pos.y][pos.x] < 0 : this->board[pos.y][pos.x] > 0; // black chess < 0 : red chess > 0
}

std::vector<Position> General::canMove(Board& board) {
	std::vector<Position> movePos;
	for (int x = 3; x <= 5; x++) {
		if (this->color == ColorEnum::Red) {
			for (int y = 7; y <= 9; y++) {
				if (board.applyMove(Position(x, y), this->color) && abs(this->pos.x - x) + abs(this->pos.y - y) == 1) {
					movePos.push_back(Position(x, y));
				}
			}
		}
		else {
			for (int y = 0; y <= 2; y++) {
				if (board.applyMove(Position(x, y), this->color) && abs(this->pos.x - x) + abs(this->pos.y - y) == 1) {
					movePos.push_back(Position(x, y));
				}
			}
		}
	}
	return movePos;
}
std::vector<Position> General::canEat(Board& board) {
	std::vector<Position> eatPos;
	for (int x = 3; x <= 5; x++) {
		if (this->color == ColorEnum::Red) {
			for (int y = 0; y <= 2; y++) {
				if (board.applyEat(Position(x, y), this->color) && abs(this->pos.x - x) + abs(this->pos.y - y) == 1) {
					eatPos.push_back(Position(x, y));
				}
			}
		}
		else {
			for (int y = 7; y <= 9; y++) {
				if (board.applyEat(Position(x, y), this->color) && abs(this->pos.x - x) + abs(this->pos.y - y) == 1) {
					eatPos.push_back(Position(x, y));
				}
			}
		}
	}
	return eatPos;
}

std::vector<Position> Advisor::canMove(Board& board) {
	return std::vector<Position>();
}
std::vector<Position> Advisor::canEat(Board& board) {
	return std::vector<Position>();
}

std::vector<Position> Elephant::canMove(Board& board) {
	return std::vector<Position>();
}
std::vector<Position> Elephant::canEat(Board& board) {
	return std::vector<Position>();
}

std::vector<Position> Chariot::canMove(Board& board) {
	return std::vector<Position>();
}
std::vector<Position> Chariot::canEat(Board& board) {
	return std::vector<Position>();
}

std::vector<Position> Horse::canMove(Board& board) {
	return std::vector<Position>();
}
std::vector<Position> Horse::canEat(Board& board) {
	return std::vector<Position>();
}

std::vector<Position> Cannon::canMove(Board& board) {
	return std::vector<Position>();
}
std::vector<Position> Cannon::canEat(Board& board) {
	return std::vector<Position>();
}

std::vector<Position> Soldier::canMove(Board& board) {
	return std::vector<Position>();
}
std::vector<Position> Soldier::canEat(Board& board) {
	return std::vector<Position>();
}