#ifndef VECTOR3D_H
#define VECTOR3D_H

#include <iostream>

#include "Fixed.h"

class Vector3D {
public:
	Vector3D(const Fixed& scalar = 0);
	Vector3D(const Fixed& x, const Fixed& y, const Fixed& z);
	Vector3D(const Vector3D& copyVector);
	~Vector3D() {};

	// ----- ASSIGNMENT OPERATORS -----

	Vector3D& operator*=(const Vector3D& otherVector);
	Vector3D& operator/=(const Vector3D& otherVector);
	Vector3D& operator+=(const Vector3D& otherVector);
	Vector3D& operator=(const Vector3D& otherVector);
	Vector3D& operator-=(const Vector3D& otherVector);

	Vector3D& operator*=(const Fixed& scalar);
	Vector3D& operator/=(const Fixed& scalar);
	Vector3D& operator=(const Fixed& scalar);

	// ----- ARITHMETIC OPERATOR -----

	Vector3D operator-(const Vector3D& otherVector) const;
	Vector3D operator*(const Vector3D& otherVector) const;
	Vector3D operator/(const Vector3D& otherVector) const;
	Vector3D operator+(const Vector3D& otherVector) const;

	Vector3D operator*(const Fixed& scalar) const;
	Vector3D operator/(const Fixed& scalar) const;

	/// <summary>
	/// Shorthand for multiplying by -1;
	/// </summary>
	/// <returns></returns>
	Vector3D operator-() const;

	// ----- GETTERS -----

	Fixed GetX() { return m_x; };
	Fixed GetY() { return m_y; };
	Fixed GetZ() { return m_z; };

	// ----- OTHER -----

	static Fixed DotProduct(const Vector3D& v1, const Vector3D& v2);
	static Fixed ToroidalDistance(const Vector3D& a, const Vector3D& b, const Vector3D& min, const Vector3D& max);
	static Vector3D Abs(const Vector3D& v);
	static Vector3D Clamp(const Vector3D& val, const Vector3D& min, const Vector3D& max);
	static Vector3D CrossProduct(const Vector3D& v1, const Vector3D& v2);
	static Vector3D RandomInHemisphere(const Vector3D& normal);
	static Vector3D RandomInUnitDisk();
	static Vector3D RandomInUnitSphere();
	static Vector3D RandomUnitVector();
	static Vector3D RandomVector(const Fixed& min = 0, const Fixed& max = 1, bool withZAxis = true);

	static Vector3D Floor(const Vector3D& v);

	Fixed Magnitude();
	Fixed SqrMagnitude();
	Vector3D UVSphere();
	void Normalize();
	void WithZAxis(bool withZAxis);

	// ----- friend FUNCTIONS -----

	friend std::ostream& operator<<(std::ostream& os, const Vector3D& otherVector);

private:
	Fixed m_x;
	Fixed m_y;
	Fixed m_z;

	bool m_withZAxis;
};

#endif // !VECTOR3D_H
