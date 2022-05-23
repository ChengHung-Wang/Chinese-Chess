#include <iostream>
#include <string>


#include "GameManager.h"

using namespace std;


int main() {
	system("chcp 65001");
	GameManager gm;
	std::string opt, hash;
	while (std::cin >> opt) {
		std::cin >> hash;
		if (opt == "save") {

		}
		else if (opt == "setFile") {
			cout << "as1234" << endl;
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