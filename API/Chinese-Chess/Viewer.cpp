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
			{"uni", c->uni},
			{"color", c->color},
			{"id", c->id},
			{"x", c->pos.x},
			{"y", c->pos.y},
			{"uni", c->uni}
			});
		response["chess"].push_back(chess);
	}
	return response.dump();
}

std::string Viewer::getTime(int bTime, int rTime, int winner, std::string modal, std::string hash) {
	json response = {
		{"rTime", rTime},
		{"bTime", bTime},
		{"winner", winner},
		{"modal", modal},
		{"hash", hash}
	};
	return response.dump();
}

std::string Viewer::getRound(ColorEnum color, int checkmate, int winner, std::string modal, Chess* moveChess, Chess* eatChess, Position* from, Position* to, std::string hash) {
	json response = {
		{"color", color},
		{"checkmate", checkmate},
		{"winner", winner},
		{"modal", modal},
		{"hash", hash}
	};
	if (moveChess != NULL) {
		response["move"] = json::object({
			{"id", moveChess->id},
			{"uni", moveChess->uni},
			{"fromX", from->x},
			{"fromY", from->y},
			{"toX", to->x},
			{"toY", to->y}
			});
	}
	else {
		response["move"] = nullptr;
	}
	if (eatChess != NULL) {
		response["delete"] = json::object({
			{"id", eatChess->id},
			{"uni", eatChess->uni},
			{"x", to->x},
			{"y", to->y}
			});
	}
	else {
		response["delete"] = nullptr;
	}
	return response.dump();
}

std::string Viewer::getMove(Chess* moveChess, std::vector<Position> canMove, std::vector<Position> canEat, std::string hash) {
	json response = {
		{"uni", moveChess->uni},
		{"x", moveChess->pos.x},
		{"y", moveChess->pos.y},
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

std::string Viewer::logs(std::vector<Record> records, std::string hash) {
	json response = {
		{"hash", hash}
	};
	response["logs"] = json::array();
	for (auto& r : records) {
		json record = json::object({
			{"rTime", r.rTime},
			{"bTime", r.bTime}
			});
		record["chess"] = json::array();
		for (auto& c : r.onBoard) {
			json chess = json::object({
				{"name", c->chessName},
				{"uni", c->uni},
				{"color", c->color},
				{"id", c->id},
				{"x", c->pos.x},
				{"y", c->pos.y},
				});
			record["chess"].push_back(chess);
		}
		response["logs"].push_back(record);
	}
	return response.dump();
}

std::string Viewer::move(std::string action, std::string hash) {
	json response = {
		{"action", action},
		{"hash", hash}
	};
	return response.dump();
}

std::string Viewer::save(std::string content, std::string hash) {
	json response = {
		{"content", content},
		{"hash", hash}
	};
	return response.dump();
}
