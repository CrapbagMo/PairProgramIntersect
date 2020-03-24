#pragma once

#define EPS (0.0000000000001)

#include <math.h>

class Point {
public:
	Point();
	Point(double x, double y);
	virtual	double getX()const;
	virtual	double getY()const;
	bool operator ==(const Point& point)const;
	bool operator <(const Point& point)const;

private:
	double x, y;
};

