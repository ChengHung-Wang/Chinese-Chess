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
			int player, fromX, fromY, toX, toY;
			//std::string chessName, a, b, c;
			char chessName[20];
			//std::cin >> a;
			//scanf_s("%d,", &player);
			//std::cin >> b;
			//std::cin >> chessName;
			//scanf_s("(%d, %d)", &fromX, &fromY);
			//std::cin >> c;
			//scanf_s("(%d, %d)", &toX, &toY);

			sscanf_s("Player: 1, Action: abc", "Player: %d, Action: %s", &player, &chessName);
			//std::cout << gm.setFile(hash);
		}
		else if (opt == "setNew") {
			std::cout << gm.setNew(hash);
		}
		else if (opt == "getRound") {

		}
		else if (opt == "getMove") {

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