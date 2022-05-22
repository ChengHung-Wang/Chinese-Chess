#include <iostream>
#include <string>
#include "GameManager.h"

int main() {
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

		}
		else if (opt == "move") {

		}
		else if (opt == "getTime") {
			std::cout << gm.getTime(1, hash);
		}
	}
}