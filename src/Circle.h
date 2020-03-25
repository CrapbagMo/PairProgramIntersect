#pragma once
#include "Figure.h"
#include "Circle.h"
#include "Line.h"
#include "Point.h"
class Circle :public Figure {
public:
	Circle(int x, int y, int r);
	set<Point> intersect(Figure* figure);
	double getX();
	double getY();
	double getR();
private:
	double x, y, r;
};

