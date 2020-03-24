#pragma once

#ifdef CORE_API
#define CORE_API _declspec(dllexport)
#else
#define CORE_API _declspec(dllimport)
#endif 

#include "PlaneContainer.h"
#include "Circle.h"
#include "Line.h"
#include <string>

extern "C" CORE_API PlaneContainer * create_PlaneContainer();
extern "C" CORE_API Circle * create_Circle(int, int, int);
extern "C" CORE_API Line * create_Line(int, int, int, int, LineType);


extern "C" CORE_API int add_Figure(char*);
extern "C" CORE_API void initial_PlaneContainer();
extern "C" CORE_API void dispose_PlaneContainer();
extern "C" CORE_API double* get_IntersectionPoints();
extern "C" CORE_API int get_NumOfIntersectionPoints();