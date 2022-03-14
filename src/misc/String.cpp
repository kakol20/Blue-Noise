#include "String.h"

String::String(const char copyChar) {
	m_string = copyChar;
}

String::String(const char* copyString) {
	m_string = copyString;
}

String::String(const std::string& copyString) {
	m_string = copyString;
}

String::String(const String& copyString) {
	m_string = copyString.m_string;
}

String& String::operator=(const char copyChar) {
	m_string = copyChar;
	return *this;
}

String& String::operator=(const char* copyString) {
	m_string = copyString;
	return *this;
}

String& String::operator=(const std::string& copyString) {
	m_string = copyString;
	return *this;
}

String& String::operator=(const String& copyString) {
	if (this == &copyString) return *this;

	m_string = copyString.m_string;
	return *this;
}

String& String::operator+=(const char copyChar) {
	m_string += copyChar;
	return *this;
}

String& String::operator+=(const char* copyString) {
	m_string += copyString;
	return *this;
}

String& String::operator+=(const std::string& copyString) {
	m_string += copyString;
	return *this;
}

String& String::operator+=(const String& copyString) {
	m_string += copyString.m_string;
	return *this;
}

String String::operator+(const char right) const {
	String out = m_string;
	out += right;
	return out;
}

String String::operator+(const char* right) const {
	String out = m_string;
	out += right;
	return out;
}

String String::operator+(const float right) const {
	String out = m_string;
	out += String::ToString(right);
	return out;
}

String String::operator+(const int right) const {
	String out = m_string;
	out += String::ToString(right);
	return out;
}

String String::operator+(const String& right) const {
	String out = m_string;
	out += right;
	return out;
}

String String::operator+(const unsigned int right) const {
	String out = m_string;
	out += String::ToString(right);
	return out;
}

bool String::operator==(const char* otherString) const {
	return m_string == otherString;
}

bool String::operator==(const String& otherString) const {
	return m_string == otherString.m_string;
}

bool String::operator!=(const char* otherString) const {
	return m_string != otherString;
}

bool String::operator!=(const String& otherString) const {
	return m_string != otherString.m_string;
}

bool String::operator<(const String& otherString) const {
	return m_string < otherString.m_string;
}

const std::string String::GetFirst(const char delimiter) const {
	std::string first;

	//bool out = true;
	for (auto c : m_string) {
		if (c == delimiter) {
			break;
		}
		else {
			first += c;
		}
	}

	return first;
}

const std::string String::GetSecond(const char delimiter) const {
	std::string second;

	bool firstOut = true;
	for (auto c : m_string) {
		if (firstOut) {
			if (c == delimiter) {
				firstOut = false;
			}
		}
		else {
			second += c;
		}
	}

	return second;
}

void String::Clear() {
	m_string.clear();
}

String String::ToString(const float number) {
	return String(std::to_string(number));
}

String String::ToString(const int number) {
	return String(std::to_string(number));
}

String String::ToString(const unsigned int number) {
	return String(std::to_string(number));
}

float String::ToFloat(const char* number) {
	return std::stof(number);
}

float String::ToFloat(const String& number) {
	return std::stof(number.m_string);
}

int String::ToInt(const char* number) {
	return std::stoi(number);
}

int String::ToInt(const String& number) {
	return std::stoi(number.m_string);
}

unsigned int String::ToUInt(const char* number) {
	return (unsigned int)std::stoul(number);
}

unsigned int String::ToUInt(const String& number) {
	return (unsigned int)std::stoul(number.m_string);
}

std::istream& operator>>(std::istream& is, String& string) {
	string.Clear();

	std::string tempString;

	std::getline(is, tempString);

	string = tempString;

	return is;
}

std::ostream& operator<<(std::ostream& os, const String& string) {
	os << string.GetChar();
	return os;
}
