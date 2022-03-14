#include <iostream>

#include "misc/Random.h"
#include "misc/String.h"

thread_local unsigned int Random::Seed = 1;

int main() {
	std::cout << "Hello World!\n";
	std::cout << "Random Int: " << Random::RandInt() << '\n';
	
	String thisString = "string class ";
	std::cout << thisString << "first then const char* \n";
	std::cout << "const char* first then " << thisString << '\n';

	String addedString = thisString + 3.14159265f;
	std::cout << addedString << '\n';

	std::system("pause");

	return 0;
}