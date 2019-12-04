#pragma once
#include "pch.h"
#include <vector>
#include <string>
#include <sstream>

class LongInt
{
private:
	LongInt(const std::vector<int>& number);

	std::vector<int> x;
	bool negative;

	void removeZeros();
	void shiftRight();
	void revert(int size);



public:
	LongInt();
	LongInt(long long number);
	LongInt(const std::string& str);

	bool isNegative() const;

	friend bool operator >(const LongInt& number1, const LongInt& number2);
	friend bool operator <(const LongInt& number1, const LongInt& number2);
	friend bool operator <=(const LongInt& number1, const LongInt& number2);
	friend bool operator >=(const LongInt& number1, const LongInt& number2);
	friend bool operator ==(const LongInt& number1, const LongInt& number2);
	friend bool operator !=(const LongInt& number1, const LongInt& number2);

	int getSize() const;
	static LongInt gcdExtended(const LongInt& a, const LongInt& b, LongInt& x, LongInt& y);
	LongInt operator -() const;
	LongInt operator /(const LongInt& number2) const;
	LongInt operator *(const LongInt& number2) const;
	LongInt operator -(LongInt number2) const;
	LongInt operator +(LongInt number2) const;
	LongInt operator %(const LongInt& number2) const;


	friend std::ostream& operator <<(std::ostream& stream, const LongInt& number);


};