#pragma once
#include <math.h>
#define EPS (0.00000001)

class Point {
public:
	Point();
	Point(double x, double y);
	double getX()const;
	double getY()const;
	bool operator ==(const Point& point)const;
	bool operator <(const Point& point)const;

private:
	double x, y;
};

