#include "../../ext/fpm/ios.hpp"
#include "../../ext/fpm/math.hpp"

#include "Fixed.h"

Fixed::Fixed(const double& n) {
	m_num = Fixed::CustomFixed{ n };
}

Fixed::Fixed(const Fixed& n) {
	m_num = n.m_num;
}

Fixed::Fixed(const Fixed::CustomFixed& n) {
	m_num = n;
}

Fixed::Fixed(const float& n) {
	m_num = Fixed::CustomFixed{ n };
}

Fixed::Fixed(const int& n) {
	m_num = Fixed::CustomFixed{ n };
}

Fixed::Fixed(const unsigned int& n) {
	m_num = Fixed::CustomFixed{ n };
}

Fixed& Fixed::operator%=(const Fixed& n) {
	m_num = fpm::fmod(m_num, n.m_num);
	return *this;
}

Fixed& Fixed::operator*=(const Fixed& n) {
	m_num *= n.m_num;
	return *this;
}

Fixed& Fixed::operator/=(const Fixed& n) {
	m_num /= n.m_num;
	return *this;
}

Fixed& Fixed::operator+=(const Fixed& n) {
	m_num += n.m_num;
	return *this;
}

Fixed& Fixed::operator=(const Fixed& n) {
	if (this == &n) return *this;

	m_num = n.m_num;

	return *this;
}

Fixed& Fixed::operator-=(const Fixed& n) {
	m_num -= n.m_num;
	return *this;
}

Fixed Fixed::operator%(const Fixed& n) const {
	Fixed out = m_num;
	out %= n;
	return out;
}

Fixed Fixed::operator-(const Fixed& n) const {
	Fixed out = m_num;
	out -= n;
	return out;
}

Fixed Fixed::operator*(const Fixed& n) const {
	Fixed out = m_num;
	out *= n;
	return out;
}

Fixed Fixed::operator/(const Fixed& n) const {
	Fixed out = m_num;
	out /= n;

#ifdef _DEBUG
	Fixed l_n = n;

	Fixed::FlOrDo numDebug = static_cast<Fixed::FlOrDo>(m_num);
	Fixed::FlOrDo nDebug = l_n.ToFloat();
	Fixed::FlOrDo outDebug = out.ToFloat();
#endif // _DEBUG

	return out;
}

Fixed Fixed::operator+(const Fixed& n) const {
	Fixed out = m_num;
	out += n;
	return out;
}

Fixed Fixed::operator-() const {
	Fixed out = m_num;
	out *= -1;
	return out;
}

bool Fixed::operator!=(const Fixed& n) const {
	return m_num != n.m_num;
}

bool Fixed::operator<(const Fixed& n) const {
	return m_num < n.m_num;
}

bool Fixed::operator<=(const Fixed& n) const {
	return m_num <= n.m_num;
}

bool Fixed::operator==(const Fixed& n) const {
	return m_num == n.m_num;
}

bool Fixed::operator>(const Fixed& n) const {
	return m_num > n.m_num;
}

bool Fixed::operator>=(const Fixed& n) const {
	return m_num >= n.m_num;
}

Fixed Fixed::operator--(int) {
	Fixed original = m_num;
	m_num -= 1;
	return original;
}

Fixed Fixed::operator++(int) {
	Fixed original = m_num;
	m_num += 1;
	return original;
}

Fixed& Fixed::operator--() {
	m_num -= 1;
	return *this;
}

Fixed& Fixed::operator++() {
	m_num += 1;
	return *this;
}

Fixed Fixed::Max() {
	return Fixed(std::numeric_limits<Fixed::CustomFixed>::max());
}

Fixed Fixed::Min() {
	return Fixed(std::numeric_limits<Fixed::CustomFixed>::min());
}

Fixed Fixed::Max(const Fixed& a, const Fixed& b) {
	return a >= b ? a : b;
}

Fixed Fixed::Min(const Fixed& a, const Fixed& b) {
	return a <= b ? a : b;
}

Fixed::FlOrDo Fixed::ToFloat() {
	return static_cast<Fixed::FlOrDo>(m_num);
}

int Fixed::ToInt() {
	return static_cast<int>(m_num);
}

unsigned int Fixed::ToUInt() {
	return static_cast<unsigned int>(m_num);
}

Fixed operator-(const Fixed::FlOrDo& l, const Fixed& r) {
	Fixed out = Fixed(l) - r;
	return out;
}

Fixed operator-(const int& l, const Fixed& r) {
	Fixed out = Fixed(l) - r;
	return out;
}

Fixed operator*(const Fixed::FlOrDo& l, const Fixed& r) {
	Fixed out = r * l;
	return out;
}

Fixed operator*(const int& l, const Fixed& r) {
	Fixed out = r * l;
	return out;
}

Fixed operator/(const Fixed::FlOrDo& l, const Fixed& r) {
	Fixed out = Fixed(l) / r;
	return out;
}

Fixed operator/(const int& l, const Fixed& r) {
	Fixed out = Fixed(l) / r;
	return out;
}

Fixed operator+(const Fixed::FlOrDo& l, const Fixed& r) {
	Fixed out = r + l;
	return out;
}

Fixed operator+(const int& l, const Fixed& r) {
	Fixed out = r + l;
	return out;
}

std::istream& operator>>(std::istream& is, Fixed& num) {
	is >> num.m_num;
	return is;
}

std::ostream& operator<<(std::ostream& os, const Fixed& num) {
	os << num.m_num;
	return os;
}

Fixed Fixed::Abs(const Fixed& v) {
	if (v < 0) return v * -1;
	return v;
}

Fixed Fixed::Asin(const Fixed& x) {
	return fpm::asin(x.m_num);
}

Fixed Fixed::Atan2(const Fixed& y, const Fixed& x) {
	return fpm::atan2(y.m_num, x.m_num);
}

Fixed Fixed::Ceil(const Fixed& v) {
	return fpm::ceil(v.m_num);
}

Fixed Fixed::Clamp(const Fixed& v, const Fixed& lo, const Fixed& hi) {
	Fixed out = v;
	if (out < Fixed::Min(lo, hi)) out = Fixed::Min(lo, hi);
	if (out > Fixed::Max(lo, hi)) out = Fixed::Max(lo, hi);
	return out;
}

Fixed Fixed::Cos(const Fixed& x) {
	return fpm::cos(x.m_num);
}

Fixed Fixed::Floor(const Fixed& v) {
	return fpm::floor(v.m_num);
}

Fixed Fixed::Lerp(const Fixed& from, const Fixed& to, const Fixed& factor, bool clamp) {
	Fixed out = ((to - from) * factor) + from;

	if (clamp) out = Fixed::Clamp(out, from, to);

	return out;
}

Fixed Fixed::Map(const Fixed& v, const Fixed& fromMin, const Fixed& fromMax, const Fixed& toMin, const Fixed& toMax) {
	Fixed factor = (v - fromMin) / (fromMax - fromMin);
	return Fixed::Lerp(toMin, toMax, factor);
}

Fixed Fixed::Pow(const Fixed& base, const Fixed& exponent) {
	return fpm::pow(base.m_num, exponent.m_num);
}

Fixed Fixed::Round(const Fixed& v) {
	return fpm::round(v.m_num);
}

Fixed Fixed::Sin(const Fixed& x) {
	return fpm::sin(x.m_num);
}

Fixed Fixed::Sqrt(const Fixed& v) {
	return fpm::sqrt(v.m_num);
}

Fixed Fixed::Cubic(const Fixed& a, const Fixed& b, const Fixed& c, const Fixed& d, const Fixed& factor) {
	// https://www.paulinternet.nl/?page=bicubic

//#define method1

#ifdef method1
	Fixed fCubed = Fixed::Pow(factor, 3);
	Fixed fSquared = Fixed::Pow(factor, 2);

	Fixed part1 = (-a + (3 * b) - (3 * c) + d) * fCubed;
	Fixed part2 = (-a + c) * factor;
	Fixed part3 = ((-5 * b) - d) * fSquared;

	Fixed out = part1 + part2 + part3;
	out /= 2;
	return out + (a * fSquared) + (2 * fSquared * c) + b;
#else

	return b + (Fixed::FlOrDo)0.5 * factor * (c - a + factor * (2 * a - 5 * b + 4 * c - d + factor * (3 * (b - c) + d - a)));
#endif // method1
}
