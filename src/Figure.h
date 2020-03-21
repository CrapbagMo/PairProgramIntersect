#pragma once
#define INF (1000000000.0)

#include <typeinfo>
#include <set>
#include <vector>

#include "Point.h"

using namespace std;

class Figure {
public:
	virtual set<Point> intersect(Figure* figure) = 0;
};
//RL:RayLine,LS:LineSegment,SL:StraightLine
enum  LineType { RL, LS, SL };