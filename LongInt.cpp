//
// Created by yurik on 29.11.2019.
//
#include "pch.h"
#include <iostream>
#include "LongInt.h"



const int BASE = 10;



LongInt::LongInt(const std::string& str)
{
	int i = 0;

	if (str[0] == '-') {
		negative = true;
		i = 1;
	}
	else negative = false;

	x.resize(str.length());
	for (; i < str.length(); i++) {
		x[i] = str[i] - '0';
	}

	removeZeros();
}


LongInt::LongInt(long long number)
		: LongInt(std::to_string(number))
{}

LongInt::LongInt(const std::vector<int>& number)
		: x(number), negative(false)
{}

LongInt::LongInt()
{
	negative = false;
}


void LongInt::revert(int size)
{
	std::vector<int> updated_result;
	int i = size - 1;
	while (i >= 0) {
		updated_result.push_back(x[i]);
		i--;
	}
	x = updated_result;
}

void LongInt::removeZeros()
{
	while (this->x.size() > 1 && this->x.front() == 0) this->x.erase(x.begin());
}

void LongInt::shiftRight()
{
	if (x.size() == 0) {
		x.push_back(0);
		return;
	}
	x.push_back(x[x.size() - 1]);
	for (int i = x.size() - 2; i > 0; --i) x[i] = x[i - 1];
	x[0] = 0;
}

LongInt LongInt::gcdExtended(const LongInt& a, const LongInt& b, LongInt& x, LongInt& y)
{
	// Base Case
	if (a == LongInt(0))
	{
		x = LongInt(0);
		y = LongInt(1);
		return b;
	}
	LongInt x1, y1;
	LongInt gcd = gcdExtended(b % a, a, x1, y1);
	x = y1 - (b / a) * x1;
	y = x1;
	return gcd;
}

std::ostream& operator<<(std::ostream& stream, const LongInt& number)
{
	if(number.x.empty())
	{
		stream << '0';
		return stream;
	}

	if (number.negative) stream << '-';
	for (int i = 0; i < number.x.size(); i++) {
		stream << number.x[i];
	}

	return stream;
}

bool operator <(const LongInt& number1, const LongInt& number2)
{
	if (number1.negative && !number2.negative)
		return true;

	if (!number1.negative && number2.negative)
		return false;

	if (number1.negative && number2.negative) return !(-number1 < -number2) && number1 != number2;

	if (number1.x.size() != number2.x.size()) return number1.x.size() < number2.x.size();

	//they have the same array sizes
	for (int j = 0; j < number1.x.size(); j++)
		if (number1.x[j] != number2.x[j]) return number1.x[j] < number2.x[j];

	return false;
}

bool operator <=(const LongInt& number1, const LongInt& number2)
{
	return !(number1 > number2);
}

bool operator >=(const LongInt& number1, const LongInt& number2)
{
	return !(number1 < number2);
}

bool operator ==(const LongInt& number1, const LongInt& number2)
{
	if (number1.negative != number2.negative) return false;
	if (number1.x.size() != number2.x.size()) return false;
	for (int i = 0; i < number1.x.size(); i++)
		if (number1.x[i] != number2.x[i]) return false;
	return true;
}

bool operator !=(const LongInt& number1, const LongInt& number2)
{
	if (number1.negative != number2.negative) return true;
	if (number1.x.size() != number2.x.size()) return true;
	for (int i = 0; i < number1.x.size(); i++)
		if (number1.x[i] != number2.x[i]) return true;
	return false;
}

bool operator >(const LongInt& number1, const LongInt& number2)
{
	if (number1.negative && !number2.negative)
		return false;

	if (!number1.negative && number2.negative)
		return true;

	if (number1.negative && number2.negative) return !(-number1 > -number2) && number1 != number2;

	if (number1.x.size() != number2.x.size()) return number1.x.size() > number2.x.size();

	//they have the same array sizes
	for (int j = 0; j < number1.x.size(); j++)
		if (number1.x[j] != number2.x[j]) return number1.x[j] > number2.x[j];

	return false;
//	if (number1.x.size() < number2.x.size())
//		return false;
//	if (number1.x.size() > number2.x.size())
//		return true;
//	for (int i = 0; i < number2.x.size(); i++)
//		if (number1.x[i] < number2.x[i])
//			return false;
//		else if (number1.x[i] > number2.x[i])
//			return true;
//	return false;
}


LongInt LongInt::operator*(const LongInt& number2) const
{
	LongInt result;
	int n = this->x.size();
	int t = number2.x.size();
	int size = n + t + 1;
	result.x.resize(size);
	int c = 0;
	if (this->negative && !number2.negative) result.negative = true;
	if (number2.negative && !this->negative) result.negative = true;

	int shift = 0;
	int shift_iterator = 0;

	for (int i = this->x.size() - 1; i >= 0; i--) {
		c = 0;
		shift_iterator = 0;
		for (int j = number2.x.size() - 1; j >= 0; j--) {
			int current = result.x[shift + shift_iterator] + number2.x[j] * this->x[i] + c;
			result.x[shift + shift_iterator] = current % BASE;
			c = current / BASE;
			shift_iterator++;
		}
		result.x[shift + shift_iterator] = c;
		shift++;
	}
	result.revert(size);
	result.removeZeros();
	return result;
}

LongInt LongInt::operator+(LongInt number2) const
{
	LongInt result;
	int n1 = this->x.size();
	int n2 = number2.x.size();


	if (number2.negative && !this->negative) return *this - (-number2);
	if (this->negative && !number2.negative) return number2 - -(*this);
	if (this->negative && number2.negative) result.negative = true;

	LongInt number1 = *this;

	int size = (n1 > n2 ? n1 : n2) + 1;
	result.x.resize(size);

	number1.revert(n1);
	number2.revert(n2);

	int c = 0;
	int i;
	for (i = 0; i < size - 1; i++) {
		c = (i < number1.x.size() ? number1.x[i] : 0) + (i < number2.x.size() ? number2.x[i] : 0) + c;
		result.x[i] = c%BASE;
		c = c/BASE;
	}
	result.x[i] = c;
	result.revert(size);
	result.removeZeros();

	return result;
}

LongInt LongInt::operator-(LongInt number2) const
{
	if (!this->negative && number2.negative) return (*this + (-number2));
	if (this->negative && !number2.negative) return -((-*this) + number2);
	if (this->negative && number2.negative) return (-number2) - (-*this);

	LongInt number1 = *this;
	LongInt result;
	if (number2 > number1) {
		result.negative = true;
		number1 = number2;
		number2 = *this;
	}
	int n1 = number1.x.size();
	int n2 = number2.x.size();

	int size = (n1 > n2 ? n1 : n2) + 1;
	result.x.resize(size);

	if (number1.x.size() > 1) number1.revert(n1);
	if (number2.x.size() > 1) number2.revert(n2);

	int add = 0;
	int c = 0;
	for (int i = 0; i < size - 1; i++) {
		int number = (i < n2 ? number2.x[i] : 0);
		if (number1.x[i] + c >= number) {
			result.x[i] = number1.x[i] + c - number;
			c = 0;
		}
		else {
			if (i >= n2) add = 0; else add = number2.x[i];
			result.x[i] = BASE + number1.x[i] + c - add;
			c = -1;
		}
	}
	number2.removeZeros();
	result.revert(size);
	result.removeZeros();
	return result;
}

LongInt LongInt::operator%(const LongInt& number2) const
{
	//cannot divide by zero
	if (number2.x.size() == 1 && number2.x[0] == 0)
		throw std::invalid_argument("Modulo can't be 0.");

	int n = this->x.size();
	int t = number2.x.size();
	LongInt result, remainder;
	int x = 0;
	int left = 0;
	int right = BASE;
	result.x.resize(n);

	for (int i = 0; i < this->x.size(); i++) {
		if (remainder.x.size() == 1 && remainder.x[0] == 0) remainder.x[0] = this->x[i];
		else remainder.x.push_back(this->x[i]);
		x = 0;
		left = 0;
		right = BASE;
		while (left <= right) {
			int m = (left + right) / 2;
			LongInt mod = LongInt(m);
			LongInt t = number2 * mod;
			if (t <= remainder) {
				x = m;
				left = m + 1;
			}
			else right = m - 1;
		}
		result.x[i] = x;
		remainder = (remainder - (number2 * LongInt(x)));
	}
	result.negative = this->negative != number2.negative;
	result.removeZeros();
	return remainder;
}

LongInt LongInt::operator/(const LongInt& number2) const
{
	//cannot divide by zero
	if (number2.x.size() == 1 && number2.x[0] == 0)
		throw std::invalid_argument("Can't divide by 0");

	int n = this->x.size();
	//int t = number2.x.size();
	LongInt result, remainder;
	int x = 0;
	int left = 0;
	int right = BASE;
	result.x.resize(n);

	for (int i = 0; i < this->x.size(); i++) {
		if (remainder.x.size() == 1 && remainder.x[0] == 0) remainder.x[0] = this->x[i]; 
		else remainder.x.push_back(this->x[i]);
		x = 0;
		left = 0;
		right = BASE;
		while (left <= right) {
			int m = (left + right) / 2;
			LongInt mod = LongInt(m);
			LongInt t = number2 * mod;
			if (t <= remainder) {
				x = m;
				left = m + 1;
			}
			else right = m - 1;
		}
		result.x[i] = x;
		remainder = remainder - number2 * LongInt(x);
	}
	result.negative = this->negative != number2.negative;
	result.removeZeros();
	return result;
}

LongInt LongInt::operator-() const
{
	LongInt number2 = *this;
	number2.negative = !this->negative;
	return number2;
}

bool LongInt::isNegative() const
{
	return negative;
}

int LongInt::getSize() const
{
	return x.size();
}