#pragma once
#include<cmath>
using namespace std;
struct Vector {               //œÚ¡ø
	double i;
	double j;
	double k;
	Vector() { i = 0; j = 0; k = 0; }
	Vector(double x, double y, double z) {
		i = x;
		j = y;
		k = z;
	}
};

double mole(Vector v) {
	return sqrt(v.i*v.i+v.j*v.j+v.k*v.k);
}

Vector vectorplus(Vector v1, Vector v2) {
	Vector tem;
	tem.i = v1.i + v2.i;
	tem.j = v1.j + v2.j;
	tem.k = v1.k + v2.k;
	return tem;
}
Vector minus(Vector v1, Vector v2) {
	Vector tem;
	tem.i = v1.i - v2.i;
	tem.j = v1.j - v2.j;
	tem.k = v1.k - v2.k;
	return tem;
}
Vector numbermulptiply(double a, Vector v) {
	Vector tem;
	tem.i = a*v.i;
	tem.j = a*v.j;
	tem.k = a*v.k;
	return tem;
};

double vectormultiply(Vector v1, Vector v2) {
	return v1.i*v2.i + v1.j*v2.j + v1.k*v2.k;
};

double cos(Vector v1, Vector v2) {
	if (mole(v1) != 0 && mole(v2) != 0)
		return vectormultiply(v1, v2) / (mole(v1)*mole(v2));
};
