#include "Chess.h" 

Chess::Chess() {}
Chess::Chess(Position pos, ColorEnum color, ChessEnum id) {
	this->pos = pos;
	this->color = color;
	this->id = id;
	switch (id)
	{
	case ChessEnum::General:
		this->chessName = color == ColorEnum::Red ? "帥" : "將";
		break;
	case ChessEnum::Advisor:
		this->chessName = color == ColorEnum::Red ? "仕" : "士";
		break;
	case ChessEnum::Elephant:
		this->chessName = color == ColorEnum::Red ? "相" : "象";
		break;
	case ChessEnum::Chariot:
		this->chessName = color == ColorEnum::Red ? "俥" : "車";
		break;
	case ChessEnum::Horse:
		this->chessName = color == ColorEnum::Red ? "傌" : "馬";
		break;
	case ChessEnum::Cannon:
		this->chessName = color == ColorEnum::Red ? "炮" : "砲";
		break;
	case ChessEnum::Soldier:
		this->chessName = color == ColorEnum::Red ? "兵" : "卒";
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


void Chess::move(Board& board, Position& fromPos, Position& toPos) {

}

std::vector<Position> General::canMove() {
	return std::vector<Position>();
}
std::vector<Position> General::canEat() {
	return std::vector<Position>();
}

std::vector<Position> Advisor::canMove() {
	return std::vector<Position>();
}
std::vector<Position> Advisor::canEat() {
	return std::vector<Position>();
}

std::vector<Position> Elephant::canMove() {
	return std::vector<Position>();
}
std::vector<Position> Elephant::canEat() {
	return std::vector<Position>();
}

std::vector<Position> Chariot::canMove() {
	return std::vector<Position>();
}
std::vector<Position> Chariot::canEat() {
	return std::vector<Position>();
}

std::vector<Position> Horse::canMove() {
	return std::vector<Position>();
}
std::vector<Position> Horse::canEat() {
	return std::vector<Position>();
}

std::vector<Position> Cannon::canMove() {
	return std::vector<Position>();
}
std::vector<Position> Cannon::canEat() {
	return std::vector<Position>();
}

std::vector<Position> Soldier::canMove() {
	return std::vector<Position>();
}
std::vector<Position> Soldier::canEat() {
	return std::vector<Position>();
}