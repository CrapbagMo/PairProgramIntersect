// main.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
#include <windows.h>
#include <iostream>
#include <istream>
#include <fstream>
#include "core.h"

using namespace std;

int main(int argc, char* argv[]) {
	string inputPath = "";
	string outputPath = "";
	ifstream in;
	ofstream out;
	string strBuf;
	char buf[100];
	int n;
	//arguments process
	for (int i = 1; i < argc; i++) {
		if (string(argv[i]) == "-i") {
			inputPath = string(argv[++i]);
		}
		else if (string(argv[i]) == "-o") {
			outputPath = string(argv[++i]);
		}
	}
	if (inputPath.size() == 0) {
		cout << "-i is in need" << endl;
		return -1;
	}
	if (outputPath.size() == 0) {
		cout << "-o is in need" << endl;
		return -1;
	}

	//load core.dll
	HINSTANCE coreHdl = LoadLibrary("core.dll");
	if (!coreHdl) {
		printf("no core.dll\n");
		return 1;
	}

	/*typedef PlaneContainer* (*A)();
	typedef Circle* (*B)(int, int, int);
	typedef Line* (*C)(int, int, int, int, enum LineType);*/
	typedef int (*A)(char*);
	typedef  void (*B)();
	typedef  void (*C)();
	typedef  double* (*D)();
	typedef  int (*E)();

	/*A create_PC = (A)GetProcAddress(coreHdl, "create_PlaneContainer");
	B create_Circle = (B)GetProcAddress(coreHdl, "create_Circle");
	C create_Line = (C)GetProcAddress(coreHdl, "create_Line");*/

	A add_Figure = (A)GetProcAddress(coreHdl, "add_Figure");
	B initial_PlaneContainer = (B)GetProcAddress(coreHdl, "initial_PlaneContainer");
	C dispose_PlaneContainer = (C)GetProcAddress(coreHdl, "dispose_PlaneContainer");
	D get_IntersectionPoints = (D)GetProcAddress(coreHdl, "get_IntersectionPoints");
	E get_NumOfIntersectionPoints = (E)GetProcAddress(coreHdl, "get_NumOfIntersectionPoints");

	initial_PlaneContainer();
	//input and output process
	in.open(inputPath);
	out.open(outputPath);

	in >> n;
	in.getline(buf, 100);
	for (int i = 0; i < n; i++) {
		memset(buf, 0, 90);
		in.getline(buf, 100);
		int ret = add_Figure(buf);
		switch (ret)
		{
		case -1:
			cout << "Wrong Format at line " << i + 1 << endl;
			break;
		case 1:
			cout << "Parameter out of limitation at line " << i + 1 << endl;
			break;
		case 2:
			cout << "The two points to locate a line coincide at line " << i + 1 << endl;
			break;
		case 3:
			cout << "The radius is less than or equal to zero at line " << i + 1 << endl;
			break;
		case 4:
			cout << "Infinite intersect points " << endl;
			break;
		default:
			break;
		}
	}

	out << get_NumOfIntersectionPoints() << endl;
	cout << "total intersection points: " << get_NumOfIntersectionPoints() << endl;


	//for (auto p = pc->getIntersectPoints()->begin(); p != pc->getIntersectPoints()->end(); p++) {
		//cout << (p->getX()) << "," << (p->getY()) << endl;
	//}

	dispose_PlaneContainer();
	in.close();
	out.close();

	return 0;
}