#pragma once

#include "math.stem.h"
#include "MatrixException.h"
#include <string>
#include <vector>

class DLLEXPORT Matrix {
public:

	//Structure
	Matrix(int m, int n, bool identify = true);
	~Matrix();

	//writers
	void set(int j, int i, float value);

	//readers
	float get(int j, int i) const;

	int M() const;
	int N() const;

	//Queries
	bool isSquare();		//m=n
	bool isDiagonal();	// a(i,j)=0 if i!=j
	bool isIdentity();	// a(i,j)=0 if i!=j		&&	a(i,j)=1 if i=j
	bool isZero();			// a(i,j)=0 for all i,j
	bool isNonNegative(); // a(i,j)>=0 for all i,j
	bool isPositive();		// a(i,j)>0 for all i,j
	//bool isInvertible();

	//Comparison
	static bool compareSize(Matrix const& mat1, Matrix const& mat2);
	static bool compareValues(Matrix const& mat1, Matrix const& mat2);
	bool compareSize(Matrix const& mat);
	bool compareValues(Matrix const& mat);


	//Operations
		//Addition (Different forms, all cases)
			//Matrix-Matrix Addition
			//Matrix-Matrix Subtraction
		//multiplication  (Different forms, all cases)
			//Matrix-Scalar Multiplication
			//Matrix-Matrix Multiplication
			//vector?...
		//inverse
		//determinant

	static Matrix Add(const Matrix& mat1, const Matrix& mat2);
	static Matrix Sub(const Matrix& mat1, const Matrix& mat2);
	static Matrix Scale(const Matrix& mat1, float s);
	static Matrix transpose(Matrix& mat);

	Matrix Add(const Matrix& mat);
	Matrix Sub(const Matrix& mat);
	Matrix Scale(float s);
	Matrix transpose();

	Matrix operator+ (const Matrix& mat);			//Matrix-Matrix Addition
	Matrix operator- (const Matrix& mat);			//Matrix-Matrix Subtraction
	Matrix operator* (float s);								//Matrix-Scalar Multiplication

	//output
	void print();
	void print(const char* label);
private:
	int m;
	int n;

	std::vector<std::vector<float>> values;

	static const int MIN_DIMMENSION_SIZE = 1;
	static const int MAX_DIMMENSION_SIZE = 10000;
};

extern DLLEXPORT Matrix operator* (float s, const Matrix& mat); //Scalar-Matrix Multiplication