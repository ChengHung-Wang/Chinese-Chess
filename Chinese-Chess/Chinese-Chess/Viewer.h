#pragma once
#include <string>

// 用於把前端所需的資料包裝成 Json
class Viewer {

public:
	std::string haveLast();
	std::string getLast();
	std::string getNew();
	std::string getRound();
	std::string getMove();
	std::string move();
	std::string save();
	std::string getTime();
	std::string getLast();

};