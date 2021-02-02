#pragma once

#include "math.stem.h"
#include "MatrixException.h"
#include <string>
#include <vector>

class Matrix {
public:

	//Structure
	DLLEXPORT Matrix(int m, int n, bool identify = true);
	DLLEXPORT Matrix(int m, int n, const std::vector<std::vector<float>>& vals);
	DLLEXPORT Matrix(const Matrix& mat);
	DLLEXPORT ~Matrix();

	//writers
	DLLEXPORT void set(int j, int i, float value);

	//readers
	DLLEXPORT float get(int j, int i) const;

	DLLEXPORT int M() const;
	DLLEXPORT int N() const;

	//Queries
	DLLEXPORT bool isSquare() const;		//m=n
	DLLEXPORT bool isDiagonal() const;	// a(i,j)=0 if i!=j
	DLLEXPORT bool isIdentity() const;	// a(i,j)=0 if i!=j		&&	a(i,j)=1 if i=j
	DLLEXPORT bool isZero() const;			// a(i,j)=0 for all i,j
	DLLEXPORT bool isNonNegative() const; // a(i,j)>=0 for all i,j
	DLLEXPORT bool isPositive() const;		// a(i,j)>0 for all i,j
	DLLEXPORT bool isInvertible();

	//Comparison
	DLLEXPORT static bool compareSize(const Matrix& mat1, const Matrix& mat2);
	DLLEXPORT static bool compareValues(const Matrix& mat1, const Matrix& mat2);
	DLLEXPORT bool compareSize(const Matrix& mat);
	DLLEXPORT bool compareValues(const Matrix& mat);

	DLLEXPORT static Matrix Add(const Matrix& mat1, const Matrix& mat2);
	DLLEXPORT static Matrix Sub(const Matrix& mat1, const Matrix& mat2);
	DLLEXPORT static Matrix Mult(const Matrix& mat1, const Matrix& mat2);
	DLLEXPORT static Matrix Scale(const Matrix& mat1, float s);

	DLLEXPORT static Matrix transpose(const Matrix& mat);
	DLLEXPORT static float determinant(const Matrix& mat);
	DLLEXPORT static Matrix inverse(Matrix& mat);

	DLLEXPORT Matrix Add(const Matrix& mat);
	DLLEXPORT Matrix Sub(const Matrix& mat);
	DLLEXPORT Matrix Mult(const Matrix& mat);
	DLLEXPORT Matrix Scale(float s);

	DLLEXPORT Matrix transpose();
	DLLEXPORT float determinant();
	DLLEXPORT Matrix inverse();

	DLLEXPORT Matrix operator+ (const Matrix& mat);			//Matrix-Matrix Addition
	DLLEXPORT Matrix operator- (const Matrix& mat);			//Matrix-Matrix Subtraction
	DLLEXPORT Matrix operator* (float s);								//Matrix-Scalar Multiplication
	DLLEXPORT Matrix operator* (const Matrix& mat1);		//Matrix-Scalar Multiplication

	DLLEXPORT Matrix& operator+= (const Matrix& mat);		//Matrix-Matrix Addition
	DLLEXPORT Matrix& operator-= (const Matrix& mat);		//Matrix-Matrix Addition
	DLLEXPORT Matrix& operator*= (float s);							//Matrix-Scalar Multiplication
	DLLEXPORT Matrix& operator*= (const Matrix& mat1);		//Matrix-Scalar Multiplication

	//output
	DLLEXPORT void print() const;
	DLLEXPORT void print(const char* label) const;
protected:
	void setValues(int m, int n, const std::vector<std::vector<float>>& vals);
	static Matrix subMatrix(const Matrix& mat, int m, int n);
private:
	int m;
	int n;

	std::vector<std::vector<float>> values;

	static const int MIN_DIMMENSION_SIZE = 1;
	static const int MAX_DIMMENSION_SIZE = 10000;
};

extern DLLEXPORT Matrix operator* (float s, const Matrix& mat); //Scalar-Matrix Multiplication