#define CORE_API

#include "core.h"
using namespace std;
static PlaneContainer* pc = nullptr;

CORE_API int add_Figure(std::string buf)
{
	stringstream stream;
	stream << buf;

	if (pc == nullptr) {
		pc = new PlaneContainer();
	}

	int x1, y1, x2, y2, a, b, r;
	char type;
	std::regex segmentREGEX("S\\s+-?\\d+\\s+-?\\d+\\s+-?\\d+\\s+-?\\d+\\s*\\n?");
	std::regex lineREGEX("L\\s+-?\\d+\\s+-?\\d+\\s+-?\\d+\\s+-?\\d+\\s*\\n?");
	std::regex rayREGEX("R\\s+-?\\d+\\s+-?\\d+\\s+-?\\d+\\s+-?\\d+\\s*\\n?");
	std::regex circleREGEX("C\\s+-?\\d+\\s+-?\\d+\\s+-?\\d+\\s*\\n?");
	if (regex_match(buf, segmentREGEX)) {
		stringstream stream;
		stream << buf;
		stream >> type;
		stream >> x1 >> y1 >> x2 >> y2;
		try {
			pc->insert(new Line(x1, y1, x2, y2, LS));
		}
		catch (int exceptionType) {
			return exceptionType;
		}
	}
	else if (regex_match(buf, rayREGEX)) {
		stringstream stream;
		stream << buf;
		stream >> type;
		stream >> x1 >> y1 >> x2 >> y2;
		try {
			pc->insert(new Line(x1, y1, x2, y2, RL));
		}
		catch (int exceptionType) {
			return exceptionType;
		}
	}
	else if (regex_match(buf, lineREGEX)) {
		stringstream stream;
		stream << buf;
		stream >> type;
		stream >> x1 >> y1 >> x2 >> y2;
		try {
			pc->insert(new Line(x1, y1, x2, y2, SL));
		}
		catch (int exceptionType) {
			return exceptionType;
		}
	}
	else if (regex_match(buf, circleREGEX)) {
		stringstream stream;
		stream << buf;
		stream >> type;
		stream >> a >> b >> r;
		try {
			pc->insert(new Circle(a, b, r));
		}
		catch (int exceptionType) {
			return exceptionType;
		}
	}
	else {
		return -1;
	}
	return 0;
}

/*CORE_API PlaneContainer* create_PlaneContainer()
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
}*/



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

