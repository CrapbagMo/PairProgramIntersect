#include "Circle.h"

Circle::Circle(int x, int y, int r) {

	if (r <= 0) {
		throw 3;
	}
	else if (abs(x) > 100000 || abs(y) > 100000 || r > 100000) {
		throw 1;
	}

	this->x = x;
	this->y = y;
	this->r = r;
}

std::set<Point> Circle::intersect(Figure* figure) {

	std::set<Point> points;
	if (typeid(*figure) == typeid(Line)) {
		Line* line = (Line*)figure;
		points = line->intersect(this);
	}
	else if (typeid(*figure) == typeid(Circle)) {
		Circle* circle = (Circle*)figure;
		double x1, x2, y1, y2, r1, r2;
		double D1, D2, E1, E2, F1, F2, dis;
		x1 = this->x;
		y1 = this->y;
		r1 = this->r;
		x2 = circle->getX();
		y2 = circle->getY();
		r2 = circle->getR();

		if (x1 == x2 && y1 == y2 && r1 == r2) {
			throw 4;
		}

		dis = (x1 - x2) * (x1 - x2) + (y1 - y2) * (y1 - y2);
		dis = sqrt(dis);
		D1 = -2 * x1;
		E1 = -2 * y1;
		F1 = x1 * x1 + y1 * y1 - r1 * r1;
		D2 = -2 * x2;
		E2 = -2 * y2;
		F2 = x2 * x2 + y2 * y2 - r2 * r2;

		if (dis - EPS <= r1 + r2 && dis + EPS >= fabs(r1 - r2)) {
			points = Line(D1 - D2, E1 - E2, F1 - F2).intersect(this);
		}
	}
	return points;
}

double Circle::getX() {
	return x;
}

double Circle::getY() {
	return y;
}

double Circle::getR() {
	return r;
}
