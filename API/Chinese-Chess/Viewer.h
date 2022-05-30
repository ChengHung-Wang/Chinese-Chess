#pragma once
#include <string>
#include "ColorEnum.h"
#include "Chess.h"
#include "Record.h"
#include "nlohmann/json.hpp"

using json = nlohmann::json;

// Use for exchange data with UI
class Viewer {

public:
	std::string setBoard(std::vector<Chess*> onBoard, int rTime, int bTime, std::string hash);
	std::string getTime(int bTime, int rTime, int winner, std::string modal, std::string hash);
	std::string getRound(ColorEnum color, int checkmate, int winner, std::string modal, Chess* moveChess, Chess* eatChess, Position* from, Position* to, std::string hash);
	std::string getMove(Chess* moveChess, std::vector<Position> canMove, std::vector<Position> canEat, std::string hash);
	std::string giveUp(ColorEnum color, std::string modal, std::string hash);
	std::string logs(std::vector<Record> records, std::string hash);
	std::string move(std::string action, std::string hash);
	std::string save(std::string content, std::string hash);

};