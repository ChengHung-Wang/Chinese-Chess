#include "GameManager.h"

std::string GameManager::setNew(std::string hash) {
	return this->viewer.setNew(this->onBoard, this->rTime, this->bTime, hash);
}

std::string GameManager::getTime(int color, std::string hash) {
	if (color == 1) {
		this->rTime--;
	}
	if (color == 2) {
		this->bTime--;
	}

	int noTime = 0;
	if (bTime <= 0) {
		noTime = static_cast<int>(ColorEnum::Black);
	}
	if (rTime <= 0) {
		noTime = static_cast<int>(ColorEnum::Red);
	}
	return this->viewer.getTime(this->bTime, this->rTime, noTime, hash);
}
