#include <iostream>
#include <string>
#include "GameManager.h"

int main() {
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
			int x, y;
			std::cin >> x >> y;
			std::cout << gm.getMove(x, y, hash);
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