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


void Chess::move(Board& board, Position fromPos, Position toPos) {
	this->pos.x = toPos.x;
	this->pos.y = toPos.y;
	board.board[fromPos.y][fromPos.x] = 0;
	board.board[toPos.y][toPos.x] = static_cast<int>(this->id) * (this->color == ColorEnum::Red ? 1 : -1);
	return;
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
	std::vector<Position> movePos;
	if (this->pos.x != 8 && board.applyMove(Position(this->pos.x + 1, this->pos.y), this->color)) {
		movePos.push_back(Position(this->pos.x + 1, this->pos.y));
	}
	if (this->pos.x != 0 && board.applyMove(Position(this->pos.x - 1, this->pos.y), this->color)) {
		movePos.push_back(Position(this->pos.x - 1, this->pos.y));
	}
	if (this->pos.y != 9 && board.applyMove(Position(this->pos.x, this->pos.y + 1), this->color)) {
		movePos.push_back(Position(this->pos.x, this->pos.y + 1));
	}
	if (this->pos.y != 0 && board.applyMove(Position(this->pos.x, this->pos.y - 1), this->color)) {
		movePos.push_back(Position(this->pos.x, this->pos.y - 1));
	}

	return movePos;
}
std::vector<Position> Advisor::canEat(Board& board) {
	std::vector<Position> eatPos;
	if (this->pos.x != 8 && board.applyEat(Position(this->pos.x + 1, this->pos.y), this->color)) {
		eatPos.push_back(Position(this->pos.x + 1, this->pos.y));
	}
	if (this->pos.x != 0 && board.applyEat(Position(this->pos.x - 1, this->pos.y), this->color)) {
		eatPos.push_back(Position(this->pos.x - 1, this->pos.y));
	}
	if (this->pos.y != 9 && board.applyEat(Position(this->pos.x, this->pos.y + 1), this->color)) {
		eatPos.push_back(Position(this->pos.x, this->pos.y + 1));
	}
	if (this->pos.y != 0 && board.applyEat(Position(this->pos.x, this->pos.y - 1), this->color)) {
		eatPos.push_back(Position(this->pos.x, this->pos.y - 1));
	}

	return eatPos;
}

std::vector<Position> Elephant::canMove(Board& board) {
	std::vector<Position> movePos;
	if (this->pos.x != 8 && board.applyMove(Position(this->pos.x + 1, this->pos.y), this->color)) {
		movePos.push_back(Position(this->pos.x + 1, this->pos.y));
	}
	if (this->pos.x != 0 && board.applyMove(Position(this->pos.x - 1, this->pos.y), this->color)) {
		movePos.push_back(Position(this->pos.x - 1, this->pos.y));
	}
	if (this->pos.y != 9 && board.applyMove(Position(this->pos.x, this->pos.y + 1), this->color)) {
		movePos.push_back(Position(this->pos.x, this->pos.y + 1));
	}
	if (this->pos.y != 0 && board.applyMove(Position(this->pos.x, this->pos.y - 1), this->color)) {
		movePos.push_back(Position(this->pos.x, this->pos.y - 1));
	}

	return movePos;
}
std::vector<Position> Elephant::canEat(Board& board) {
	std::vector<Position> eatPos;
	if (this->pos.x != 8 && board.applyEat(Position(this->pos.x + 1, this->pos.y), this->color)) {
		eatPos.push_back(Position(this->pos.x + 1, this->pos.y));
	}
	if (this->pos.x != 0 && board.applyEat(Position(this->pos.x - 1, this->pos.y), this->color)) {
		eatPos.push_back(Position(this->pos.x - 1, this->pos.y));
	}
	if (this->pos.y != 9 && board.applyEat(Position(this->pos.x, this->pos.y + 1), this->color)) {
		eatPos.push_back(Position(this->pos.x, this->pos.y + 1));
	}
	if (this->pos.y != 0 && board.applyEat(Position(this->pos.x, this->pos.y - 1), this->color)) {
		eatPos.push_back(Position(this->pos.x, this->pos.y - 1));
	}

	return eatPos;
}

std::vector<Position> Chariot::canMove(Board& board) {
	std::vector<Position> movePos;
	if (this->pos.x != 8 && board.applyMove(Position(this->pos.x + 1, this->pos.y), this->color)) {
		movePos.push_back(Position(this->pos.x + 1, this->pos.y));
	}
	if (this->pos.x != 0 && board.applyMove(Position(this->pos.x - 1, this->pos.y), this->color)) {
		movePos.push_back(Position(this->pos.x - 1, this->pos.y));
	}
	if (this->pos.y != 9 && board.applyMove(Position(this->pos.x, this->pos.y + 1), this->color)) {
		movePos.push_back(Position(this->pos.x, this->pos.y + 1));
	}
	if (this->pos.y != 0 && board.applyMove(Position(this->pos.x, this->pos.y - 1), this->color)) {
		movePos.push_back(Position(this->pos.x, this->pos.y - 1));
	}

	return movePos;
}
std::vector<Position> Chariot::canEat(Board& board) {
	std::vector<Position> eatPos;
	if (this->pos.x != 8 && board.applyEat(Position(this->pos.x + 1, this->pos.y), this->color)) {
		eatPos.push_back(Position(this->pos.x + 1, this->pos.y));
	}
	if (this->pos.x != 0 && board.applyEat(Position(this->pos.x - 1, this->pos.y), this->color)) {
		eatPos.push_back(Position(this->pos.x - 1, this->pos.y));
	}
	if (this->pos.y != 9 && board.applyEat(Position(this->pos.x, this->pos.y + 1), this->color)) {
		eatPos.push_back(Position(this->pos.x, this->pos.y + 1));
	}
	if (this->pos.y != 0 && board.applyEat(Position(this->pos.x, this->pos.y - 1), this->color)) {
		eatPos.push_back(Position(this->pos.x, this->pos.y - 1));
	}

	return eatPos;
}

std::vector<Position> Horse::canMove(Board& board) {
	std::vector<Position> movePos;
	if (this->pos.x != 8 && board.applyMove(Position(this->pos.x + 1, this->pos.y), this->color)) {
		movePos.push_back(Position(this->pos.x + 1, this->pos.y));
	}
	if (this->pos.x != 0 && board.applyMove(Position(this->pos.x - 1, this->pos.y), this->color)) {
		movePos.push_back(Position(this->pos.x - 1, this->pos.y));
	}
	if (this->pos.y != 9 && board.applyMove(Position(this->pos.x, this->pos.y + 1), this->color)) {
		movePos.push_back(Position(this->pos.x, this->pos.y + 1));
	}
	if (this->pos.y != 0 && board.applyMove(Position(this->pos.x, this->pos.y - 1), this->color)) {
		movePos.push_back(Position(this->pos.x, this->pos.y - 1));
	}

	return movePos;
}
std::vector<Position> Horse::canEat(Board& board) {
	std::vector<Position> eatPos;
	if (this->pos.x != 8 && board.applyEat(Position(this->pos.x + 1, this->pos.y), this->color)) {
		eatPos.push_back(Position(this->pos.x + 1, this->pos.y));
	}
	if (this->pos.x != 0 && board.applyEat(Position(this->pos.x - 1, this->pos.y), this->color)) {
		eatPos.push_back(Position(this->pos.x - 1, this->pos.y));
	}
	if (this->pos.y != 9 && board.applyEat(Position(this->pos.x, this->pos.y + 1), this->color)) {
		eatPos.push_back(Position(this->pos.x, this->pos.y + 1));
	}
	if (this->pos.y != 0 && board.applyEat(Position(this->pos.x, this->pos.y - 1), this->color)) {
		eatPos.push_back(Position(this->pos.x, this->pos.y - 1));
	}

	return eatPos;
}

std::vector<Position> Cannon::canMove(Board& board) {
	std::vector<Position> movePos;
	if (this->pos.x != 8 && board.applyMove(Position(this->pos.x + 1, this->pos.y), this->color)) {
		movePos.push_back(Position(this->pos.x + 1, this->pos.y));
	}
	if (this->pos.x != 0 && board.applyMove(Position(this->pos.x - 1, this->pos.y), this->color)) {
		movePos.push_back(Position(this->pos.x - 1, this->pos.y));
	}
	if (this->pos.y != 9 && board.applyMove(Position(this->pos.x, this->pos.y + 1), this->color)) {
		movePos.push_back(Position(this->pos.x, this->pos.y + 1));
	}
	if (this->pos.y != 0 && board.applyMove(Position(this->pos.x, this->pos.y - 1), this->color)) {
		movePos.push_back(Position(this->pos.x, this->pos.y - 1));
	}

	return movePos;
}
std::vector<Position> Cannon::canEat(Board& board) {
	std::vector<Position> eatPos;
	if (this->pos.x != 8 && board.applyEat(Position(this->pos.x + 1, this->pos.y), this->color)) {
		eatPos.push_back(Position(this->pos.x + 1, this->pos.y));
	}
	if (this->pos.x != 0 && board.applyEat(Position(this->pos.x - 1, this->pos.y), this->color)) {
		eatPos.push_back(Position(this->pos.x - 1, this->pos.y));
	}
	if (this->pos.y != 9 && board.applyEat(Position(this->pos.x, this->pos.y + 1), this->color)) {
		eatPos.push_back(Position(this->pos.x, this->pos.y + 1));
	}
	if (this->pos.y != 0 && board.applyEat(Position(this->pos.x, this->pos.y - 1), this->color)) {
		eatPos.push_back(Position(this->pos.x, this->pos.y - 1));
	}

	return eatPos;
}

std::vector<Position> Soldier::canMove(Board& board) {
	std::vector<Position> movePos;
	if (this->pos.x != 8 && board.applyMove(Position(this->pos.x + 1, this->pos.y), this->color)) {
		movePos.push_back(Position(this->pos.x + 1, this->pos.y));
	}
	if (this->pos.x != 0 && board.applyMove(Position(this->pos.x - 1, this->pos.y), this->color)) {
		movePos.push_back(Position(this->pos.x - 1, this->pos.y));
	}
	if (this->pos.y != 9 && board.applyMove(Position(this->pos.x, this->pos.y + 1), this->color)) {
		movePos.push_back(Position(this->pos.x, this->pos.y + 1));
	}
	if (this->pos.y != 0 && board.applyMove(Position(this->pos.x, this->pos.y - 1), this->color)) {
		movePos.push_back(Position(this->pos.x, this->pos.y - 1));
	}

	return movePos;
}
std::vector<Position> Soldier::canEat(Board& board) {
	std::vector<Position> eatPos;
	if (this->pos.x != 8 && board.applyEat(Position(this->pos.x + 1, this->pos.y), this->color)) {
		eatPos.push_back(Position(this->pos.x + 1, this->pos.y));
	}
	if (this->pos.x != 0 && board.applyEat(Position(this->pos.x - 1, this->pos.y), this->color)) {
		eatPos.push_back(Position(this->pos.x - 1, this->pos.y));
	}
	if (this->pos.y != 9 && board.applyEat(Position(this->pos.x, this->pos.y + 1), this->color)) {
		eatPos.push_back(Position(this->pos.x, this->pos.y + 1));
	}
	if (this->pos.y != 0 && board.applyEat(Position(this->pos.x, this->pos.y - 1), this->color)) {
		eatPos.push_back(Position(this->pos.x, this->pos.y - 1));
	}

	return eatPos;
}