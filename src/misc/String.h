#pragma once
#include <iostream>
#include <string>

class String {
public:
	String(const char copyChar);
	String(const char* copyString = "");
	String(const std::string& copyString);
	String(const String& copyString);

	~String() {};

	// ----- ASSIGNMENT -----

	String& operator=(const char copyChar);
	String& operator=(const char* copyString);
	String& operator=(const std::string& copyString);
	String& operator=(const String& copyString);

	String& operator+=(const char copyChar);
	String& operator+=(const char* copyString);
	String& operator+=(const std::string& copyString);
	String& operator+=(const String& copyString);

	// ----- ARITHMETIC -----
	String operator+(const char right) const;
	String operator+(const char* right) const;
	String operator+(const float right) const;
	String operator+(const int right) const;
	String operator+(const String& right) const;
	String operator+(const unsigned int right) const;

	// ----- COMPARISON -----

	bool operator==(const char* otherString) const;
	bool operator==(const String& otherString) const;

	bool operator!=(const char* otherString) const;
	bool operator!=(const String& otherString) const;

	bool operator<(const String& otherString) const;

	// ----- GETTERS -----

	const char* GetChar() const { return m_string.c_str(); };
	size_t Length() { return m_string.length(); };

	const std::string GetFirst(const char delimiter) const;
	const std::string GetSecond(const char delimiter) const;

	// ----- IOSTREAM -----

	friend std::istream& operator>>(std::istream& is, String& string);
	friend std::ostream& operator<<(std::ostream& os, const String& string);

	// ----- CONVERSIONS -----

	static String ToString(const float number);
	static String ToString(const int number);
	static String ToString(const unsigned int number);

	static float ToFloat(const char* number);
	static float ToFloat(const String& number);
	static int ToInt(const char* number);
	static int ToInt(const String& number);
	static unsigned int ToUInt(const char* number);
	static unsigned int ToUInt(const String& number);

	// ----- OTHER -----

	void Clear();
private:
	std::string m_string;
};
