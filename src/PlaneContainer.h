#pragma once

#include "Figure.h"
#include "Point.h"
#include <algorithm>
#include <iostream>

class PlaneContainer
{
public:
	PlaneContainer();
	virtual	void insert(Figure* figure);
	virtual	int countIntersectionPoints();
	virtual std::set<Point>* getIntersectPoints();
	virtual	~PlaneContainer() {
		std::cout << "PlaneContainer destroy" << std::endl;
		for (Figure* var : *figures) {
			delete var;
		}
		delete intersetionPoints;
		delete figures;
	}
private:
	std::set<Point>* intersetionPoints;
	std::vector<Figure*>* figures;
};

