#include "pch.h"
#include "Matrix.h"
#include <iostream>

//====================STRUCTURE=====================

Matrix::Matrix(int m, int n, bool identity) {
	if (m < Matrix::MIN_DIMMENSION_SIZE) m = Matrix::MIN_DIMMENSION_SIZE;
	if (n < Matrix::MIN_DIMMENSION_SIZE) n = Matrix::MIN_DIMMENSION_SIZE;
	if (m > Matrix::MAX_DIMMENSION_SIZE) m = Matrix::MAX_DIMMENSION_SIZE;
	if (n > Matrix::MAX_DIMMENSION_SIZE) n = Matrix::MAX_DIMMENSION_SIZE;

	this->m = m;
	this->n = n;

	this->values = std::vector<std::vector<float>>(this->m, std::vector<float>(this->n, 0));

	if (identity && this->isSquare()) {
		for (int i = 0; i < this->n; ++i)  this->values[i][i] = 1;
	}
}

Matrix::Matrix(int m, int n, const std::vector<std::vector<float>>& vals) {
	this->setValues(m, n, vals);
}

Matrix::Matrix(const Matrix& mat) {
	this->m = mat.m;
	this->n = mat.n;
	this->setValues(mat.m, mat.n, mat.values);
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
bool Matrix::isSquare() const { return m == n; }

//NOTE:  a(i,j)=0 if i!=j
bool Matrix::isDiagonal() const {
	if (!this->isSquare()) return false;
	for (int j = 0; j < this->m; ++j)
		for (int i = 0; i < this->n; ++i)
			if (i != j && this->values[j][i] != 0) return false;
	return true;
}

//NOTE:  a(i,j)=0 if i!=j		&&	a(i,j)=1 if i=j
bool Matrix::isIdentity() const {
	if (!this->isSquare()) return false;
	for (int j = 0; j < this->m; ++j)
		for (int i = 0; i < this->n; ++i)
			if (i != j && this->values[j][i] != 0 || i == j && this->values[j][i] != 1) return false;
	return true;
}

//NOTE:  a(i,j)=0 for all i,j
bool Matrix::isZero() const {
	for (int j = 0; j < this->m; ++j)
		for (int i = 0; i < this->n; ++i)
			if (this->values[j][i] != 0) return false;
	return true;
}

//NOTE:  a(i,j)>=0 for all i,j
bool Matrix::isNonNegative() const {
	for (int j = 0; j < this->m; ++j)
		for (int i = 0; i < this->n; ++i)
			if (this->values[j][i] < 0) return false;
	return true;
}

//NOTE:  a(i,j)>0 for all i,j
bool Matrix::isPositive() const {
	for (int j = 0; j < this->m; ++j)
		for (int i = 0; i < this->n; ++i)
			if (this->values[j][i] <= 0) return false;
	return true;
}

bool Matrix::isInvertible() {
	return this->isSquare() && this->determinant() != 0;
}

//===================COMPARISON====================

bool Matrix::compareSize(const Matrix& mat1, const Matrix& mat2) { return mat1.m == mat2.m && mat1.n == mat2.n; }

bool Matrix::compareValues(const Matrix& mat1, const Matrix& mat2) {
	if (!Matrix::compareSize(mat1, mat2)) return false;
	for (int j = 0; j < mat1.m; ++j)
		for (int i = 0; i < mat1.n; ++i)
			if (mat1.values[j][i] != mat2.values[j][i]) return false;
	return true;
}

bool Matrix::compareSize(const Matrix& mat) { return Matrix::compareSize(*this, mat); }
bool Matrix::compareValues(const Matrix& mat) { return Matrix::compareValues(*this, mat); }

//===================OPERATORS=======================

Matrix Matrix::Add(const Matrix& mat1, const Matrix& mat2) {
	if (!Matrix::compareSize(mat1, mat2)) throw MatrixIncompatibleDimensionsException();
	Matrix res(mat1.m, mat1.n);
	for (int j = 0; j < res.m; ++j)
		for (int i = 0; i < res.n; ++i) res.values[j][i] = mat1.values[j][i] + mat2.values[j][i];
	return res;
}

Matrix Matrix::Sub(const Matrix& mat1, const Matrix& mat2) {
	if (!Matrix::compareSize(mat1, mat2)) throw MatrixIncompatibleDimensionsException();
	Matrix res(mat1.m, mat1.n);
	for (int j = 0; j < res.m; ++j)
		for (int i = 0; i < res.n; ++i) res.values[j][i] = mat1.values[j][i] - mat2.values[j][i];
	return res;
}

Matrix Matrix::Mult(const Matrix& mat1, const Matrix& mat2) {
	if (mat1.n != mat2.m) throw MatrixIncompatibleDimensionsException();
	Matrix res(mat1.m, mat2.n);
	for (int j = 0; j < res.m; ++j)
		for (int i = 0; i < res.n; ++i) {
			res.values[j][i] = 0;
			for (int n = 0; n < mat1.n; ++n)
				res.values[j][i] += mat1.values[j][n] * mat2.values[n][i];
		}
	return res;
}

Matrix Matrix::Scale(const Matrix& mat, float s) {
	Matrix res(mat.m, mat.n);
	for (int j = 0; j < res.m; ++j)		//NOTE: scale each entry in matrix by "s"
		for (int i = 0; i < res.n; ++i) res.values[j][i] = s * mat.values[j][i];
	return res;
}

Matrix Matrix::transpose(const Matrix& mat) {
	Matrix trans(mat.n, mat.m);	//NOTE: swap n and m for transpose
	for (int j = 0; j < mat.m; ++j)
		for (int i = 0; i < mat.n; ++i)  trans.values[j][i] = mat.values[i][j];
	return trans;
}

float Matrix::determinant(const Matrix& mat) {
	if (!mat.isSquare()) throw MatrixNotSquareException();
	float det = 0;
	if (mat.n == 1) det = mat.values[0][0];
	else if (mat.n == 2) det = mat.values[0][0] * mat.values[1][1] - mat.values[0][1] * mat.values[1][0];
	else {
		int sign = 1;
		for (int c = 0; c < mat.n; ++c) {
			if (mat.values[0][c] != 0) det += sign * mat.values[0][c] * Matrix::determinant(Matrix::subMatrix(mat, 0, c));
			sign *= -1;
		}
	}
	return det;
}

Matrix Matrix::subMatrix(const Matrix& mat, int excRow_m, int excCol_n) {
	if (excRow_m >= mat.m) excRow_m = mat.m - 1;
	if (excCol_n >= mat.n) excCol_n = mat.n - 1;
	Matrix newMat(mat.m - 1, mat.n - 1, false);
	int j = 0;
	for (int p = 0; p < mat.m; ++p) {
		if (p != excRow_m) {
			int i = 0;
			for (int q = 0; q < mat.n; ++q) {
				if (q != excCol_n) {
					newMat.values[j][i] = mat.values[p][q];
					i++;
				}
			}
			j++;
		}
	}
	return newMat;
}

Matrix Matrix::inverse(Matrix& mat) {		//NOTE: Matrix inverse with LU decomposition
	if (!mat.isInvertible()) throw MatrixNotInvertibleException();
	int M = mat.m, N = mat.n;
	Matrix old(mat);
	Matrix inv(M, N, true);
	for (int i = 0; i < N; ++i) {
		if (old.values[i][i] == 0)	throw MatrixNotInvertibleException();
		for (int j = 0; j < N; ++j) {
			if (i != j) {
				float ratio = old.values[j][i] / old.values[i][i];
				for (int k = 0; k < N * 2; ++k) {
					if (k < N) old.values[j][k] = (old.values[j][k] - ratio * old.values[i][k]);
					else inv.values[j][k - N] = inv.values[j][k - N] - ratio * inv.values[i][k - N];
				}
			}
		}
	}
	for (int i = 0; i < N; ++i)
		for (int j = 0; j < N; ++j)
			inv.values[i][j] = inv.values[i][j] / old.values[i][i];
	return inv;
}


Matrix Matrix::Add(const Matrix& mat) { return Matrix::Add(*this, mat); }
Matrix Matrix::Sub(const Matrix& mat) { return Matrix::Sub(*this, mat); }
Matrix Matrix::Mult(const Matrix& mat) { return Matrix::Mult(*this, mat); }
Matrix Matrix::Scale(float s) { return Matrix::Scale(*this, s); }
Matrix Matrix::transpose() { return Matrix::transpose(*this); }
float Matrix::determinant() { return Matrix::determinant(*this); }
Matrix Matrix::inverse() { return Matrix::inverse(*this); }

Matrix Matrix::operator+ (const Matrix& mat) { return Matrix::Add(*this, mat); }
Matrix Matrix::operator- (const Matrix& mat) { return Matrix::Sub(*this, mat); }
Matrix Matrix::operator* (const Matrix& mat) { return Matrix::Mult(*this, mat); }
Matrix Matrix::operator* (float s) { return Matrix::Scale(*this, s); }
Matrix operator* (float s, const Matrix& mat) { return Matrix::Scale(mat, s); }

Matrix& Matrix::operator+= (const Matrix& mat) {
	if (!Matrix::compareSize(*this, mat)) throw MatrixIncompatibleDimensionsException();
	for (int j = 0; j < this->m; ++j)		//NOTE: scale each entry in matrix by "s"
		for (int i = 0; i < this->n; ++i) this->values[j][i] += mat.values[j][i];
	return *this;
}
Matrix& Matrix::operator-= (const Matrix& mat) {
	if (!Matrix::compareSize(*this, mat)) throw MatrixIncompatibleDimensionsException();
	for (int j = 0; j < this->m; ++j)		//NOTE: scale each entry in matrix by "s"
		for (int i = 0; i < this->n; ++i) this->values[j][i] -= mat.values[j][i];
	return *this;
}

Matrix& Matrix::operator*= (const Matrix& mat) {
	Matrix res = (*this) * mat;
	this->setValues(res.m, res.n, res.values);
	return *this;
}


Matrix& Matrix::operator*= (float s) {
	for (int j = 0; j < this->m; ++j)
		for (int i = 0; i < this->n; ++i) this->values[j][i] *= s;
	return *this;
}




//====================OUTPUT=====================

void Matrix::print() const {
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

void Matrix::print(const char* label) const {
	std::cout << label << std::endl;
	this->print();
}

//====================PRIVATE========================

void Matrix::setValues(int m, int n, const std::vector<std::vector<float>>& vals) {
	if (m < Matrix::MIN_DIMMENSION_SIZE) m = Matrix::MIN_DIMMENSION_SIZE;
	if (n < Matrix::MIN_DIMMENSION_SIZE) n = Matrix::MIN_DIMMENSION_SIZE;
	if (m > Matrix::MAX_DIMMENSION_SIZE) m = Matrix::MAX_DIMMENSION_SIZE;
	if (n > Matrix::MAX_DIMMENSION_SIZE) n = Matrix::MAX_DIMMENSION_SIZE;

	//TODO: verify dimensions with size of 2D vector 

	this->m = m;
	this->n = n;

	this->values = std::vector<std::vector<float>>(this->m, std::vector<float>(this->n, 0));

	for (int j = 0; j < this->m; ++j)
		for (int i = 0; i < this->n; ++i)
			this->values[j][i] = vals[j][i];
}


//====================MATRIX PRESETS========================

Matrix2::Matrix2(bool identity) : Matrix(2, 2, identity) {}
Matrix2::Matrix2(const std::vector<std::vector<float>>& vals) : Matrix(2, 2, vals) {}
Matrix2::Matrix2(const Matrix2& mat) : Matrix(mat) {}

Matrix3::Matrix3(bool identity) : Matrix(3, 3, identity) {}
Matrix3::Matrix3(const std::vector<std::vector<float>>& vals) : Matrix(3, 3, vals) {}
Matrix3::Matrix3(const Matrix3& mat) : Matrix(mat) {}

Matrix4::Matrix4(bool identity) : Matrix(4, 4, identity) {}
Matrix4::Matrix4(const std::vector<std::vector<float>>& vals) : Matrix(4, 4, vals) {}
Matrix4::Matrix4(const Matrix4& mat) : Matrix(mat) {}


//----------------LU Decomposition---------------------
	/*Matrix inv(mat.m, mat.n, false);
	int M = mat.m, N = mat.n;
	int e, i, j, k, y, counter;
	float c, sum;
	counter = 0;

	std::vector<std::vector<float>> A(M, std::vector<float>(N + 1, 0));
	for (int p = 0; p < M; ++p)
		for (int q = 0; q < N + 1; ++q)
			A[p][q] = (q < N) ? mat.values[p][q] : ++counter;

	std::vector<std::vector<float>> L(M, std::vector<float>(N + 1, 0));
	for (int p = 0; p < M; ++p)
		for (int q = 0; q < N + 1; ++q)
			L[p][q] = (p == q) ? 1 : 0;

	for (j = 0; j < M; j++) {
		for (i = 0; i < M; i++) {
			if (i > j) {
				c = A[i][j] / A[j][j];
				L[i][j] = c;
				for (k = 0; k < M; k++) A[i][k] = A[i][k] - c * A[j][k];
			}
		}
	}

	for (y = 0; y < M; y++) {
		for (int p = 0; p < M; ++p) L[p][N] = (y == p) ? 1 : 0;
		A[0][N] = L[0][N] / L[0][0];
		for (i = 1; i < M; i++) {
			sum = 0;
			for (j = i - 1; j >= 0; j--) sum = sum + L[i][j] * A[j][N];
			A[i][N] = (L[i][N] - sum) / L[i][i];
		}
		inv.values[M - 1][y] = A[M - 1][N] / A[M - 1][M - 1];
		for (i = 1; i >= 0; i--) {
			sum = 0;
			for (j = i + 1; j < M; j++) sum = sum + A[i][j] * inv.values[j][y];
			inv.values[i][y] = (A[i][N] - sum) / A[i][i];
		}
	}
	return inv;*/