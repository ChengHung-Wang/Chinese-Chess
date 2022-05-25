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

			Chess* eatChess = NULL;
			if (this->board.board[toY][toX] != 0) {
				eatChess = this->eaten(Position(toX, toY));
			}
			for (auto& c : this->onBoard) {
				if (c->enName == chessName && c->pos.x == fromX && c->pos.y == fromY) {
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
	std::string modal = "";
	int lastCheckmate = 0;
	int checkmate = 0;
	int winner = 0;
	if (this->records.size() > 1) {
		Record last = this->records[this->records.size() - 2];
		if (isCheckmate(last.onBoard, ColorEnum::Black, last.board)) {
			lastCheckmate = static_cast<int>(ColorEnum::Black);
		}
		if (isCheckmate(last.onBoard, ColorEnum::Red, last.board)) {
			lastCheckmate = static_cast<int>(ColorEnum::Red);
		}
	}
	//only one checkmate
	if (isCheckmate(this->onBoard, ColorEnum::Black, this->board)) {
		checkmate = static_cast<int>(ColorEnum::Black);
		modal = "Black Checkmate";
		if (lastCheckmate == static_cast<int>(ColorEnum::Black)) {
			winner = static_cast<int>(ColorEnum::Black);
			modal = "Black Win!";
		}
		else if (this->currentPlayer == ColorEnum::Red) { //last player
			winner = static_cast<int>(ColorEnum::Black);
			modal = "Black Win!";
		}
	}
	if (winner == 0 && isCheckmate(this->onBoard, ColorEnum::Red, this->board)) {
		checkmate = static_cast<int>(ColorEnum::Red);
		modal = "Red Checkmate";
		if (lastCheckmate == static_cast<int>(ColorEnum::Red)) {
			winner = static_cast<int>(ColorEnum::Red);
			modal = "Red Win!";
		}
		else if (this->currentPlayer == ColorEnum::Black) { //last player
			winner = static_cast<int>(ColorEnum::Red);
			modal = "Red Win!";
		}
	}

	if (!newGame) {
		this->currentPlayer = this->currentPlayer == ColorEnum::Red ? ColorEnum::Black : ColorEnum::Red; //change current player
	}
	else {
		this->newGame = false;
	}

	if (winner == 0) {
		for (auto& c : onBoard) {
			if (c->id == ChessEnum::General) {
				winner += this->board.board[c->pos.y][c->pos.x];
			}
		}
		if (winner == 0) {
			//Stalemate
			if (isStalemate(this->onBoard, ColorEnum::Black, this->board)) {
				winner = static_cast<int>(ColorEnum::Red);
				modal = "Red Win!";
			}
			if (winner == 0 && isStalemate(this->onBoard, ColorEnum::Red, this->board)) {
				winner = static_cast<int>(ColorEnum::Black);
				modal = "Black Win!";
			}
		}
		else {
			//Die
			if (winner == 1) {
				modal = "Red Win!";
				winner = 1;
			}
			else if (winner == -1) {
				modal = "Black Win!";
				winner = 2;
			}
		}
	}

	if (this->records.size() == 0) {
		return this->viewer.getRound(this->currentPlayer, checkmate, winner, modal, NULL, NULL, NULL, NULL, hash);
	}
	else {
		Record last = this->records[this->records.size() - 1];
		return this->viewer.getRound(this->currentPlayer, checkmate, winner, modal, last.chess, last.eatChess, &(last.from), &(last.to), hash);
	}
}

bool GameManager::isCheckmate(std::vector<Chess*> onBoard, ColorEnum color, Board board) {
	for (auto& c : onBoard) {
		if (c->color == color) {
			std::vector<Position> canEat = c->canEat(board);
			for (auto& e : canEat) {
				if (abs(board.board[e.y][e.x]) == abs(static_cast<int>(ChessEnum::General))) {
					return true;
				}
			}
		}
	}
	return false;
}

bool GameManager::isStalemate(std::vector<Chess*> onBoard, ColorEnum color, Board board) {
	for (auto& c : onBoard) {
		if (c->color == color) {
			std::vector<Position> canMove = c->canMove(board);
			for (auto& m : canMove) {
				std::vector<Chess*> cOnBoard;
				for (auto chess : onBoard) {
					switch (chess->id)
					{
					case ChessEnum::General:
						cOnBoard.push_back(new General(chess->pos, chess->color, chess->uni));
						break;
					case ChessEnum::Advisor:
						cOnBoard.push_back(new Advisor(chess->pos, chess->color, chess->uni));
						break;
					case ChessEnum::Elephant:
						cOnBoard.push_back(new Elephant(chess->pos, chess->color, chess->uni));
						break;
					case ChessEnum::Chariot:
						cOnBoard.push_back(new Chariot(chess->pos, chess->color, chess->uni));
						break;
					case ChessEnum::Horse:
						cOnBoard.push_back(new Horse(chess->pos, chess->color, chess->uni));
						break;
					case ChessEnum::Cannon:
						cOnBoard.push_back(new Cannon(chess->pos, chess->color, chess->uni));
						break;
					case ChessEnum::Soldier:
						cOnBoard.push_back(new Soldier(chess->pos, chess->color, chess->uni));
						break;
					}
				}
				Board cBoard;
				for (int i = 0; i < 10; i++) {
					for (int j = 0; j < 9; j++) {
						cBoard.board[i][j] = board.board[i][j];
					}
				}
				for (auto& cc : cOnBoard) {
					if (cc->pos.x == c->pos.x && cc->pos.y == cc->pos.y) {
						cc->move(cBoard, c->pos, m);
					}
				}
				if (!isCheckmate(cOnBoard, color == ColorEnum::Red ? ColorEnum::Black : ColorEnum::Red, cBoard)) {
					return false;
				}
			}
		}
	}
	return true;
}

std::string GameManager::getMove(int x, int y, std::string hash) {
	std::vector<Position> canMove;
	std::vector<Position> canEat;
	Chess* moveChess;
	for (auto& c : this->onBoard) {
		if (c->color == this->currentPlayer && c->pos.x == x && c->pos.y == y) {
			canMove = c->canMove(this->board);
			canEat = c->canEat(this->board);
			moveChess = c;
			break;
		}
	}
	return this->viewer.getMove(moveChess, canMove, canEat, hash);
}

std::string GameManager::getTime(std::string hash) {
	if (this->currentPlayer == ColorEnum::Red) {
		this->rTime--;
	}
	if (this->currentPlayer == ColorEnum::Black) {
		this->bTime--;
	}

	int winner = 0;
	std::string modal = "";
	if (bTime <= 0) {
		winner = static_cast<int>(ColorEnum::Red);
		modal = "Red Win!";
	}
	if (rTime <= 0) {
		winner = static_cast<int>(ColorEnum::Black);
		modal = "Black Win!";
	}
	return this->viewer.getTime(this->bTime, this->rTime, winner, modal, hash);
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
			cOnBoard.push_back(new General(c->pos, c->color, c->uni));
			break;
		case ChessEnum::Advisor:
			cOnBoard.push_back(new Advisor(c->pos, c->color, c->uni));
			break;
		case ChessEnum::Elephant:
			cOnBoard.push_back(new Elephant(c->pos, c->color, c->uni));
			break;
		case ChessEnum::Chariot:
			cOnBoard.push_back(new Chariot(c->pos, c->color, c->uni));
			break;
		case ChessEnum::Horse:
			cOnBoard.push_back(new Horse(c->pos, c->color, c->uni));
			break;
		case ChessEnum::Cannon:
			cOnBoard.push_back(new Cannon(c->pos, c->color, c->uni));
			break;
		case ChessEnum::Soldier:
			cOnBoard.push_back(new Soldier(c->pos, c->color, c->uni));
			break;
		}
	}
	Record r = Record(cOnBoard, this->board, chess, eatChess, Position(fromX, fromY), Position(toX, toY), this->rTime, this->bTime);
	this->records.push_back(r);

	return;
}

std::string GameManager::move(int fromX, int fromY, int toX, int toY, std::string hash) {
	std::string action = "move";
	Chess* eatChess = NULL;
	if (this->board.board[toY][toX] != 0) {
		eatChess = this->eaten(Position(toX, toY));
		action = "replace";
	}

	for (auto& c : this->onBoard) {
		if (c->color == this->currentPlayer && c->pos.x == fromX && c->pos.y == fromY) {
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

void GameManager::showBoard() {
	for (size_t i = 0; i < 10; i++) {
		for (size_t j = 0; j < 9; j++) {
			std::cout << std::setw(2) << std::setfill(' ') << this->board.board[i][j] << " ";
		}
		std::cout << std::endl;
	}
}
