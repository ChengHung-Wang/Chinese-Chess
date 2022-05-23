#include "GameManager.h"

std::string GameManager::setFile(int rows, std::string hash) {
	std::regex reg("Player: (\\d+), Action: (\\w+) \\((\\d+), (\\d+)\\) -> \\((\\d+), (\\d+)\\)");
	std::string input;
	std::cin.ignore();
	for (int i = 0; i < rows; i++) {
		std::getline(std::cin, input);
		std::smatch sm;
		if (regex_search(input, sm, reg)) {
			this->currentPlayer = static_cast<ColorEnum>(std::atoi(sm.str(1).c_str()));
			std::string chessName = sm.str(2);
			int fromX, fromY, toX, toY;
			fromX = std::atoi(sm.str(3).c_str());
			fromY = std::atoi(sm.str(4).c_str());
			toX = std::atoi(sm.str(5).c_str());
			toY = std::atoi(sm.str(6).c_str());

			std::string move;
			for (auto& c : this->onBoard) {
				if (c->enName == chessName && c->pos.x == fromX && c->pos.y == fromY) {
					move = c->move(this->board, Position(fromX, fromY), Position(toX, toY));
					break;
				}
			}
		}
	}
	return this->viewer.setBoard(this->onBoard, this->rTime, this->bTime, hash);
}

std::string GameManager::setNew(std::string hash) {
	return this->viewer.setBoard(this->onBoard, this->rTime, this->bTime, hash);
}

std::string GameManager::getMove(ColorEnum color, ChessEnum chessId, int x, int y, std::string hash) {
	std::vector<Position> canMove;
	std::vector<Position> canEat;
	for (auto& c : this->onBoard) {
		if (c->color == color && c->id == chessId && c->pos.x == x && c->pos.y == y) {
			canMove = c->canMove(this->board);
			canEat = c->canEat(this->board);
			break;
		}
	}

	return this->viewer.getMove(canMove, canEat, hash);
}

std::string GameManager::getTime(ColorEnum color, std::string hash) {
	if (color == ColorEnum::Red) {
		this->rTime--;
	}
	if (color == ColorEnum::Black) {
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

std::string GameManager::giveUp(ColorEnum color, std::string hash) {
	std::string modal;
	ColorEnum winner;
	if (color == ColorEnum::Red) {
		modal = "Black Win!";
		winner = ColorEnum::Black;
	}
	if (color == ColorEnum::Black) {
		modal = "Red Win!";
		winner = ColorEnum::Red;
	}
	return this->viewer.giveUp(winner, modal, hash);
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
