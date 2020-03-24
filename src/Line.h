#pragma once

#include "Figure.h"
#include "Circle.h"
#include "Point.h"
#include <regex>

class Line :public Figure {
public:
	Line(int x1, int y1, int x2, int y2, LineType type);
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

