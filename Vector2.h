#pragma once

#include "math.stem.h"
#include <string>

class DLLEXPORT Vector2 {
public:
	Vector2(float x, float y);
	std::string toString();
private:
	float x;
	float y;
};