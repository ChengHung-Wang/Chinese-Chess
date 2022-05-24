#include "GameManager.h"

std::string GameManager::setFile(std::string hash) {
	this->newGame = false;
	std::regex reg("Player: (\\d+), Action: (\\w+) \\((\\d+), (\\d+)\\) -> \\((\\d+), (\\d+)\\)");
	std::string input;
	std::cin.ignore();
	while (true) {
		std::getline(std::cin, input);
		if (input == "@~!~@") {
			break;
		}
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
					Chess* eatChess = NULL;
					if (this->board.board[toY][toX] != 0) {
						eatChess = this->eaten(Position(toX, toY));
					}
					c->move(this->board, Position(fromX, fromY), Position(toX, toY));
					addRecord(c, eatChess, fromX, fromY, toX, toY);
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

std::string GameManager::getRound(std::string hash) {
	if (!newGame) {
		this->currentPlayer = this->currentPlayer == ColorEnum::Red ? ColorEnum::Black : ColorEnum::Red; //change current player
	}
	this->newGame = false;
	int checkmate = 0;
	int winner = 0;
	std::string modal = "";
	if (this->records.size() == 0) {
		return this->viewer.getRound(this->currentPlayer, checkmate, winner, modal, NULL, NULL, NULL, NULL, hash);
	}
	else {
		Record last = this->records[this->records.size() - 1];
		return this->viewer.getRound(this->currentPlayer, checkmate, winner, modal, last.chess, last.eatChess, &(last.from), &(last.to), hash);
	}
}

std::string GameManager::getMove(ChessEnum chessId, int x, int y, std::string hash) {
	std::vector<Position> canMove;
	std::vector<Position> canEat;
	for (auto& c : this->onBoard) {
		if (c->color == this->currentPlayer && c->id == chessId && c->pos.x == x && c->pos.y == y) {
			canMove = c->canMove(this->board);
			canEat = c->canEat(this->board);
			break;
		}
	}

	return this->viewer.getMove(canMove, canEat, hash);
}

std::string GameManager::getTime(std::string hash) {
	if (this->currentPlayer == ColorEnum::Red) {
		this->rTime--;
	}
	if (this->currentPlayer == ColorEnum::Black) {
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

std::string GameManager::save(std::string hash) {
	std::ostringstream ostr;
	for (auto& r : this->records) {
		ostr << "Player: " << static_cast<int>(r.chess->color) << ", Action: " << r.chess->enName << " (" << r.from.x << ", " << r.from.y << ") -> (" << r.to.x << ", " << r.to.y << ")" << std::endl;
	}
	return this->viewer.save(ostr.str(), hash);
}

std::string GameManager::giveUp(std::string hash) {
	std::string modal;
	ColorEnum winner;
	if (this->currentPlayer == ColorEnum::Red) {
		modal = "Black Win!";
		winner = ColorEnum::Black;
	}
	if (this->currentPlayer == ColorEnum::Black) {
		modal = "Red Win!";
		winner = ColorEnum::Red;
	}
	return this->viewer.giveUp(winner, modal, hash);
}

std::string GameManager::logs(std::string hash) {
	return this->viewer.logs(this->records, hash);
}

void GameManager::addRecord(Chess* chess, Chess* eatChess, int fromX, int fromY, int toX, int toY) {
	std::vector<Chess*> cOnBoard;
	for (auto c : onBoard) {
		switch (c->id)
		{
		case ChessEnum::General:
			cOnBoard.push_back(new General(c->pos, c->color));
			break;
		case ChessEnum::Advisor:
			cOnBoard.push_back(new Advisor(c->pos, c->color));
			break;
		case ChessEnum::Elephant:
			cOnBoard.push_back(new Elephant(c->pos, c->color));
			break;
		case ChessEnum::Chariot:
			cOnBoard.push_back(new Chariot(c->pos, c->color));
			break;
		case ChessEnum::Horse:
			cOnBoard.push_back(new Horse(c->pos, c->color));
			break;
		case ChessEnum::Cannon:
			cOnBoard.push_back(new Cannon(c->pos, c->color));
			break;
		case ChessEnum::Soldier:
			cOnBoard.push_back(new Soldier(c->pos, c->color));
			break;
		}
	}
	Record r = Record(cOnBoard, chess, eatChess, Position(fromX, fromY), Position(toX, toY), this->rTime, this->bTime);
	this->records.push_back(r);

	return;
}

std::string GameManager::move(ChessEnum chessId, int fromX, int fromY, int toX, int toY, std::string hash) {
	for (auto& c : this->onBoard) {
		if (c->color == this->currentPlayer && c->id == chessId && c->pos.x == fromX && c->pos.y == fromY) {
			std::string action = "move";
			Chess* eatChess = NULL;
			if (this->board.board[toY][toX] != 0) {
				eatChess = this->eaten(Position(toX, toY));
				action = "replace";
			}
			c->move(this->board, Position(fromX, fromY), Position(toX, toY));
			addRecord(c, eatChess, fromX, fromY, toX, toY);
			return this->viewer.move(action, hash);
		}
	}
}

Chess* GameManager::eaten(Position eatPos) {
	Chess* eatChess = NULL;
	auto it = std::begin(this->onBoard);
	while (it != std::end(this->onBoard)) {
		if ((*it)->pos.x == eatPos.x && (*it)->pos.y == eatPos.y) {
			eatChess = *it;
			it = this->onBoard.erase(it);
			break;
		}
		else {
			++it;
		}
	}
	return eatChess;
}
