#include "pch.h"
#include "ModArithmetic.h"
#include <string>
#include <iostream>
#include <cassert>
#include <limits>

ModField::ModField(const LongInt& mod)
	: mod(mod)
{}

ModField::ModField(const std::string& str)
	: mod(str)
{}

LongModInt::LongModInt()
	: num(0), field(nullptr)
{}

LongModInt::LongModInt(const LongInt &num, ModField *field)
	: field(field)
{
	if (num > field->mod) {
		this->num = num % field->mod;
	}
	else if (num.isNegative()) {
		this->num = (field->mod - num) % field->mod;
	}
	else
		this->num = num;
}

LongModInt::LongModInt(const std::string &str, ModField *field)
	: LongModInt(LongInt(str), field)
{}

std::ostream& operator<<(std::ostream& stream, const LongModInt& number)
{
	stream << number.num;

//	stream << "(mod ";
//	for (int i = 0; i < number.m.size(); i++) {
//		stream << number.m[i];
//	}
//	stream << ")";

	return stream;
}

LongModInt LongModInt::operator~() const
{
	LongInt x, y;

	LongInt g = LongInt::gcdExtended(num, field->mod, x, y);
	if (g != LongInt(1))
	{
		throw std::invalid_argument("Inverse doesn't exist");
	}
	else
	{
		if (x > field->mod) {
			x = x % field->mod;
		}
		if (x.isNegative()) {
			x = x + field->mod;
		}
		return LongModInt(x, field);
	}
}

LongModInt LongModInt::operator/(const LongModInt& number2) const
{
	if(field->mod != number2.field->mod)
		throw std::invalid_argument("Moduli must be equal.");

	return *this * ~number2;
}

LongModInt LongModInt::operator *(const LongModInt& number2) const
{
	if(field->mod != number2.field->mod)
		throw std::invalid_argument("Moduli must be equal.");

	return LongModInt(num * number2.num % field->mod, field);
}

LongModInt LongModInt::operator +(const LongModInt& number2) const
{
	if(field->mod != number2.field->mod)
		throw std::invalid_argument("Moduli must be equal.");

    LongInt result = num + number2.num;
    if (result >= field->mod)
		return LongModInt(result - field->mod, field);
    else
    	return LongModInt(result, field);
}

LongModInt LongModInt::operator-(const LongModInt& number2) const
{
	if(field->mod != number2.field->mod)
		throw std::invalid_argument("Moduli must be equal.");

    if (number2 > *this)
	    return LongModInt(num - number2.num + field->mod, field);
    else
		return LongModInt(num - number2.num, field);
}


LongModInt LongModInt::operator-() const
{
	return LongModInt(LongInt(0), field) - *this;
}


bool operator<(const LongModInt& number1, const LongModInt& number2)
{
	return number1.num < number2.num;
}

bool operator>(const LongModInt& number1, const LongModInt& number2)
{
	return number1.num > number2.num;
}

bool operator<=(const LongModInt& number1, const LongModInt& number2)
{
	return number1.num <= number2.num;
}

bool operator>=(const LongModInt& number1, const LongModInt& number2)
{
	return number1.num >= number2.num;
}

bool operator==(const LongModInt& number1, const LongModInt& number2)
{
	return number1.num == number2.num;
}

bool operator!=(const LongModInt& number1, const LongModInt& number2)
{
	return number1.num != number2.num;
}


//Operators with strings, for convenience

LongModInt operator*(const std::string& number, const LongModInt& number2)
{
	return LongModInt(LongInt(number), number2.field) * number2;
}

LongModInt operator/(const std::string&  number, const LongModInt& number2)
{
	return LongModInt(LongInt(number), number2.field) / number2;
}

LongModInt operator+(const std::string& number, const LongModInt& number2)
{
	return LongModInt(LongInt(number), number2.field) + number2;
}

LongModInt operator-(const std::string& number, const LongModInt& number2)
{
	return LongModInt(LongInt(number), number2.field) - number2;
}


LongModInt LongModInt::operator/(const std::string& number2) const
{
	return *this / LongModInt(LongInt(number2), field);
}

LongModInt LongModInt::operator*(const std::string& number2) const
{
	return *this * LongModInt(LongInt(number2), field);
}

LongModInt LongModInt::operator-(const std::string& number2) const
{
	return *this - LongModInt(LongInt(number2), field);
}

LongModInt LongModInt::operator+(const std::string& number2) const
{
	return *this + LongModInt(LongInt(number2), field);
}

bool LongModInt::operator==(const std::string& number2) const
{
	return *this == LongModInt(LongInt(number2), field);
}

bool LongModInt::operator!=(const std::string& number2) const
{
	return *this != LongModInt(LongInt(number2), field);
}

ModField* LongModInt::getField() const
{
	return field;
}