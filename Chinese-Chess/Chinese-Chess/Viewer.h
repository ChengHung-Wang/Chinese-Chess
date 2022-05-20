#pragma once
#include <string>
#include "nlohmann/json.hpp"

using json = nlohmann::json;

// Use for exchange data with UI
class Viewer {

public:
	std::string setFile();
	std::string setNew();
	std::string getTime();
	std::string getRound();
	std::string getMove();
	void move();
	void save();

};