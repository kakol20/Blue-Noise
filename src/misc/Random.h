#ifndef RANDOM_H
#define RANDOM_H

#include "../math/Fixed.h"

class Random {
public:
	Random() {};
	~Random() {};

	static thread_local unsigned int Seed;
	static const int MaxVal = 2047;

	/// <summary>
	/// Since the return is a signed fpm::fixed&lt;std::int32_t, std::int64_t, 20&gt; the highest positive int is 11 bits long but will still use 32 bit seed
	/// </summary>
	/// <param name="bitCount">max 11</param>
	/// <returns>a positive integer between 0 and 2047</returns>
	static Fixed RandomPInt(const unsigned int bitCount = 11);

	static Fixed RandomFloat(const Fixed& min = 0, const Fixed& max = 1);
};

#endif // !RANDOM_H
