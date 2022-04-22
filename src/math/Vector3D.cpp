#include "../misc/Random.h"

#include "Vector3D.h"

Vector3D::Vector3D(const Fixed& scalar) : Vector3D(scalar, scalar, scalar) {
}

Vector3D::Vector3D(const Fixed& x, const Fixed& y, const Fixed& z) {
	m_x = x;
	m_y = y;
	m_z = z;
	m_withZAxis = true;
}

Vector3D::Vector3D(const Vector3D& copyVector) : Vector3D(copyVector.m_x, copyVector.m_y, copyVector.m_z) {
}

Vector3D& Vector3D::operator*=(const Vector3D& otherVector) {
	m_x *= otherVector.m_x;
	m_y *= otherVector.m_y;

	if (m_withZAxis) m_z *= otherVector.m_z;
	return *this;
}

Vector3D& Vector3D::operator/=(const Vector3D& otherVector) {
	m_x /= otherVector.m_x;
	m_y /= otherVector.m_y;
	if (m_withZAxis) m_z /= otherVector.m_z;
	return *this;
}

Vector3D& Vector3D::operator+=(const Vector3D& otherVector) {
	m_x += otherVector.m_x;
	m_y += otherVector.m_y;
	m_z += otherVector.m_z;
	if (m_withZAxis) m_z += otherVector.m_z;
	return *this;
}

Vector3D& Vector3D::operator=(const Vector3D& otherVector) {
	if (this == &otherVector) return *this;
	m_x = otherVector.m_x;
	m_y = otherVector.m_y;
	m_z = otherVector.m_z;
	m_withZAxis = otherVector.m_withZAxis;
	return *this;
}

Vector3D& Vector3D::operator-=(const Vector3D& otherVector) {
	m_x -= otherVector.m_x;
	m_y -= otherVector.m_y;
	m_z -= otherVector.m_z;
	if (m_withZAxis) m_z -= otherVector.m_z;
	return *this;
}

Vector3D& Vector3D::operator*=(const Fixed& scalar) {
	m_x *= scalar;
	m_y *= scalar;
	if (m_withZAxis) m_z *= scalar;
	return *this;
}

Vector3D& Vector3D::operator/=(const Fixed& scalar) {
	m_x /= scalar;
	m_y /= scalar;
	if (m_withZAxis) m_z /= scalar;
	return *this;
}

Vector3D& Vector3D::operator=(const Fixed& scalar) {
	m_x = scalar;
	m_y = scalar;
	if (m_withZAxis) m_z = scalar;
	return *this;
}

Vector3D Vector3D::operator-(const Vector3D& otherVector) const {
	Vector3D out = Vector3D(m_x, m_y, m_z);
	out -= otherVector;
	return out;
}

Vector3D Vector3D::operator*(const Vector3D& otherVector) const {
	Vector3D out = Vector3D(m_x, m_y, m_z);
	out *= otherVector;
	return out;
}

Vector3D Vector3D::operator/(const Vector3D& otherVector) const {
	Vector3D out = Vector3D(m_x, m_y, m_z);
	out /= otherVector;
	return out;
}

Vector3D Vector3D::operator+(const Vector3D& otherVector) const {
	Vector3D out = Vector3D(m_x, m_y, m_z);
	out += otherVector;
	return out;
}

Vector3D Vector3D::operator*(const Fixed& scalar) const {
	Vector3D out(m_x, m_y, m_z);
	out *= scalar;
	return out;
}

Vector3D Vector3D::operator/(const Fixed& scalar) const {
	Vector3D out(m_x, m_y, m_z);
	out /= scalar;
	return out;
}

Vector3D Vector3D::operator-() const {
	return Vector3D(m_x, m_y, m_z) * -1;
}

Fixed Vector3D::DotProduct(const Vector3D& v1, const Vector3D& v2) {
	Fixed addZ = v1.m_withZAxis || v2.m_withZAxis ? v1.m_z * v2.m_z : 0;
	return v1.m_x * v2.m_x + v1.m_y * v2.m_y + addZ;
}

Fixed Vector3D::ToroidalDistance(const Vector3D& a, const Vector3D& b, const Vector3D& min, const Vector3D& max) {
	Vector3D delta = Vector3D::Abs(b - a);
	delta.WithZAxis(a.m_withZAxis || b.m_withZAxis);

	Vector3D minMaxDelta = Vector3D::Abs(max - min);
	minMaxDelta.WithZAxis(delta.m_withZAxis);

	Vector3D mid = minMaxDelta / 2;
	mid.WithZAxis(delta.m_withZAxis);

	if (delta.m_x > mid.m_x) delta.m_x = minMaxDelta.m_x - delta.m_x;
	if (delta.m_y > mid.m_y) delta.m_y = minMaxDelta.m_y - delta.m_y;

	if (delta.m_withZAxis) {
		if (delta.m_z > mid.m_z) delta.m_z = minMaxDelta.m_z - delta.m_z;
	}

	//return delta.Magnitude();
	return Fixed::Abs(delta.SqrMagnitude());
}

Vector3D Vector3D::Abs(const Vector3D& v) {
	return Vector3D(Fixed::Abs(v.m_x), Fixed::Abs(v.m_y), Fixed::Abs(v.m_z));
}

Vector3D Vector3D::Clamp(const Vector3D& val, const Vector3D& min, const Vector3D& max) {
	return Vector3D(Fixed::Clamp(val.m_x, min.m_x, max.m_x), Fixed::Clamp(val.m_y, min.m_y, max.m_y), Fixed::Clamp(val.m_z, min.m_z, max.m_z));
}

Vector3D Vector3D::CrossProduct(const Vector3D& v1, const Vector3D& v2) {
	return Vector3D(v1.m_y * v2.m_z - v1.m_z * v2.m_y,
		v1.m_z * v2.m_x - v1.m_x * v2.m_z,
		v1.m_x * v2.m_y - v1.m_y * v2.m_x);
}

Vector3D Vector3D::RandomInHemisphere(const Vector3D& normal) {
	Vector3D o = Vector3D::RandomInUnitSphere();
	if (Vector3D::DotProduct(normal, o) < 0) {
		o *= -1;
	}
	return o;
}

Vector3D Vector3D::RandomInUnitDisk() {
	//Vector3D o = Vector3D(Random::RandomFloat(-1, 1), Random::RandomFloat(-1, 1), 0);
	Vector3D o = Vector3D::RandomVector(-1, 1, false);

	if (o.SqrMagnitude() >= 1) o.Normalize();
	return o;
}

Vector3D Vector3D::RandomInUnitSphere() {
	Vector3D o = RandomVector(-1, 1);

	if (o.SqrMagnitude() >= 1) o.Normalize();
	return o;
}

Vector3D Vector3D::RandomUnitVector() {
	Vector3D o = Vector3D::RandomVector(-1, 1);
	o.Normalize();
	return o;
}

Vector3D Vector3D::RandomVector(const Fixed& min, const Fixed& max, bool withZAxis) {
	Vector3D out = Vector3D(Random::RandomFloat(min, max), Random::RandomFloat(min, max), withZAxis ? Random::RandomFloat(min, max) : 0);
	out.WithZAxis(withZAxis);
	return out;
}

Vector3D Vector3D::Floor(const Vector3D& v) {
	return Vector3D(Fixed::Floor(v.m_x), Fixed::Floor(v.m_y), Fixed::Floor(v.m_z));
}

Fixed Vector3D::Magnitude() {
	Fixed sqrMag = SqrMagnitude();

	if (sqrMag == 1) return 1;
	return Fixed::Sqrt(sqrMag);
}

Fixed Vector3D::SqrMagnitude() {
	Fixed plusZ = m_withZAxis ? (m_z * m_z) : 0;
	return (m_x * m_x) + (m_y * m_y) + plusZ;
}

Vector3D Vector3D::UVSphere() {
	return Vector3D(0.5 + (Fixed::Atan2(m_x, m_z) / Fixed::TAU), 0.5 - (Fixed::Asin(m_y) / Fixed::PI), 0);
}

void Vector3D::Normalize() {
	Fixed length = Magnitude();
	if (length != 1) {
		m_x /= length;
		m_y /= length;

		if (m_withZAxis) m_z /= length;
	}
}

void Vector3D::WithZAxis(bool withZAxis) {
	m_z = withZAxis ? m_z : 0;
	m_withZAxis = withZAxis;
}

std::ostream& operator<<(std::ostream& os, const Vector3D& otherVector) {
	os << otherVector.m_x << "," << otherVector.m_y;

	if (otherVector.m_withZAxis) os << "," << otherVector.m_z;
	return os;
}