#include <iostream>
#include <string>
#include "GameManager.h"


#define _CRT_SECURE_NO_WARNINGS

int main() {
	system("chcp 65001");
	GameManager gm;
	std::string opt, hash;
	while (std::cin >> opt) {
		std::cin >> hash;
		if (opt == "save") {

		}
		else if (opt == "setFile") {
			int rows;
			std::cin >> rows;
			std::cout << gm.setFile(rows, hash);
		}
		else if (opt == "setNew") {
			gm = GameManager();
			std::cout << gm.setNew(hash);
		}
		else if (opt == "getRound") {

		}
		else if (opt == "getMove") {
			int color, chessId, x, y;
			std::cin >> color >> chessId >> x >> y;
			std::cout << gm.getMove(static_cast<ChessEnum>(chessId), x, y, hash);
		}
		else if (opt == "move") {
			int color, chessId, fromX, fromY, toX, toY;
			std::cin >> color >> chessId >> fromX >> fromY >> toX >> toY;
			std::cout << gm.move(static_cast<ChessEnum>(chessId), fromX, fromY, toX, toY, hash);
		}
		else if (opt == "getTime") {
			int color;
			std::cout << gm.getTime(hash);
		}
		else if (opt == "giveUp") {
			int color;
			std::cin >> color;
			std::cout << gm.giveUp(hash);
		}
		else if (opt == "logs") {
			std::cout << gm.logs(hash);
		}
	}
}