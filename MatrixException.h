#pragma once
#include <exception>
#include <string>

class MatrixException : public std::exception {
	virtual const char* what() const throw();
};

class MatrixIndexOutOfBoundsException : public MatrixException {
public:
	virtual const char* what() const throw();
};

class MatrixIncompatibleDimensionsException : public MatrixException {
	virtual const char* what() const throw();
};

class MatrixNotSquareException : public MatrixException {
	virtual const char* what() const throw();
};

class MatrixNotInvertibleException : public MatrixException {
	virtual const char* what() const throw();
};