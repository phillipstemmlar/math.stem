#pragma once
#include "pch.h"
#include "Matrix.h"
#include "VectorException.h"
#include <sstream>
#include <string>
#include <iostream>

class Vector2;
class Vector3;
class Vector4;

class Vector : public Matrix
{
public:
	//Strucutre
	DLLEXPORT Vector(int m);
	DLLEXPORT Vector(int m, const std::vector<float>& vals);
	DLLEXPORT Vector(const std::vector<float>& vals);
	DLLEXPORT Vector(const Vector& vec);

	//writers
	DLLEXPORT void set(int i, float val);

	DLLEXPORT void X(float x);
	DLLEXPORT void Y(float y);
	DLLEXPORT void Z(float w);
	DLLEXPORT void W(float z);

	//readers
	DLLEXPORT int size() const;
	DLLEXPORT float get(int i) const;

	DLLEXPORT float X() const;
	DLLEXPORT float Y() const;
	DLLEXPORT float Z() const;
	DLLEXPORT float W() const;

	DLLEXPORT float& operator[](int i);
	DLLEXPORT float operator[](int i) const;

	//static presets
	DLLEXPORT static Vector Zero(int n);

	//Queries
	DLLEXPORT bool isZero() const;
	DLLEXPORT bool isUnit() const;

	//Operations
	DLLEXPORT static Vector Add(const Vector& vec1, const Vector& vec2);
	DLLEXPORT static Vector Sub(const Vector& vec1, const Vector& vec2);
	DLLEXPORT static float Dot(const Vector& vec1, const Vector& vec2);
	DLLEXPORT static Vector Cross(const Vector& vec1, const Vector& vec2);
	DLLEXPORT static Vector Scale(const Vector& vec1, float s);

	DLLEXPORT static Vector Unit(const Vector& vec);
	DLLEXPORT static Vector Normalized(const Vector& vec);

	DLLEXPORT static float Magnitude(const Vector& vec);
	DLLEXPORT static float MagnitudeSquared(const Vector& vec);
	DLLEXPORT static void ClampMagnitude(Vector& vec, float mag);
	DLLEXPORT static void SetMagnitude(Vector& vec, float mag);

	DLLEXPORT Vector Add(const Vector& vec);
	DLLEXPORT Vector Sub(const Vector& vec);
	DLLEXPORT float Dot(const Vector& vec);
	DLLEXPORT Vector Cross(const Vector& vec);
	DLLEXPORT Vector Scale(float s);

	DLLEXPORT Vector Unit();
	DLLEXPORT Vector Normalized();
	DLLEXPORT float Magnitude();
	DLLEXPORT float MagnitudeSquared();
	DLLEXPORT void ClampMagnitude(float mag);
	DLLEXPORT void SetMagnitude(float mag);

	DLLEXPORT Vector operator+ (const Vector& vec);
	DLLEXPORT Vector operator- (const Vector& vec);
	DLLEXPORT Vector operator* (float s);
	DLLEXPORT friend Vector operator* (float s, const Vector& vec);

	DLLEXPORT Vector& operator+= (const Vector& vec);
	DLLEXPORT Vector& operator-= (const Vector& vec);
	DLLEXPORT Vector& operator*= (float s);

	//Casting
	DLLEXPORT operator Vector2();
	DLLEXPORT operator Vector3();
	DLLEXPORT operator Vector4();

	DLLEXPORT operator std::string();

	//Output
	DLLEXPORT std::string ToString() const;
	DLLEXPORT friend std::ostream& operator<<(std::ostream& os, const Vector& vec);

	DLLEXPORT virtual void print() const;
	DLLEXPORT void print(const char* label) const;
protected:
	virtual void setValues(int m, const std::vector<float>& vals);

};

class Vector2 : public Vector {
public:
	DLLEXPORT Vector2();
	DLLEXPORT Vector2(float x, float y);
	DLLEXPORT Vector2(const std::vector<float>& vals);
	DLLEXPORT Vector2(const Vector2& mat);

	DLLEXPORT static Vector2 Zero();

	DLLEXPORT operator Vector3();
	DLLEXPORT operator Vector4();
};

class Vector3 : public Vector {
public:
	DLLEXPORT Vector3();
	DLLEXPORT Vector3(float x, float y, float z);
	DLLEXPORT Vector3(const std::vector<float>& vals);
	DLLEXPORT Vector3(const Vector3& mat);

	DLLEXPORT static Vector3 Zero();

	DLLEXPORT operator Vector2();
	DLLEXPORT operator Vector4();
};

class Vector4 : public Vector {
public:
	DLLEXPORT Vector4();
	DLLEXPORT Vector4(float x, float y, float z, float w);
	DLLEXPORT Vector4(const std::vector<float>& vals);
	DLLEXPORT Vector4(const Vector4& mat);

	DLLEXPORT static Vector4 Zero();

	DLLEXPORT operator Vector2();
	DLLEXPORT operator Vector3();
};