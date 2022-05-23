#include "GameManager.h"

std::string GameManager::setFile(std::string hash) {

	return std::string();
}

std::string GameManager::setNew(std::string hash) {
	return this->viewer.setNew(this->onBoard, this->rTime, this->bTime, hash);
}

std::string GameManager::getTime(int color, std::string hash) {
	if (color == 1) {
		this->rTime--;
	}
	if (color == 2) {
		this->bTime--;
	}

	int noTime = 0;
	if (bTime <= 0) {
		noTime = static_cast<int>(ColorEnum::Black);
	}
	if (rTime <= 0) {
		noTime = static_cast<int>(ColorEnum::Red);
	}
	return this->viewer.getTime(this->bTime, this->rTime, noTime, hash);
}

void GameManager::move(ColorEnum color, ChessEnum chessId, int fromX, int fromY, int toX, int toY, std::string hash) {
	std::string chessName;
	switch (chessId)
	{
	case ChessEnum::General:
		chessName = "General";
		break;
	case ChessEnum::Advisor:
		chessName = "Advisor";
		break;
	case ChessEnum::Elephant:
		chessName = "Elephant";
		break;
	case ChessEnum::Chariot:
		chessName = "Chariot";
		break;
	case ChessEnum::Horse:
		chessName = "Horse";
		break;
	case ChessEnum::Cannon:
		chessName = "Cannon";
		break;
	case ChessEnum::Soldier:
		chessName = "Soldier";
		break;
	}
	std::string move;
	for (auto& c : this->onBoard) {
		if (c->color == color && c->id == chessId && c->pos.x == fromX && c->pos.y == fromY) {
			move = c->move(this->board, Position(fromX, fromY), Position(toX, toY));
			break;
		}
	}
	Record r = Record(color, chessName, Position(fromX, fromY), Position(toX, toY), move);
	this->record.push_back(r);
}
