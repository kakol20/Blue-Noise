#include "../misc/Random.h"	

#include "Vector3D.h"

Vector3D::Vector3D(const Fixed& scalar) : Vector3D(scalar, scalar, scalar) {
}

Vector3D::Vector3D(const Fixed& x, const Fixed& y, const Fixed& z) {
	m_x = x;
	m_y = y;
	m_z = z;
}

Vector3D::Vector3D(const Vector3D& copyVector) : Vector3D(copyVector.m_x, copyVector.m_y, copyVector.m_z) {
}

Vector3D& Vector3D::operator*=(const Vector3D& otherVector) {
	m_x *= otherVector.m_x;
	m_y *= otherVector.m_y;
	m_z *= otherVector.m_z;
	return *this;
}

Vector3D& Vector3D::operator/=(const Vector3D& otherVector) {
	m_x /= otherVector.m_x;
	m_y /= otherVector.m_y;
	m_z /= otherVector.m_z;
	return *this;
}

Vector3D& Vector3D::operator+=(const Vector3D& otherVector) {
	m_x += otherVector.m_x;
	m_y += otherVector.m_y;
	m_z += otherVector.m_z;
	return *this;
}

Vector3D& Vector3D::operator=(const Vector3D& otherVector) {
	if (this == &otherVector) return *this;
	m_x = otherVector.m_x;
	m_y = otherVector.m_y;
	m_z = otherVector.m_z;
	return *this;
}

Vector3D& Vector3D::operator-=(const Vector3D& otherVector) {
	m_x -= otherVector.m_x;
	m_y -= otherVector.m_y;
	m_z -= otherVector.m_z;
	return *this;
}

Vector3D& Vector3D::operator*=(const Fixed& scalar) {
	m_x *= scalar;
	m_y *= scalar;
	m_z *= scalar;
	return *this;
}

Vector3D& Vector3D::operator/=(const Fixed& scalar) {
	m_x /= scalar;
	m_y /= scalar;
	m_z /= scalar;
	return *this;
}

Vector3D& Vector3D::operator=(const Fixed& scalar) {
	m_x = scalar;
	m_y = scalar;
	m_z = scalar;
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
	return Vector3D(m_x, m_y, m_z) * scalar;
}

Vector3D Vector3D::operator/(const Fixed& scalar) const {
	return Vector3D(m_x, m_y, m_z) / scalar;
}

Vector3D Vector3D::operator-() const {
	return Vector3D(m_x, m_y, m_z) * -1;
}

Fixed Vector3D::DotProduct(const Vector3D& v1, const Vector3D& v2) {
	return v1.m_x * v2.m_x + v1.m_y * v2.m_y + v1.m_z * v2.m_z;
}

Fixed Vector3D::ToroidalDistance(const Vector3D& a, const Vector3D& b, const Vector3D& min, const Vector3D& max) {
	Vector3D delta = Vector3D::Abs(a - b);
	Vector3D minMaxDelta = Vector3D::Abs(max - min);
	Vector3D mid = minMaxDelta / 2;

	if (delta.m_x > mid.m_x) delta.m_x = minMaxDelta.m_x - delta.m_x;
	if (delta.m_y > mid.m_y) delta.m_y = minMaxDelta.m_y - delta.m_y;
	if (delta.m_z > mid.m_z) delta.m_z = minMaxDelta.m_z - delta.m_z;

	return delta.Magnitude();
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
	Vector3D o = Vector3D(Random::RandomFloat(-1, 1), Random::RandomFloat(-1, 1), 0);

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

Vector3D Vector3D::RandomVector(const Fixed& min, const Fixed& max) {
	return Vector3D(Random::RandomFloat(min, max), Random::RandomFloat(min, max), Random::RandomFloat(min, max));
}

Fixed Vector3D::Magnitude() {
	Fixed sqrMag = SqrMagnitude();

	if (sqrMag == 1) return 1;
	return Fixed::Sqrt(sqrMag);
}

Fixed Vector3D::SqrMagnitude() {
	return (m_x * m_x) + (m_y * m_y) + (m_z * m_z);
}

Vector3D Vector3D::UVSphere() {
	return Vector3D(0.5 + (Fixed::Atan2(m_x, m_z) / Fixed::TAU), 0.5 - (Fixed::Asin(m_y) / Fixed::PI), 0);
}

void Vector3D::Normalize() {
	Fixed length = Magnitude();
	if (length != 1) {
		m_x /= length;
		m_y /= length;
		m_z /= length;
	}
}

std::ostream& operator<<(std::ostream& os, const Vector3D& otherVector) {
	os << "( " << otherVector.m_x << ", " << otherVector.m_y << ", " << otherVector.m_z << ")";
	return os;
}
