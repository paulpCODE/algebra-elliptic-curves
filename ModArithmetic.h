#pragma once
#include "pch.h"
#include <vector>
#include <string>
#include <sstream>
#include "LongInt.h"


class LongModInt;

struct ModField
{
	LongInt mod;

	ModField(const LongInt& mod);
	ModField(const std::string& str);
};

class LongModInt
{
private:
	ModField* field;

public:
	LongInt num;

	LongModInt();
	LongModInt(const std::string& num, ModField* field);
	LongModInt(const LongInt& num, ModField* field);
	ModField* getField() const;

	// ~x is x^-1
	LongModInt operator ~() const;
	LongModInt operator -() const;
	LongModInt operator /(const LongModInt& number2) const;
	LongModInt operator *(const LongModInt& number2) const;
	LongModInt operator -(const LongModInt& number2) const;
	LongModInt operator +(const LongModInt& number2) const;

	friend std::ostream& operator <<(std::ostream& stream, const LongModInt& number);

	friend bool operator >(const LongModInt& number1, const LongModInt& number2);
	friend bool operator <(const LongModInt& number1, const LongModInt& number2);
	friend bool operator <=(const LongModInt& number1, const LongModInt& number2);
	friend bool operator >=(const LongModInt& number1, const LongModInt& number2);
	friend bool operator ==(const LongModInt& number1, const LongModInt& number2);
	friend bool operator !=(const LongModInt& number1, const LongModInt& number2);

	//Functions with strings, for convenience
	bool operator !=(const std::string&) const;
	bool operator ==(const std::string&) const;

	LongModInt operator /(const std::string& number2) const;
	LongModInt operator *(const std::string& number2) const;
	LongModInt operator -(const std::string& number2) const;
	LongModInt operator +(const std::string& number2) const;

	friend LongModInt operator /(const std::string& number1, const LongModInt& number2);
	friend LongModInt operator *(const std::string& number1, const LongModInt& number2);
	friend LongModInt operator -(const std::string& number1, const LongModInt& number2);
	friend LongModInt operator +(const std::string& number1, const LongModInt& number2);
};


