#pragma once

#ifdef MATHSTEM_EXPORTS
#define DLLEXPORT __declspec(dllexport)
#else
#define DLLEXPORT __declspec(dllimport)
#endif

#include "Vector2.h"




//extern "C" DLLEXPORT void fibonacci_init(
//	const unsigned long long a, const unsigned long long b);




