#include "Viewer.h"

std::string Viewer::setBoard(std::vector<Chess*> onBoard, int rTime, int bTime, std::string hash) {
	json response = {
		{"rTime", rTime},
		{"bTime", bTime},
		{"hash", hash}
	};
	response["chess"] = json::array();
	for (auto& c : onBoard) {
		json chess = json::object({
			{"name", c->chessName},
			{"color", c->color},
			{"id", c->id},
			{"x", c->pos.x},
			{"y", c->pos.y}
			});
		response["chess"].push_back(chess);
	}
	return response.dump();
}

std::string Viewer::getTime(int bTime, int rTime, int noTime, std::string hash) {
	json response = {
		{"rTime", rTime},
		{"bTime", bTime},
		{"noTime", noTime},
		{"hash", hash}
	};
	return response.dump();
}

std::string Viewer::getMove(std::vector<Position> canMove, std::vector<Position> canEat, std::string hash) {
	json response = {
		{"hash", hash}
	};
	response["canMove"] = json::array();
	response["canEat"] = json::array();
	for (auto& m : canMove) {
		json movePos = json::object({
			{"x", m.x},
			{"y", m.y},
			});
		response["canMove"].push_back(movePos);
	}
	for (auto& e : canEat) {
		json eatPos = json::object({
			{"x", e.x},
			{"y", e.y},
			});
		response["canEat"].push_back(eatPos);
	}
	return response.dump();
}

std::string Viewer::giveUp(ColorEnum color, std::string modal, std::string hash) {
	json response = {
		{"modal", modal},
		{"winner", color},
		{"hash", hash}
	};
	return response.dump();
}
