#include "Point.h"

Point::Point() {
	this->x = this->y = 0;
}

Point::Point(double x, double y) {
	this->x = x;
	this->y = y;
}

bool Point::operator==(const Point& point) const {
	return fabs(this->x - point.x) <= EPS && fabs(this->y - point.y) <= EPS;
	//this->x == point.x && y...
}

bool Point::operator<(const Point& point) const {
	if ((point.x - this->x) >= EPS) {
		return true;
	}
	if ((this->x - point.x) >= EPS) {
		return false;
	}
	if ((point.y - this->y) >= EPS) {
		return true;
	}
	return false;
}

double Point::getX() const {
	return x;
}

double Point::getY() const {
	return y;
}
