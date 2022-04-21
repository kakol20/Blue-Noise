#include "Random.h"

Fixed Random::RandomPInt(const unsigned int bitCount) {
    unsigned int count = bitCount > 11 ? 11 : bitCount;
    int out = 0;

    if (Random::Seed == 0) Random::Seed = 1;

    for (int i = (int)count - 1; i >= 0; i--) {
        out = out | ((Random::Seed & 0b1) << i);

        unsigned int newBit = Random::Seed ^ (Random::Seed >> 1) ^ (Random::Seed >> 21) ^ (Random::Seed >> 31);
        newBit = newBit & 1;

        Random::Seed = (Random::Seed >> 1) | (newBit << 31);
    }
    return Fixed(out);
}

Fixed Random::RandomFloat(const Fixed& min, const Fixed& max) {
    Fixed random = Random::RandomPInt();
    random /= Random::MaxVal;
    return (random * (max - min)) + min;
}
