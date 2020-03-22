#pragma once

#include "Figure.h"
#include "Circle.h"
#include "Point.h"

class Line :public Figure {
public:
	Line(int, int, int, int, LineType);
	Line(double, double, double);
	std::set <Point> intersect(Figure*);
	bool contain(Point);
	double calX(double);
	double calY(double);
	double getA();
	double getB();
	double getC();
	double getR();
	double getS();
private:
	double A, B, C, R, S;
};

