#include <iostream>

#include "misc/Random.h"

thread_local unsigned int Random::Seed = 1;

int main() {
	std::cout << "Hello World!\n";
	std::cout << "Random Int: " << Random::RandInt() << '\n';

	std::system("pause");

	return 0;
}