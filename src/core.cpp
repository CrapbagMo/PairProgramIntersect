#define CORE_API

#include "core.h"

CORE_API PlaneContainer* create_PlaneContainer()
{
	return new PlaneContainer();
}

CORE_API Circle* create_Circle(int a, int b, int r)
{
	return new Circle(a, b, r);
}

CORE_API Line* create_Line(int x1, int y1, int x2, int y2, enum LineType type)
{
	return new Line(x1, y1, x2, y2, type);
}
