#include "pch.h"
#include "Matrix.h"
#include <sstream>
#include <iostream>

//====================STRUCTURE=====================

Matrix::Matrix(unsigned int m, unsigned int n) {
	//TODO: check edge cases with matrix dimensions

	this->m = m;
	this->n = n;

	this->values = new float* [this->m];
	for (int j = 0; j < this->m; ++j) {
		this->values[j] = new float[this->n];
		for (int i = 0; i < this->n; ++i)  this->values[j][i] = (m == n && i == j) ? 1 : 0;
	}

}

Matrix::~Matrix() {
	for (int j = 0; j < this->m; ++j) delete[] this->values[j];
	delete[] this->values;
}

//====================WRITERS=====================

void Matrix::set(unsigned int j, unsigned int i, float value) {
	if (j >= 0 && j < this->M() && i >= 0 && i < this->N()) this->values[j][i] = value;
	else throw MatrixIndexOutOfBoundsException();
}

//====================READERS=====================

float Matrix::get(unsigned int j, unsigned int i) const {
	if (j >= 0 && j < this->M() && i >= 0 && i < this->N()) return this->values[j][i];
	else throw MatrixIndexOutOfBoundsException();
}

int Matrix::M() const { return this->m; }
int Matrix::N() const { return this->n; }

//====================QUERIES=====================

//NOTE:  m=n
bool Matrix::isSquare() { return m == n; }

//NOTE:  a(i,j)=0 if i!=j
bool Matrix::isDiagonal() {
	if (!this->isSquare()) return false;
	for (int j = 0; j < this->m; ++j)
		for (int i = 0; i < this->n; ++i)
			if (i != j && this->values[j][i] != 0) return false;
	return true;
}

//NOTE:  a(i,j)=0 if i!=j		&&	a(i,j)=1 if i=j
bool Matrix::isIdentity() {
	if (!this->isSquare()) return false;
	for (int j = 0; j < this->m; ++j)
		for (int i = 0; i < this->n; ++i)
			if (i != j && this->values[j][i] != 0 || i == j && this->values[j][i] != 1) return false;
	return true;
}

//NOTE:  a(i,j)=0 for all i,j
bool Matrix::isZero() {
	for (int j = 0; j < this->m; ++j)
		for (int i = 0; i < this->n; ++i)
			if (this->values[j][i] != 0) return false;
	return true;
}

//NOTE:  a(i,j)>=0 for all i,j
bool Matrix::isNonNegative() {
	for (int j = 0; j < this->m; ++j)
		for (int i = 0; i < this->n; ++i)
			if (this->values[j][i] < 0) return false;
	return true;
}

//NOTE:  a(i,j)>0 for all i,j
bool Matrix::isPositive() {
	for (int j = 0; j < this->m; ++j)
		for (int i = 0; i < this->n; ++i)
			if (this->values[j][i] <= 0) return false;
	return true;
}

//====================OUTPUT=====================

void Matrix::print() {
	std::cout << "( m = " << this->m << ", n = " << this->n << " )" << std::endl;

	for (int j = 0; j < this->m; ++j) {
		std::cout << "[ ";
		for (int i = 0; i < this->n; ++i) {
			std::cout << this->values[j][i] << " ";
		}
		std::cout << "]" << std::endl;
	}

}

void Matrix::print(const char* label) {
	std::cout << label << std::endl;
	this->print();
}