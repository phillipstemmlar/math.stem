#pragma once

#include "math.stem.h"
#include "MatrixException.h";
#include <string>

class DLLEXPORT Matrix {
public:

	//Structure
	Matrix(unsigned int m, unsigned int n);
	~Matrix();

	//writers
	void set(unsigned int j, unsigned int i, float value);

	//readers
	float get(unsigned int j, unsigned int i) const;

	int M() const;
	int N() const;

	//Queries
	bool isSquare();		//m=n
	bool isDiagonal();	// a(i,j)=0 if i!=j
	bool isIdentity();	// a(i,j)=0 if i!=j		&&	a(i,j)=1 if i=j
	bool isZero();			// a(i,j)=0 for all i,j
	bool isNonNegative(); // a(i,j)>=0 for all i,j
	bool isPositive();		// a(i,j)>0 for all i,j

	//Equality
		//Compare 2 matrices' sizes
		//Compare 2 matrices' values

	//Arithmetic
		//Addition (Different forms, all cases)
		//multiplication  (Different forms, all cases)
		//scaling

	//output
	void print();
	void print(const char* label);
private:
	int m;
	int n;

	float** values;

};