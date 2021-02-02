#include "pch.h"
#include "MatrixException.h"

const char* MatrixException::what() const throw() {
	return "MatrixException: Matrix has thrown an unkown exception!";
}

const char* MatrixIndexOutOfBoundsException::what() const throw() {
	return "MatrixIndexOutOfBoundsException: Index used to access Matrix element is not within the Matrix bounds!";
}

const char* MatrixIncompatibleDimensionsException::what() const throw() {
	return "MatrixIncompatibleDimensionsException: Matrix operation cannot be performed with the dimensions specified!";
}

const char* MatrixNotSquareException::what() const throw() {
	return "MatrixNotSquareException: Operation only valid for a square matrix!";
}

const char* MatrixNotInvertibleException::what() const throw() {
	return "MatrixNotInvertibleException: Matrix is not invertible!";
}