#pragma once
#include "Figure.h"
#include "Point.h"
#include <algorithm>
#include <iostream>

class Figure;

class PlaneContainer {
public:
	PlaneContainer();
	void insert(Figure* figure);
	int countIntersectionPoints();
	set<Point>* getIntersectPoints();
	~PlaneContainer() {
		cout << "PlaneContainer destroy" << endl;
		delete intersetionPoints;
		delete figures;
	}
private:
	set<Point>* intersetionPoints;
	vector<Figure*>* figures;
};

