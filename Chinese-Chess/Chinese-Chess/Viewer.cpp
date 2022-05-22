#include "Viewer.h"

std::string Viewer::setNew(std::vector<Chess*> onBoard, int rTime, int bTime, std::string hash) {
	json response = {
		{"rTime", rTime},
		{"bTime", bTime},
		{"hash", hash}
	};
	response["chess"] = json::array();
	for (auto& c : onBoard) {
		json chess = json::object({
			{"name", c->id},
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
