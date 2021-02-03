#include "pch.h"
#include "Vector.h"
#include <iostream>

//============================STRUCTURE=================================

Vector::Vector(int m) : Matrix(m, 1, false) {}

Vector::Vector(int m, const std::vector<float>& vals) : Matrix(m, 1, false) { this->setValues(m, vals); }

Vector::Vector(const std::vector<float>& vals) : Matrix(vals.size(), 1, false) { this->setValues(vals.size(), vals); }

Vector::Vector(const Vector& vec) : Matrix(vec) {}

//==============================WRITERS=================================

void Vector::set(int i, float val) {
	if (i < this->size()) this->Matrix::set(i, 0, val);
	else if (i < 4) return;
	else throw VectorIndexOutOfBoundsException();
}

void Vector::X(float x) { this->set(0, x); }
void Vector::Y(float y) { this->set(1, y); }
void Vector::Z(float z) { this->set(2, z); }
void Vector::W(float w) { this->set(3, w); }


//==============================READERS=================================

int Vector::size() const { return this->M(); }
float Vector::get(int i) const {
	if (i < this->size()) return this->Matrix::get(i, 0);
	else if (i < 4) return 0;
	else throw VectorIndexOutOfBoundsException();
}

float Vector::X() const { return this->get(0); }
float Vector::Y() const { return this->get(1); }
float Vector::Z() const { return this->get(2); }
float Vector::W() const { return this->get(3); }


float& Vector::operator[] (int i) {
	if (i >= 0 && i < this->size()) return this->Matrix::getValueRef(i, 0);
	else throw VectorIndexOutOfBoundsException();
}

float Vector::operator[] (int i) const {
	if (i >= 0 && i < this->size()) return this->get(i);
	else throw VectorIndexOutOfBoundsException();
}

//====================STATIC PRESETS==============
Vector Vector::Zero(int n) { return Vector(n); }

//=============================QUERIES==================================
bool Vector::isZero() const {
	for (int i = 0; i < this->size(); ++i) if (this->get(i) != 0) return false;
	return true;
}

bool Vector::isUnit() const {
	//check if vector is a unit-vector
	return false;
}

//============================COMPARISONS===============================

//=============================OPERATIONS===============================

Vector Vector::Add(const Vector& vec1, const Vector& vec2) {
	if (!Vector::compareSize(vec1, vec2)) throw VectorIncompatibleDimensionsException();
	Vector res(vec1.size());
	for (int i = 0; i < res.size(); ++i) res[i] = vec1[i] + vec2[i];
	return res;
}

Vector Vector::Sub(const Vector& vec1, const Vector& vec2) {
	if (!Vector::compareSize(vec1, vec2)) throw VectorIncompatibleDimensionsException();
	Vector res(vec1.size());
	for (int i = 0; i < res.size(); ++i) res[i] = vec1[i] - vec2[i];
	return res;
}

float Vector::Dot(const Vector& vec1, const Vector& vec2) {
	if (!Vector::compareSize(vec1, vec2)) throw VectorIncompatibleDimensionsException();
	float dot = 0;
	for (int i = 0; i < vec1.size(); ++i) dot += vec1[i] * vec2[i];
	return dot;
}

Vector Vector::Cross(const Vector& vec1, const Vector& vec2) {
	if (vec1.size() != 3 || vec2.size() != 3) throw VectorIncompatibleDimensionsException();
	else if (!Vector::compareSize(vec1, vec2)) throw VectorIncompatibleDimensionsException();
	Vector res(vec1.size());
	res[0] = vec1[1] * vec2[2] - vec1[2] * vec2[1];
	res[1] = vec1[2] * vec2[0] - vec1[0] * vec2[2];
	res[2] = vec1[0] * vec2[1] - vec1[1] * vec2[0];
	return res;
}

Vector Vector::Scale(const Vector& vec, float s) {
	Vector res(vec.size());
	for (int i = 0; i < res.size(); ++i) res[i] = vec[i] * s;
	return res;
}

Vector Vector::Unit(const Vector& vec) {
	float inv_mag = 1 / Vector::Magnitude(vec);
	Vector res(vec);
	return res * inv_mag;
}

Vector Vector::Normalized(const Vector& vec) { return Vector::Unit(vec); }
float Vector::Magnitude(const Vector& vec) { return sqrtf(Vector::MagnitudeSquared(vec)); }
float Vector::MagnitudeSquared(const Vector& vec) { return Vector::Dot(vec, vec); }

void Vector::ClampMagnitude(Vector& vec, float mag) {
	float curMag = Vector::Magnitude(vec);
	if (curMag > mag) {
		float mag_ratio = mag / curMag;
		vec = Vector::Scale(vec, mag_ratio);
	}
}

void Vector::SetMagnitude(Vector& vec, float mag) {
	float mag_ratio = mag / Vector::Magnitude(vec);
	vec = Vector::Scale(vec, mag_ratio);
}

Vector Vector::Add(const Vector& vec) { return Vector::Add(*this, vec); }
Vector Vector::Sub(const Vector& vec) { return Vector::Sub(*this, vec); }
float Vector::Dot(const Vector& vec) { return Vector::Dot(*this, vec); }
Vector Vector::Cross(const Vector& vec) { return Vector::Cross(*this, vec); }
Vector Vector::Scale(float s) { return Vector::Scale(*this, s); }

Vector Vector::Unit() { return Vector::Unit(*this); }
Vector Vector::Normalized() { return Vector::Normalized(*this); }
float Vector::Magnitude() { return Vector::Magnitude(*this); }
float Vector::MagnitudeSquared() { return Vector::MagnitudeSquared(*this); }
void Vector::ClampMagnitude(float mag) { Vector::ClampMagnitude(*this, mag); }
void Vector::SetMagnitude(float mag) { Vector::SetMagnitude(*this, mag); }

Vector Vector::operator+ (const Vector& vec) { return Vector::Add(*this, vec); }
Vector Vector::operator- (const Vector& vec) { return Vector::Sub(*this, vec); }
Vector Vector::operator* (float s) { return Vector::Scale(*this, s); }

Vector operator* (float s, const Vector& vec) { return Vector::Scale(vec, s); }

Vector& Vector::operator+= (const Vector& vec) {
	if (!Vector::compareSize(*this, vec)) throw VectorIncompatibleDimensionsException();
	for (int i = 0; i < this->size(); ++i) (*this)[i] += vec[i];
	return *this;
}

Vector& Vector::operator-= (const Vector& vec) {
	if (!Vector::compareSize(*this, vec)) throw VectorIncompatibleDimensionsException();
	for (int i = 0; i < this->size(); ++i) (*this)[i] -= vec[i];
	return *this;
}

Vector& Vector::operator*= (float s) {
	for (int i = 0; i < this->size(); ++i) (*this)[i] *= s;
	return *this;
}
//===========================CASTING====================================

Vector::operator Vector2() { return Vector2(this->X(), this->Y()); }
Vector::operator Vector3() { return Vector3(this->X(), this->Y(), this->Z()); }
Vector::operator Vector4() { return Vector4(this->X(), this->Y(), this->Z(), this->W()); }

Vector::operator std::string() { return this->ToString(); }

//===========================PRIVATE====================================

void Vector::setValues(int m, const std::vector<float>& vals) {
	int size = vals.size();

	std::cout << "size: " << size << std::endl;
	std::cout << "m: " << m << std::endl;

	if (m < Matrix::MIN_DIMMENSION_SIZE) m = Matrix::MIN_DIMMENSION_SIZE;
	if (m > Matrix::MAX_DIMMENSION_SIZE) m = Matrix::MAX_DIMMENSION_SIZE;


	std::cout << "m: " << m << std::endl;


	for (int i = 0; i < m; ++i) {
		if (i < size) this->set(i, vals[i]);
		else this->set(i, 0);
	}
}
//=======================OUTPUT==========================

std::ostream& operator<<(std::ostream& os, const Vector& vec) { os << vec.ToString(); return os; }
std::string Vector::ToString() const {
	std::stringstream ss;
	ss << "< ";
	for (int i = 0; i < this->size(); ++i) ss << (*this)[i] << " ";
	ss << ">";
	return ss.str();
}

void Vector::print(const char* label) const { this->Matrix::print(label); }
void Vector::print() const {
	std::cout << "( size = " << this->size() << " )" << std::endl;
	std::cout << "< ";
	for (int i = 0; i < this->size(); ++i) {
		std::cout << this->get(i) << " ";
	}
	std::cout << ">" << std::endl;
}

//=====================VECTOR PRESETS==========================

Vector2::Vector2() : Vector(2) {}
Vector2::Vector2(float x, float y) : Vector(2) { this->X(x); this->Y(y); }
Vector2::Vector2(const std::vector<float>& vals) : Vector(2, vals) {}
Vector2::Vector2(const Vector2& vec) : Vector(vec) {}

Vector2 Vector2::Zero() { return Vector2(); }
Vector2::operator Vector3() { return Vector3(this->X(), this->Y(), 0); }
Vector2::operator Vector4() { return Vector4(this->X(), this->Y(), 0, 0); }


Vector3::Vector3() : Vector(3) {}
Vector3::Vector3(float x, float y, float z) : Vector(3) { this->X(x); this->Y(y); this->Z(z); }
Vector3::Vector3(const std::vector<float>& vals) : Vector(3, vals) {}
Vector3::Vector3(const Vector3& vec) : Vector(vec) {}

Vector3 Vector3::Zero() { return Vector3(); }
Vector3::operator Vector2() { return Vector2(this->X(), this->Y()); }
Vector3::operator Vector4() { return Vector4(this->X(), this->Y(), this->Z(), 0); }


Vector4::Vector4() : Vector(4) {}
Vector4::Vector4(float x, float y, float z, float w) : Vector(4) { this->X(x); this->Y(y); this->Z(z); this->W(w); }
Vector4::Vector4(const std::vector<float>& vals) : Vector(4, vals) {}
Vector4::Vector4(const Vector4& vec) : Vector(vec) {}

Vector4 Vector4::Zero() { return Vector4(); }
Vector4::operator Vector2() { return Vector2(this->X(), this->Y()); }
Vector4::operator Vector3() { return Vector3(this->X(), this->Y(), this->Z()); }
