#include "pch.h"
#include "MatrixException.h"


const char* MatrixIndexOutOfBoundsException::what() const throw() {
	return "MatrixIndexOutOfBoundsException: Index used to access Matrix element is not within the Matrix bounds!";
}