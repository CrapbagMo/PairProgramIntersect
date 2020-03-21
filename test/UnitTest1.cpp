#include "pch.h"
#include "CppUnitTest.h"
#include "../intersect/PlaneContainer.h"
#include "../intersect/Circle.h"
#include "../intersect/Figure.h"
#include "../intersect/Line.h"
#include "../intersect/Point.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTest1
{
	TEST_CLASS(UnitTest1)
	{
	public:
		
		TEST_METHOD(TestMethod1)
		{	// 两直线相交
			PlaneContainer pc;
			pc.insert(new Line(1, 1, 2, 2, SL));
			pc.insert(new Line(0, 0, 0, 1, SL));
			int count = pc.countIntersectionPoints();
			Assert::AreEqual(count, 1);
		}

		TEST_METHOD(TestMethod2)
		{	// 两直线平行
			PlaneContainer pc;
			pc.insert(new Line(1, 1, 2, 2, SL));
			pc.insert(new Line(0, 1, 1, 2, SL));
			int count = pc.countIntersectionPoints();
			Assert::AreEqual(count, 0);
		}

		TEST_METHOD(TestMethod3)
		{	// 直线与圆相切
			PlaneContainer pc;
			pc.insert(new Line(0, 0, 0, 2, SL));
			pc.insert(new Circle(1, 0, 1));
			int count = pc.countIntersectionPoints();
			Assert::AreEqual(count, 1);
		}

		TEST_METHOD(TestMethod4)
		{	// 直线与圆相交
			PlaneContainer pc;
			pc.insert(new Line(0, 0, 0, 2, SL));
			pc.insert(new Circle(1, 0, 2));
			int count = pc.countIntersectionPoints();
			Assert::AreEqual(count, 2);
		}

		TEST_METHOD(TestMethod5)
		{	// 直线与圆无交点
			PlaneContainer pc;
			pc.insert(new Line(0, 0, 0, 2, SL));
			pc.insert(new Circle(2, 0, 1));
			int count = pc.countIntersectionPoints();
			Assert::AreEqual(count, 0);
		}

		TEST_METHOD(TestMethod6)
		{	// 两圆外切
			PlaneContainer pc;
			pc.insert(new Circle(0, 0, 1));
			pc.insert(new Circle(2, 0, 1));
			int count = pc.countIntersectionPoints();
			Assert::AreEqual(count, 1);
		}

		TEST_METHOD(TestMethod7)
		{	// 两圆内切
			PlaneContainer pc;
			pc.insert(new Circle(0, 0, 4));
			pc.insert(new Circle(3, 0, 1));
			int count = pc.countIntersectionPoints();
			Assert::AreEqual(count, 1);
		}

		TEST_METHOD(TestMethod8)
		{
			// 两圆外交
			PlaneContainer pc;
			pc.insert(new Circle(0, 0, 4));
			pc.insert(new Circle(5, 0, 2));
			int count = pc.countIntersectionPoints();
			Assert::AreEqual(count, 2);
		}

		TEST_METHOD(TestMethod9)
		{
			// 两圆内交
			PlaneContainer pc;
			pc.insert(new Circle(0, 0, 4));
			pc.insert(new Circle(3, 0, 2));
			int count = pc.countIntersectionPoints();
			Assert::AreEqual(count, 2);
		}

		TEST_METHOD(TestMethod10)
		{
			// 两圆不相交
			PlaneContainer pc;
			pc.insert(new Circle(0, 0, 4));
			pc.insert(new Circle(2, 0, 1));
			int count = pc.countIntersectionPoints();
			Assert::AreEqual(count, 0);
		}

		TEST_METHOD(TestMethod11)
		{
			// 两圆不相交
			PlaneContainer pc;
			pc.insert(new Circle(0, 0, 4));
			pc.insert(new Circle(6, 0, 1));
			int count = pc.countIntersectionPoints();
			Assert::AreEqual(count, 0);
		}

		TEST_METHOD(TestMethod12)
		{
			// 两线段相交
			PlaneContainer pc;
			pc.insert(new Line(0, 0, 2, 2, LS));
			pc.insert(new Line(2, 0, 0, 2, LS));
			int count = pc.countIntersectionPoints();
			Assert::AreEqual(count, 1);
		}

		TEST_METHOD(TestMethod13)
		{
			// 两线段不相交
			PlaneContainer pc;
			pc.insert(new Line(0, 0, 2, 2, LS));
			pc.insert(new Line(2, 0, 3, -1, LS));
			int count = pc.countIntersectionPoints();
			Assert::AreEqual(count, 0);
		}
		
		TEST_METHOD(TestMethod14)
		{
			// 两射线不相交
			PlaneContainer pc;
			pc.insert(new Line(0, 0, 2, 2, RL));
			pc.insert(new Line(2, 0, 3, -1, RL));
			int count = pc.countIntersectionPoints();
			Assert::AreEqual(count, 0);
		}

		TEST_METHOD(TestMethod15)
		{
			// 两射线相交
			PlaneContainer pc;
			pc.insert(new Line(0, 0, 2, 2, RL));
			pc.insert(new Line(3, -1, 2, 0, RL));
			int count = pc.countIntersectionPoints();
			Assert::AreEqual(count, 1);
		}

		TEST_METHOD(TestMethod16)
		{
			// 两射线平行
			PlaneContainer pc;
			pc.insert(new Line(0, 0, 2, 2, RL));
			pc.insert(new Line(2, 0, 1, -1, RL));
			int count = pc.countIntersectionPoints();
			Assert::AreEqual(count, 0);
		}

		TEST_METHOD(TestMethod17)
		{
			// 射线 圆 不相交
			PlaneContainer pc;
			pc.insert(new Circle(0, 0, 2));
			pc.insert(new Line(2, 2, 3, 3, RL));
			int count = pc.countIntersectionPoints();
			Assert::AreEqual(count, 0);
		}

		TEST_METHOD(TestMethod18)
		{
			// 射线 圆 相交
			PlaneContainer pc;
			pc.insert(new Circle(0, 0, 2));
			pc.insert(new Line(3, 3, 2, 2, RL));
			int count = pc.countIntersectionPoints();
			Assert::AreEqual(count, 2);
		}

		TEST_METHOD(TestMethod19)
		{
			// 射线 圆 内部相交
			PlaneContainer pc;
			pc.insert(new Circle(0, 0, 2));
			pc.insert(new Line(1, 0, 2, 2, RL));
			int count = pc.countIntersectionPoints();
			Assert::AreEqual(count, 1);
		}

		TEST_METHOD(TestMethod20)
		{
			// 射线 圆 相切
			PlaneContainer pc;
			pc.insert(new Circle(0, 0, 2));
			pc.insert(new Line(2, 3, 2, 2, RL));
			int count = pc.countIntersectionPoints();
			Assert::AreEqual(count, 1);
		}

		TEST_METHOD(TestMethod21)
		{
			// 射线 圆 不相交
			PlaneContainer pc;
			pc.insert(new Circle(0, 0, 2));
			pc.insert(new Line(2, 2, 2, 3, RL));
			int count = pc.countIntersectionPoints();
			Assert::AreEqual(count, 0);
		}

		TEST_METHOD(TestMethod22)
		{
			// 线段 圆 不相交
			PlaneContainer pc;
			pc.insert(new Circle(0, 0, 4));
			pc.insert(new Line(1, 1, 2, 2, LS));
			int count = pc.countIntersectionPoints();
			Assert::AreEqual(count, 0);
		}

		TEST_METHOD(TestMethod23)
		{
			// 线段 圆 相交
			PlaneContainer pc;
			pc.insert(new Circle(0, 0, 4));
			pc.insert(new Line(1, 1, 5, 6, LS));
			int count = pc.countIntersectionPoints();
			Assert::AreEqual(count, 1);
		}

		TEST_METHOD(TestMethod24)
		{
			// 线段 圆 不相交
			PlaneContainer pc;
			pc.insert(new Circle(0, 0, 4));
			pc.insert(new Line(7, 8, 5, 6, LS));
			int count = pc.countIntersectionPoints();
			Assert::AreEqual(count, 0);
		}

		TEST_METHOD(TestMethod25)
		{
			// 线段 圆 一个点
			PlaneContainer pc;
			pc.insert(new Circle(0, 0, 4));
			pc.insert(new Line(2, 3, 4, 0, LS));
			int count = pc.countIntersectionPoints();
			Assert::AreEqual(count, 1);
		}

		TEST_METHOD(TestMethod26)
		{
			// 线段 圆 相交两个点
			PlaneContainer pc;
			pc.insert(new Circle(0, 0, 4));
			pc.insert(new Line(-4, 0, 0, 4, LS));
			int count = pc.countIntersectionPoints();
			Assert::AreEqual(count, 2);
		}

		TEST_METHOD(TestMethod27)
		{
			// 线段 圆 相切
			PlaneContainer pc;
			pc.insert(new Circle(0, 0, 4));
			pc.insert(new Line(-1, 4, 3, 4, LS));
			int count = pc.countIntersectionPoints();
			Assert::AreEqual(count, 1);
		}

		TEST_METHOD(TestMethod28)
		{ 
			// 线段 圆 相交
			PlaneContainer pc;
			pc.insert(new Circle(0, 0, 4));
			pc.insert(new Line(0, 4, 0, 6, LS));
			int count = pc.countIntersectionPoints();
			Assert::AreEqual(count, 1);
		}

		TEST_METHOD(TestMethod29)
		{
			// 线段 圆 相交
			PlaneContainer pc;
			pc.insert(new Circle(0, 0, 4));
			pc.insert(new Line(4, 0, 4, 1, LS));
			int count = pc.countIntersectionPoints();
			Assert::AreEqual(count, 1);
		}


	};
}
