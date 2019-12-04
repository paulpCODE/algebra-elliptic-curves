#include "pch.h"
#include <cmath>
#include "EllipticCurve.h"

using namespace std;

Point::Point(const LongModInt& x, const LongModInt& y)
	: x(x), y(y)
{}

Point Point::makeInfinite()
{
	Point p;
	p.infinite = true;
	return p;
}

bool Point::isInfinite() const
{
	return this->infinite;
}

bool Point::operator==(const Point& p)
{
	if (p.isInfinite())
		return this->isInfinite();

	else if (this->isInfinite())
		return false;

	return this->x == p.x && this->y == p.y;
}

ostream& operator<<(ostream& os, const Point& p)
{
	if (p.isInfinite())
		os << "(inf)";
	else
		os << '(' << p.x << ", " << p.y << ")";
	return os;
}

EllipticCurve::EllipticCurve(const LongInt& a, const LongInt& b, ModField* field)
	: field(field), a(a, field), b(b, field)
{
	if ("4" * this->a * this->a * this->a + "27" * this->b * this->b == "0")
		throw std::invalid_argument("Discriminant must be not equal to 0");
}

EllipticCurve::EllipticCurve(const std::string& a, const std::string& b, ModField* field)
	: EllipticCurve(LongInt(a), LongInt(b), field)
{}

Point EllipticCurve::add(const Point& p1, const Point& p2) const
{
	if (!isVaild(p1))
	{
		std::stringstream ss;
		ss << "Point " << p1 << " is not on the elliptic curve.";
		throw std::invalid_argument(ss.str());
	}
	if (!isVaild(p2))
	{
		std::stringstream ss;
		ss << "Point " << p2 << " is not on the elliptic curve.";
		throw std::invalid_argument(ss.str());
	}
	if (p1.isInfinite())
		return p2;
	if (p2.isInfinite())
		return p1;
	if (p1.x != p2.x)
	{
		LongModInt m = (p2.y - p1.y) / (p2.x - p1.x);
		LongModInt x3 = m * m - p1.x - p2.x;
		return Point(x3, m * (p1.x - x3) - p1.y);
	}
	else if (p1.y != p2.y)
	{
		return Point::makeInfinite();
	}
	else
	{
		//Points are equal
		if (p1.y != "0")
		{
			LongModInt m = ("3" * p1.x * p1.x + a) / ("2" * p1.y);
			LongModInt x3 = m * m - "2" * p1.x;
			return Point(x3, m * (p1.x - x3) - p1.y);
		}
		else
		{
			return Point::makeInfinite();
		}
	}
}

Point EllipticCurve::add(const std::pair<std::string, std::string>& p1,
	const std::pair<std::string, std::string>& p2) const
{
	Point point1(LongModInt(p1.first, field), LongModInt(p1.second, field));
	Point point2(LongModInt(p2.first, field), LongModInt(p2.second, field));
	return add(point1, point2);
}

Point EllipticCurve::invert(const Point& p) const
{
	if (p.isInfinite())
		return p;
	else
		return Point(p.x, -p.y);
}

bool EllipticCurve::isVaild(const Point& p) const
{
	return p.isInfinite() || p.y * p.y == p.x * p.x * p.x + a * p.x + b;
}

Point  EllipticCurve::integerTimesPoint(const Point& p, int k)
{
	if (!isVaild(p))
		throw invalid_argument("Point is not on the elliptic curve.");

	if (p.isInfinite())
		return p;

	int a = k;
	Point b;
	b.infinite = true;
	Point c = p;

	while (a != 0)
	{
		if (a % 2 == 0)
		{
			a = a / 2;
			b = b;
			c = add(c, c);
		}
		else
		{
			a = a - 1;
			b = add(b, c);
			c = c;
		}
	}
	return b;
}

Point  EllipticCurve::integerTimesPoint(const pair<string, string>& p, int k)
{
	Point point(LongModInt(p.first, field), LongModInt(p.second, field));
	return integerTimesPoint(point, k);
}