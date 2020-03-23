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
#include <sstream>


extern "C" CORE_API int add_Figure(std::string buf);
/*extern "C" CORE_API PlaneContainer * create_PlaneContainer();
extern "C" CORE_API Circle * create_Circle(int, int, int);
extern "C" CORE_API Line * create_Line(int, int, int, int, LineType);*/