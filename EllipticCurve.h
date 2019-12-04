#pragma once
#include "pch.h"
#include <limits>
#include <iostream>
#include "ModArithmetic.h"

using namespace std;

struct Point
{
public:
	LongModInt x;
	LongModInt y;

	Point() = default;
	Point(const LongModInt& x, const LongModInt& y);
	static Point makeInfinite(); //"constructor" for infinite point
	bool infinite = false;
	bool isInfinite() const;
	bool operator==(const Point& p);
	friend ostream& operator<<(ostream& os, const Point& p);
};

//Weierstrass equation: y^2 = x^3 + Ax + B
class EllipticCurve
{
	ModField* field;

	LongModInt a;
	LongModInt b;

public:
	//to-do: check if modulo is prime?
	EllipticCurve(const LongInt& a, const LongInt& b, ModField* mod);
	EllipticCurve(const std::string& a, const std::string& b, ModField* mod);

	Point add(const Point& p1, const Point& p2) const;
	Point add(const std::pair<std::string, std::string>& p1, const std::pair<std::string, std::string>& p2) const;
	Point invert(const Point& p) const;
	bool isVaild(const Point& p) const;
	Point integerTimesPoint(const Point& p, int k);
	Point integerTimesPoint(const pair<string, string>& p, int k);
};