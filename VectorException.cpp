#include "pch.h"
#include "VectorException.h"

const char* VectorException::what() const throw() {
	return "VectorException: Vector has thrown an unkown exception!";
}

const char* VectorIndexOutOfBoundsException::what() const throw() {
	return "VectorIndexOutOfBoundsException: Index used to access Vector element is not within the Vector bounds!";
}

const char* VectorIncompatibleDimensionsException::what() const throw() {
	return "VectorIncompatibleDimensionsException: Vector operation cannot be performed with the dimensions specified!";
}

const char* VectorCrossProductException::what() const throw() {
	return "VectorCrossProductException: Vector cross product is only defined for vectors with 3 dimensions!";
}