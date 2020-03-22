#include "Line.h"
#include <string>
#include <math.h>
Line::Line(int x1, int y1, int x2, int y2, enum LineType type) {
	if (type == SL) {
		R = -INF;
		S = INF;
	}
	if (x1 == x2) {
		this->A = 1;
		this->B = 0;
		this->C = -x1;
		if (type == RL) {
			R = (y1 < y2) ? y1 : (-INF);
			S = (y1 < y2) ? (INF) : y1;
		}
		else if (type == LS) {
			R = (y1 < y2) ? y1 : y2;
			S = (y1 < y2) ? y2 : y1;
		}

	}
	else {
		this->A = double(y1) - double(y2);
		this->B = double(x2) - double(x1);
		this->C = double(x1) * double(y2) - double(x2) * double(y1);

		if (type == RL) {
			R = (x1 < x2) ? x1 : (-INF);
			S = (x1 < x2) ? (INF) : x1;
		}
		else if (type == LS) {
			R = (x1 < x2) ? x1 : x2;
			S = (x1 < x2) ? x2 : x1;
		}
	}
}

Line::Line(double A, double B, double C) {
	this->A = A;
	this->B = B;
	this->C = C;
	R = -INF;
	S = INF;
}

std::set<Point> Line::intersect(Figure* figure) {
	double x, y;
	std::set<Point> points;
	if (typeid(*figure) == typeid(Line)) {
		Line* line = (Line*)figure;
		double A1, B1, C1, A2, B2, C2;
		A1 = this->A; B1 = this->B; C1 = this->C;
		A2 = line->getA(); B2 = line->getB(); C2 = line->getC();
		//((B1*C2-B2*C1)/(A1*B2-A2*B1)£¬(A2*C1-A1*C2)/(A1*B2-A2*B1))
		//((b1*c2-b2*c1)/(a1*b2-a2*b1)£¬(a2*c1-a1*c2)/(a1*b2-a2*b1))
		if (fabs(A1 * B2 - A2 * B1) >= EPS) {
			//A1 * B2 != A2 * B1
			x = (B1 * C2 - B2 * C1) / (A1 * B2 - A2 * B1);
			y = (A2 * C1 - A1 * C2) / (A1 * B2 - A2 * B1);
			Point tP(x, y);
			if (this->contain(tP) && line->contain(tP)) {
				points.insert(tP);
			}
		}
		else if (fabs(A1 * C2 - A2 * C1) <= EPS) {
			//overlap each other. 3 probable conditions:
			double R1, S1;
			R1 = line->getR();
			S1 = line->getS();
			if (((R1 + EPS < R) && (R + EPS < S1)) ||
				((R1 + EPS < S) && (S + EPS < S1))) {
				//R1<R<S1 or R1<S<S1 (parallel to y should be thought)
				//1st. endless intersection points. we should throw an Exception.
				;
			}
			else if (fabs(R1 - S) <= EPS || fabs(S1 - R) <= EPS) {
				//R1 == S or R == S1
				//2nd. only one intersection point
				double t1, t2;
				t1 = (fabs(R - S1) <= EPS) ? R : S;
				t1 = (t1 > 0.0) ? floor(t1 + 0.5) : ceil(t1 - 0.5);

				if (fabs(B) <= EPS)
				{
					t2 = calX(t1);
					t2 = (t2 > 0.0) ? floor(t2 + 0.5) : ceil(t2 - 0.5);
					points.insert(Point(t2, t1));
				}
				else {
					t2 = calY(t1);
					t2 = (t2 > 0.0) ? floor(t2 + 0.5) : ceil(t2 - 0.5);
					points.insert(Point(t1, t2));
				}

			}
			//3rd. no intersection points
		}
	}
	else if (typeid(*figure) == typeid(Circle)) {
		Circle* circle = (Circle*)figure;
		double tA, tB, tC, a, b, r, k, m, Delta;
		a = circle->getX();
		b = circle->getY();
		r = circle->getR();
		if (fabs(B) > EPS) {
			//B != 0
			k = -A / B;
			m = -C / B;

			//tA=1+k^2
			tA = 1 + k * k;
			//tB=2(km-bk-a)
			tB = 2 * (k * m - b * k - a);
			//tC=a^2+(b-m)^2-r^2
			tC = a * a + (b - m) * (b - m) - r * r;

			Delta = tB * tB - 4 * tA * tC;
			if (Delta >= EPS) {
				//Delta > 0
				x = (-tB + sqrt(Delta)) / (2 * tA);
				y = k * x + m;
				Point tP(x, y);
				if (this->contain(tP)) {
					points.insert(tP);
				}

				x = (-tB - sqrt(Delta)) / (2 * tA);
				y = k * x + m;
				Point tP0(x, y);
				if (this->contain(tP0)) {
					points.insert(tP0);
				}

			}
			else if (Delta >= -EPS) {
				//Delta == 0
				Delta = fabs(Delta);
				x = -tB / (2 * tA);
				y = k * x + m;
				Point tP(x, y);
				if (this->contain(tP)) {
					points.insert(tP);
				}
			}
		}
		else {
			x = m = -C / A;
			y = b + sqrt(r * r - (m - a) * (m - a));
			Point tP(x, y);
			if (this->contain(tP)) {
				points.insert(tP);
			}

			y = b - sqrt(r * r - (m - a) * (m - a));
			Point tP0(x, y);
			if (this->contain(tP0)) {
				points.insert(tP0);
			}
		}
	}
	return points;
}

bool Line::contain(Point point) {
	double x = point.getX();
	double y = point.getY();

	if (fabs(B) <= EPS) {
		//B == 0
		//parallel to y
		return (R <= y + EPS && y <= S + EPS);
	}
	else {
		return (R <= x + EPS && x <= S + EPS);
	}
	return false;
}

double Line::calX(double y)
{
	if (fabs(A) >= EPS) {
		// A != 0
		return (-C / A - B * y / A);
	}
	return INF;
}

double Line::calY(double x)
{
	if (fabs(B) >= EPS) {
		// B != 0
		return (-C / B - A * x / B);
	}
	return INF;
}

double Line::getA() {
	return A;
}
double Line::getB() {
	return B;
}
double Line::getC() {
	return C;
}
double Line::getR() {
	return this->R;
}
double Line::getS() {
	return this->S;
}

