#pragma once
#include "Figure.h"
#include "Point.h"
#include <algorithm>
#include <iostream>

class Figure;

class PlaneContainer {
public:
	PlaneContainer();
	virtual	void insert(Figure* figure);
	virtual	int countIntersectionPoints();
	virtual	set<Point>* getIntersectPoints();
	~PlaneContainer() {
		cout << "PlaneContainer destroy" << endl;
		delete intersetionPoints;
		delete figures;
	}
private:
	set<Point>* intersetionPoints;
	vector<Figure*>* figures;
};

