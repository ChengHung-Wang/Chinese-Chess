#include <iostream>
#include <string>
#include "GameManager.h"

using namespace std;

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

		}
		else if (opt == "setNew") {
			std::cout << gm.setNew(hash);
		}
		else if (opt == "getRound") {

		}
		else if (opt == "getMove") {
			int color, chessId, x, y;
			std::cin >> color >> chessId >> x >> y;
			std::cout << gm.getMove(static_cast<ColorEnum>(color), static_cast<ChessEnum>(chessId), x, y, hash);
		}
		else if (opt == "move") {
			int color, chessId, fromX, fromY, toX, toY;
			std::cin >> color >> chessId >> fromX >> fromY >> toX >> toY;
			gm.move(static_cast<ColorEnum>(color), static_cast<ChessEnum>(chessId), fromX, fromY, toX, toY, hash);
		}
		else if (opt == "getTime") {
			std::cout << gm.getTime(1, hash);
		}
	}
}