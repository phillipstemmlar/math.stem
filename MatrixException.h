#pragma once
#include <exception>
#include <string>

class MatrixIndexOutOfBoundsException : public std::exception {
public:
	virtual const char* what() const throw();
};

