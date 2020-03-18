// SEC_HW_IndividualProject.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//
#include <istream>
#include <fstream>
#include <iostream>
#include <string>
#include <stdlib.h>
#include <algorithm>
#include <iterator>
#include "Figure.h"
#include "Circle.h"
#include "Line.h"
#include "Point.h"
#include "PlaneContainer.h"
using namespace std;

int main(int argc, char* argv[]) {
	string inputPath = "";
	string outputPath = "";
	ifstream in;
	ofstream out;
	string strBuf;
	int n;
	//arguments process
	for (int i = 1; i < argc; i++) {
		if (string(argv[i]) == "-i") {
			inputPath = string(argv[++i]);
		} else if (string(argv[i]) == "-o") {
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
	//input and output process
	in.open(inputPath);
	out.open(outputPath);

	in >> n;
	PlaneContainer pc;

	for (int i = 0; i < n; i++) {
		int x1, x2, y1, y2, r;

		in >> strBuf;
		if (strBuf == "L") {
			in >> x1 >> y1 >> x2 >> y2;
			pc.insert(new Line(x1, y1, x2, y2, SL));
		} else if (strBuf == "C") {
			in >> x1 >> y1 >> r;
			pc.insert(new Circle(x1, y1, r));
		} else if (strBuf == "R") {
			in >> x1 >> y1 >> x2 >> y2;
			pc.insert(new Line(x1, y1, x2, y2, RL));
		} else if (strBuf == "S") {
			in >> x1 >> y1 >> x2 >> y2;
			pc.insert(new Line(x1, y1, x2, y2, LS));
		}
	}

	out << pc.countIntersectionPoints() << endl;
	cout << "total intersection points :" << pc.countIntersectionPoints() << " as following:" << endl;
	for (auto p = pc.getIntersectPoints()->begin(); p != pc.getIntersectPoints()->end(); p++) {
		cout << (p->getX()) << "," << (p->getY()) << endl;
	}
	return 0;

}
