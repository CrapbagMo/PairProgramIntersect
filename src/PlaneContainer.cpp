#include "PlaneContainer.h"
#include <algorithm>
#include <iterator>
PlaneContainer::PlaneContainer() {
	figures = new vector<Figure*>();
	intersetionPoints = new set<Point>();
}

void PlaneContainer::insert(Figure* figure) {
	for (auto fig = figures->begin(); fig != figures->end(); fig++) {
		set<Point> tPoints = (*fig)->intersect(figure);
		set_union(tPoints.begin(), tPoints.end(), intersetionPoints->begin(), intersetionPoints->end(), inserter(*intersetionPoints, (*intersetionPoints).begin()));
	}
	figures->push_back(figure);
}

int PlaneContainer::countIntersectionPoints() {
	return intersetionPoints->size();
}

set<Point>* PlaneContainer::getIntersectPoints() {
	return intersetionPoints;
}
