#include "pch.h"
#include "Vector2.h"
#include <sstream>

Vector2::Vector2(float x, float y) {
	this->x = x;
	this->y = y;
}

std::string Vector2::toString() {
	std::stringstream ss;
	ss << "[ " << this->x << " " << this->y << " ]";
	return ss.str();
}