#pragma once
#include <string>
#include "ColorEnum.h"
#include "Chess.h"
#include "nlohmann/json.hpp"

using json = nlohmann::json;

// Use for exchange data with UI
class Viewer {

public:
	std::string setFile();
	std::string setBoard(std::vector<Chess*> onBoard, int rTime, int bTime, std::string hash);
	std::string getTime(int bTime, int rTime, int noTime, std::string hash);
	std::string getRound();
	std::string getMove(std::vector<Position> canMove, std::vector<Position> canEat, std::string hash);
	std::string giveUp(ColorEnum color, std::string modal, std::string hash);
	void save();

};