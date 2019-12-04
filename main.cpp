#include "pch.h"
#include <iostream>
#include <memory>

#include "ModArithmetic.h"
#include "EllipticCurve.h"

using std::cout;
using std::string;
using std::cin;

int order(const EllipticCurve& curve, const Point& p) {
	int k = 1;
	// текущая точка = сумма k точек P (или k * P)
	// (изначально = P, т.к. k = 1)
	Point current = p;
	// пока текущая точка не ушла в бесконечность
	while (!current.isInfinite()) {
		// добавляем к ней точку P
		current = curve.add(current, p);
		k++;
	}
	// точка ушла в бесконечность,
	// возвращаем сколько раз мы её добавили
	return k;
}

int main() {

	cout << "elliptic curve E(Fp): ";
	cout << "y^2 = x^3 + Ax + B, p prime" << endl;

	string p;
	cout << "enter p: ";
	cin >> p;

	string a;
	cout << "enter A: ";
	cin >> a;

	cout << endl;
	cout << "point P(x, y)" << endl;

	string x;
	cout << "enter x: ";
	cin >> x;

	string y;
	cout << "enter y: ";
	cin >> y;

	// переводим строки в объекты чисел
	unique_ptr<ModField> field(new ModField(p));
	LongModInt ma(a, field.get());
	LongModInt mx(x, field.get());
	LongModInt my(y, field.get());

	// находим такое B, при котором точка будет лежать на кривой
	// B = y^2 - x^3 - Ax
	LongModInt mb = my * my - mx * mx * mx - ma * mx;

	EllipticCurve curve(ma.num, mb.num, field.get());
	Point P(mx, my);

	// выводим B
	cout << endl;
	cout << "B = " << mb << endl;

	// выводим порядок точки P на кривой curve
	cout << endl;
	cout << "ord(P) = " << order(curve, P) << endl;

	return 0;
}
