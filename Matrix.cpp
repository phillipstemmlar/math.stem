#include "pch.h"
#include "Matrix.h"
#include <iostream>

//====================STRUCTURE=====================

Matrix::Matrix(int m, int n, bool identify) {
	if (m < Matrix::MIN_DIMMENSION_SIZE) m = Matrix::MIN_DIMMENSION_SIZE;
	if (n < Matrix::MIN_DIMMENSION_SIZE) n = Matrix::MIN_DIMMENSION_SIZE;
	if (m > Matrix::MAX_DIMMENSION_SIZE) m = Matrix::MAX_DIMMENSION_SIZE;
	if (n > Matrix::MAX_DIMMENSION_SIZE) n = Matrix::MAX_DIMMENSION_SIZE;

	this->m = m;
	this->n = n;

	this->values = std::vector<std::vector<float>>(this->m, std::vector<float>(this->n, 0));

	if (identify && this->isSquare()) {
		for (int i = 0; i < this->n; ++i)  this->values[i][i] = 1;
	}
}

Matrix::~Matrix() {
	//if (this->values != nullptr) {
	//	for (int j = 0; j < this->m; ++j) {
	//		if (this->values[j] != nullptr) delete[] this->values[j];
	//	}
	//	delete[] this->values;
	//}
}

//====================WRITERS=====================

void Matrix::set(int j, int i, float value) {
	if (j >= 0 && j < this->M() && i >= 0 && i < this->N()) this->values[j][i] = value;
	else throw MatrixIndexOutOfBoundsException();
}

//====================READERS=====================

float Matrix::get(int j, int i) const {
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

//===================COMPARISON====================

bool Matrix::compareSize(Matrix const& mat1, Matrix const& mat2) { return mat1.m == mat2.m && mat1.n == mat2.n; }

bool Matrix::compareValues(Matrix const& mat1, Matrix const& mat2) {
	if (!Matrix::compareSize(mat1, mat2)) return false;
	for (int j = 0; j < mat1.m; ++j)
		for (int i = 0; i < mat1.n; ++i)
			if (mat1.values[j][i] != mat2.values[j][i]) return false;
	return true;
}

bool Matrix::compareSize(Matrix const& mat) { return Matrix::compareSize(*this, mat); }
bool Matrix::compareValues(Matrix const& mat) { return Matrix::compareValues(*this, mat); }

//===================OPERATORS=======================

Matrix Matrix::Add(const Matrix& mat1, const Matrix& mat2) {
	Matrix res(mat1.m, mat1.n);
	for (int j = 0; j < res.m; ++j)
		for (int i = 0; i < res.n; ++i) res.values[j][i] = mat1.values[j][i] + mat2.values[j][i];
	return res;
}

Matrix Matrix::Sub(const Matrix& mat1, const Matrix& mat2) {
	Matrix res(mat1.m, mat1.n);
	for (int j = 0; j < res.m; ++j)
		for (int i = 0; i < res.n; ++i) res.values[j][i] = mat1.values[j][i] - mat2.values[j][i];
	return res;
}

Matrix Matrix::Scale(const Matrix& mat, float s) {
	Matrix res(mat.m, mat.n);
	for (int j = 0; j < res.m; ++j)		//NOTE: scale each entry in matrix by "s"
		for (int i = 0; i < res.n; ++i) res.values[j][i] = s * mat.values[j][i];
	return res;
}

Matrix Matrix::transpose(Matrix& mat) {
	Matrix trans(mat.n, mat.m);	//NOTE: swap n and m for transpose
	for (int j = 0; j < mat.m; ++j)
		for (int i = 0; i < mat.n; ++i)  trans.values[j][i] = mat.values[i][j];
	return trans;
}


Matrix Matrix::Add(const Matrix& mat) { return Matrix::Add(*this, mat); }
Matrix Matrix::Sub(const Matrix& mat) { return Matrix::Sub(*this, mat); }
Matrix Matrix::Scale(float s) { return Matrix::Scale(*this, s); }
Matrix Matrix::transpose() { return Matrix::transpose(*this); }

Matrix Matrix::operator+ (const Matrix& mat) { return Matrix::Add(*this, mat); }
Matrix Matrix::operator- (const Matrix& mat) { return Matrix::Sub(*this, mat); }
Matrix Matrix::operator* (float s) { return Matrix::Scale(*this, s); }

Matrix operator* (float s, const Matrix& mat) { return Matrix::Scale(mat, s); }



//====================OUTPUT=====================

void Matrix::print() {
	std::cout << "( m = " << this->m << ", n = " << this->n << " )" << std::endl;

	//if (this->values == nullptr) {
	//	std::cout << "[null]" << std::endl;
	//	return;
	//}

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