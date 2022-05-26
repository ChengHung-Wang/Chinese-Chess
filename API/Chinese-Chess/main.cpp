#include <iostream>
#include <string>
#include "GameManager.h"

int main() {
	system("chcp 65001");
	GameManager gm;
	std::string opt, hash;
	while (std::cin >> opt) {
		if (opt == "show") {
			gm.showBoard();
			continue;
		}

		std::cin >> hash;
		if (opt == "save") {
			std::cout << gm.save(hash);
		}
		else if (opt == "setFile") {
			gm = GameManager();
			std::cout << gm.setFile(hash);
		}
		else if (opt == "setNew") {
			gm = GameManager();
			std::cout << gm.setNew(hash);
		}
		else if (opt == "getRound") {
			std::cout << gm.getRound(hash);
		}
		else if (opt == "getMove") {
			int uni;
			std::cin >> uni;
			std::cout << gm.getMove(uni, hash);
		}
		else if (opt == "move") {
			int fromX, fromY, toX, toY;
			std::cin >> fromX >> fromY >> toX >> toY;
			std::cout << gm.move(fromX, fromY, toX, toY, hash);
		}
		else if (opt == "getTime") {
			std::cout << gm.getTime(hash);
		}
		else if (opt == "giveUp") {
			std::cout << gm.giveUp(hash);
		}
		else if (opt == "logs") {
			std::cout << gm.logs(hash);
		}
	}
}