#ifndef FIXED_H
#define FIXED_H

#include <iostream>

#include "../../ext/fpm/fixed.hpp"

class Fixed {
public:
	//using CustomFixed = fpm::fixed<int_least32_t, intmax_t, 20>;

	typedef fpm::fixed<int_least32_t, intmax_t, 20> CustomFixed;

#ifdef WIN32
	// float or double
	typedef float FlOrDo;
#else
	// float or double
	typedef double FlOrDo;
#endif // WIN32

	Fixed(const double& n);
	Fixed(const Fixed& n);
	Fixed(const Fixed::CustomFixed& n);
	Fixed(const float& n);
	Fixed(const int& n = 0);
	Fixed(const unsigned int& n);
	~Fixed() {};

	// ----- ASSIGNMENT OPERATORS -----

	Fixed& operator%=(const Fixed& n);
	Fixed& operator*=(const Fixed& n);
	Fixed& operator/=(const Fixed& n);
	Fixed& operator+=(const Fixed& n);
	Fixed& operator=(const Fixed& n);
	Fixed& operator-=(const Fixed& n);

	// ----- ARITHMETIC OPERATOR -----

	Fixed operator%(const Fixed& n) const;
	Fixed operator-(const Fixed& n) const;
	Fixed operator*(const Fixed& n) const;
	Fixed operator/(const Fixed& n) const;
	Fixed operator+(const Fixed& n) const;

	friend Fixed operator-(const Fixed::FlOrDo& l, const Fixed& r);
	friend Fixed operator-(const int& l, const Fixed& r);
	friend Fixed operator*(const Fixed::FlOrDo& l, const Fixed& r);
	friend Fixed operator*(const int& l, const Fixed& r);
	friend Fixed operator/(const Fixed::FlOrDo& l, const Fixed& r);
	friend Fixed operator/(const int& l, const Fixed& r);
	friend Fixed operator+(const Fixed::FlOrDo& l, const Fixed& r);
	friend Fixed operator+(const int& l, const Fixed& r);

	/// <summary>
	/// Shorthand for multiplying by -1;
	/// </summary>
	/// <returns></returns>
	Fixed operator-() const;

	// ----- COMPARISON OPERATORS -----

	bool operator!=(const Fixed& n) const;
	bool operator<(const Fixed& n) const;
	bool operator<=(const Fixed& n) const;
	bool operator==(const Fixed& n) const;
	bool operator>(const Fixed& n) const;
	bool operator>=(const Fixed& n) const;

	// ----- INCREMENT/DECREMENT OPERATORS -----

	Fixed operator--(int);
	Fixed operator++(int);
	Fixed& operator--();
	Fixed& operator++();

	// ----- IOSTREAM -----

	friend std::istream& operator>>(std::istream& is, Fixed& num);
	friend std::ostream& operator<<(std::ostream& os, const Fixed& num);

	// ----- OTHER -----

	static const Fixed PI;
	static const Fixed TAU;

	static Fixed Max();
	static Fixed Min();

	static Fixed Max(const Fixed& a, const Fixed& b);
	static Fixed Min(const Fixed& a, const Fixed& b);

	Fixed::FlOrDo ToFloat();
	int ToInt();
	unsigned int ToUInt();

	static Fixed Abs(const Fixed& v);
	static Fixed Asin(const Fixed& x);
	static Fixed Atan2(const Fixed& y, const Fixed& x);
	static Fixed Ceil(const Fixed& v);
	static Fixed Clamp(const Fixed& v, const Fixed& lo, const Fixed& hi);
	static Fixed Cos(const Fixed& x);
	static Fixed Floor(const Fixed& v);
	static Fixed Lerp(const Fixed& from, const Fixed& to, const Fixed& factor, bool clamp = false);
	static Fixed Map(const Fixed& v, const Fixed& fromMin, const Fixed& fromMax, const Fixed& toMin, const Fixed& toMax);
	static Fixed Pow(const Fixed& base, const Fixed& exponent);
	static Fixed Round(const Fixed& v);
	static Fixed Sin(const Fixed& x);
	static Fixed Sqrt(const Fixed& v);

	// https://en.wikipedia.org/wiki/List_of_XML_and_HTML_character_entity_references

	/// <summary>
	/// Cubic interpolation
	/// </summary>
	/// <param name="a"></param>
	/// <param name="b">lower value</param>
	/// <param name="c">upper value</param>
	/// <param name="d"></param>
	/// <param name="factor">value between 0 &amp; 1</param>
	/// <returns></returns>
	static Fixed Cubic(const Fixed& a, const Fixed& b, const Fixed& c, const Fixed& d, const Fixed& factor);

private:
	Fixed::CustomFixed m_num;
};

#endif // !FIXED_H
