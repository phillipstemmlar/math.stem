#pragma once

#ifdef MATHSTEM_EXPORTS
#define DLLEXPORT __declspec(dllexport)
#else
#define DLLEXPORT __declspec(dllimport)
#endif

#include "Matrix.h"
