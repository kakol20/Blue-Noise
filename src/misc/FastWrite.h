#ifndef FASTWRITE_H
#define FASTWRITE_H

#include <string>

class FastWrite {
public:
	FastWrite() {};
	~FastWrite() {};

	static auto EnableVTMode() -> void;

	static void Reset();
	static void Write(std::string output);
};

#endif // !FASTWRITE_H
