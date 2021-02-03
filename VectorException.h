#pragma once
#include "MatrixException.h"
class VectorException : public MatrixException {
	virtual const char* what() const throw();
};

class VectorIndexOutOfBoundsException : public VectorException {
public:
	virtual const char* what() const throw();
};

class VectorIncompatibleDimensionsException : public VectorException {
	virtual const char* what() const throw();
};

class VectorCrossProductException : public VectorException {
	virtual const char* what() const throw();
};
