#include "pch.h"
#include "CppUnitTest.h"
#include "../intersect/PlaneContainer.h"
#include "../intersect/Circle.h"
#include "../intersect/Figure.h"
#include "../intersect/Line.h"
#include "../intersect/Point.h"
#include "../intersect/core.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTest2
{
	TEST_CLASS(UnitTest2)
	{
	public:
		
		TEST_METHOD(TestMethod1)
		{	// 格式错误
			
			int res = add_Figure("acsd");
			Assert::AreEqual(res, -1);
		}

		TEST_METHOD(TestMethod2)
		{	// 格式错误
			
			int res = add_Figure("C 5 3 -2 1");
			Assert::AreEqual(res, -1);
		}

		TEST_METHOD(TestMethod3)
		{	// 格式错误
			
			int res = add_Figure("L -5 3 -2 0 4");
			Assert::AreEqual(res, -1);
		}

		TEST_METHOD(TestMethod4)
		{	// 格式错误
			
			int res = add_Figure("R 5 -3 2");
			Assert::AreEqual(res, -1);
		}

		TEST_METHOD(TestMethod5)
		{	// 格式错误
			
			int res = add_Figure("c 5 -3 2");
			Assert::AreEqual(res, -1);
		}

		TEST_METHOD(TestMethod6)
		{	// 格式错误
			
			int res = add_Figure("S 5 -3 2 0-1\n");
			Assert::AreEqual(res, -1);
		}

		TEST_METHOD(TestMethod7)
		{	// 正常
			
			int res = add_Figure("R 5 -3 2 3");
			Assert::AreEqual(res, 0);
		}

		TEST_METHOD(TestMethod8)
		{	// 正常
			
			int res = add_Figure("C 5 -3 3\n");
			Assert::AreEqual(res, 0);
		}

		TEST_METHOD(TestMethod9)
		{	// 正常
			
			int res = add_Figure("R 5 -3 2 3\n");
			Assert::AreEqual(res, 0);
		}

		TEST_METHOD(TestMethod10)
		{	// 半径小于0
			
			int res = add_Figure("C 5 -3 -2 \n");
			Assert::AreEqual(res, 3);
		}

		TEST_METHOD(TestMethod11)
		{	// 半径等于0
			
			int res = add_Figure("C -5 -3 0\n");
			Assert::AreEqual(res, 3);
		}

		TEST_METHOD(TestMethod12)
		{	// 点超出坐标轴范围
			int res = add_Figure("L 963214 -3 2 3\n");
			Assert::AreEqual(res, 1);
		}

		TEST_METHOD(TestMethod13)
		{	// 点超出坐标轴范围
			int res = add_Figure("R 5 -3 526151 3\n");
			Assert::AreEqual(res, 1);
		}

		TEST_METHOD(TestMethod14)
		{	// 点超出坐标轴范围
			int res = add_Figure("C -3 526151 3\n");
			Assert::AreEqual(res, 1);
		}

		TEST_METHOD(TestMethod15)
		{	// 两点重合
			
			int res = add_Figure("R 2 -3 2 -3 ");
			Assert::AreEqual(res, 2);
		}

		TEST_METHOD(TestMethod16)
		{	// 两点重合
			
			int res = add_Figure("L 99999 88888 99999 88888 \n");
			Assert::AreEqual(res, 2);
		}

		TEST_METHOD(TestMethod17)
		{	// 两点重合
			
			int res = add_Figure("S 0 2 0 2 \n");
			Assert::AreEqual(res, 2);
		}

		TEST_METHOD(TestMethod18)
		{	// 无穷交点
			add_Figure("L 2 2 3 3 ");
			int res = add_Figure("L 0 0 -1 -1 \n");
			Assert::AreEqual(res, 4);
		}

		TEST_METHOD(TestMethod19)
		{	// 无穷交点
			
			add_Figure("S 2 2 4 4 ");
			int res = add_Figure("S 3 3 0 0 \n");
			Assert::AreEqual(res, 4);
		}

		TEST_METHOD(TestMethod20)
		{	// 无穷交点
			
			add_Figure("R 1 1 4 4 ");
			int res = add_Figure("S 2 2 0 0 \n");
			Assert::AreEqual(res, 4);
		}

		TEST_METHOD(TestMethod21)
		{	// 无穷交点
			
			add_Figure("R 1 1 1 0 ");
			int res = add_Figure("S 1 0 1 5 \n");
			Assert::AreEqual(res, 4);
		}

		TEST_METHOD(TestMethod22)
		{	// 无穷交点

			add_Figure("C 1 1 1  ");
			int res = add_Figure("C 1 1 1 \n");
			Assert::AreEqual(res, 4);
		}
	};
}
