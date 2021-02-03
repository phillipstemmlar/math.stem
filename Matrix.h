#pragma once

#include "pch.h"
#include <string>
#include <vector>
#include "MatrixException.h"

class Matrix {
public:

	//Structure
	DLLEXPORT Matrix(int m, int n, bool identity = true);
	DLLEXPORT Matrix(int m, int n, const std::vector<std::vector<float>>& vals);
	DLLEXPORT Matrix(const Matrix& mat);
	DLLEXPORT virtual ~Matrix();

	//writers
	DLLEXPORT void set(int j, int i, float value);

	//readers
	DLLEXPORT float get(int j, int i) const;

	DLLEXPORT int M() const;
	DLLEXPORT int N() const;

	//static preset matrices
	DLLEXPORT static Matrix Zero(int m, int n);
	DLLEXPORT static Matrix Identity(int m, int n);

	//get column vector
		//virtual for presets

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

	DLLEXPORT friend bool operator==(const Matrix& matLeft, const Matrix& matRight);
	DLLEXPORT friend bool operator!=(const Matrix& matLeft, const Matrix& matRight);

	//Operations
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
	DLLEXPORT friend Matrix operator* (float s, const Matrix& mat); //Scalar-Matrix Multiplication

	DLLEXPORT Matrix& operator+= (const Matrix& mat);		//Matrix-Matrix Addition
	DLLEXPORT Matrix& operator-= (const Matrix& mat);		//Matrix-Matrix Addition
	DLLEXPORT Matrix& operator*= (float s);							//Matrix-Scalar Multiplication
	DLLEXPORT Matrix& operator*= (const Matrix& mat1);		//Matrix-Scalar Multiplication

	//output
	DLLEXPORT virtual void print() const;
	DLLEXPORT virtual void print(const char* label) const;
protected:
	void setValues(int m, int n, const std::vector<std::vector<float>>& vals);
	static Matrix subMatrix(const Matrix& mat, int m, int n);

	float& getValueRef(int j, int i);

	static const int MIN_DIMMENSION_SIZE = 1;
	static const int MAX_DIMMENSION_SIZE = 10000;

	std::vector<std::vector<float>> values;
private:
	int m;	//row count
	int n;	//col count
};

class Matrix2 : public Matrix {
public:
	DLLEXPORT Matrix2(bool identity = true);
	DLLEXPORT Matrix2(const std::vector<std::vector<float>>& vals);
	DLLEXPORT Matrix2(const Matrix2& mat);

	DLLEXPORT static Matrix2 Zero();
	DLLEXPORT static Matrix2 Identity();
};

class Matrix3 : public Matrix {
public:
	DLLEXPORT Matrix3(bool identity = true);
	DLLEXPORT Matrix3(const std::vector<std::vector<float>>& vals);
	DLLEXPORT Matrix3(const Matrix3& mat);

	DLLEXPORT static Matrix3 Zero();
	DLLEXPORT static Matrix3 Identity();
};

class Matrix4 : public Matrix {
public:
	DLLEXPORT Matrix4(bool identity = true);
	DLLEXPORT Matrix4(const std::vector<std::vector<float>>& vals);
	DLLEXPORT Matrix4(const Matrix4& mat);

	DLLEXPORT static Matrix4 Zero();
	DLLEXPORT static Matrix4 Identity();
};