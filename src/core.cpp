#define CORE_API

#include "core.h"

static PlaneContainer* pc = nullptr;

CORE_API PlaneContainer* create_PlaneContainer()
{
	return new PlaneContainer();
}

CORE_API Circle* create_Circle(int a, int b, int r)
{
	return new Circle(a, b, r);
}

CORE_API Line* create_Line(int x1, int y1, int x2, int y2, LineType type)
{
	return new Line(x1, y1, x2, y2, type);
}

CORE_API int add_Figure(char* str)
{
	std::string buf(str);
	return buf == "2";
}

CORE_API void initial_PlaneContainer()
{
	if (pc == nullptr) {
		pc = new PlaneContainer();
	}
}

CORE_API void dispose_PlaneContainer()
{
	if (pc != nullptr) {
		delete pc;
		pc = nullptr;
	}
}

CORE_API double* get_IntersectionPoints()
{
	int n = pc->countIntersectionPoints();
	int a, b, i;
	std::set<Point>* p = pc->getIntersectPoints();
	double* arr = new double[2 * n];
	auto start = p->begin();
	auto end = p->end();

	i = 0;
	for (auto ptr = start; ptr != end; ptr++) {
		a = 2 * i;
		b = a + 1;
		arr[a] = ptr->getX();
		arr[b] = ptr->getY();
	}
	return arr;
}

CORE_API int get_NumOfIntersectionPoints()
{
	return pc->countIntersectionPoints();
}

