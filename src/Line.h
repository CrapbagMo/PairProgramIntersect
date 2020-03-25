#pragma once
#include "Figure.h"
#include "Circle.h"
#include "Line.h"
#include "Point.h"
class Line :public Figure {
public:
	Line(int x1, int y1, int x2, int y2, enum LineType type);
	Line(double A, double B, double C);
	set <Point> intersect(Figure* figure);
	bool contain(Point point);
	double getA();
	double getB();
	double getC();
	double getR();
	double getS();
private:
	double A, B, C, R, S;
};

