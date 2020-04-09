#include "ConvexHull.h"
#include "Visualization.h"


vector<Point> GenerateRandomPoint(int pointsNum, float RangeXmin, float RangeXmax, float RangeYmin, float RangeYmax)
//generate pointsNum random points in [RangeXmin,RangeXmax,RangeYmin,RangeYmax]
{
	vector<Point> Points;
	srand((int)time(0));  // 产生随机种子  把0换成NULL也行
	for (int i = 0; i < pointsNum; i++)
	{
		Point Pointtemp;
		float a = RangeXmin;
		float b = RangeXmax;
		Pointtemp.Point_X = a + (rand() / double(RAND_MAX))*(b - a);
		a = RangeYmin;
		b = RangeYmax;
		Pointtemp.Point_Y = a + (rand() / double(RAND_MAX))*(b - a);
		Pointtemp.Point_Z = 0;
		Points.push_back(Pointtemp);
	}
	return Points;
}

void Test_ToLeftTest()
{
	Point PointA(30,30,0);
	Point PointB(30, 30, 0);
	/*Point PointC(5, 10, 0);*/
	Point PointC(30, 40.00000000000001, 0);
	//initgraph(200, 200);   // 这里和 TC 略有区别
	//line(PointA.Point_X, PointA.Point_Y, PointB.Point_X, PointB.Point_Y);
	//putpixel(PointC.Point_X, PointC.Point_Y, 0);
	//circle(200, 200, 100); // 画圆，圆心(200, 200)，半径 100
	int num = ToLeftTest(PointA, PointB, PointC);

}

void Test_InTriangle()
{
	Point PointA(0, 0, 0);
	Point PointB(10, 0, 0);
	/*Point PointC(5, 10, 0);*/
	Point PointC(0, 10, 0);
	Point PointD(-1, 6, 0);
	cout << InTriangle(PointA,PointB,PointC,PointD);
}

void Test_GetConvexHull_EP()
{
	vector <Point> Points;
	Points = GenerateRandomPoint(100, 0, 10, 0, 10);
	//vector <Point> Points2;
	//Points2 = GenerateRandomPoint(0, 11, 11, 11, 11);
	//for (int i = 0; i < Points2.size(); i++)
	//{
	//	Points.push_back(Points2[i]);
	//}

	OpenGLplot();
	AddBufferPoints(Points, 2.0f);
	Points = GetConvexHull_EP(Points);
	AddBufferPoints(Points, 5.0f);
	vector <Point> temp = Points;
	temp.push_back(Points[0]);
	//AddBufferLines(temp, 1.0f);
	Points = BubbleSortPoints(Points);
	temp = Points;
	temp.push_back(Points[0]);
	AddBufferLines(temp, 1.0f);
	CloseGLplot();
	
}

void Test_GetConvexHull_EE()
{
	vector <Point> Points;
	Points = GenerateRandomPoint(2500, 0, 10, 0, 10);
	vector <Point> Points2;
	Points2 = GenerateRandomPoint(500, 10, 10, 5, 5);
	for (int i = 0; i < Points2.size(); i++)
	{
		Points.push_back(Points2[i]);
	}

	OpenGLplot();
	AddBufferPoints(Points, 2.0f);
	Points = GetConvexHull_EE(Points);
	AddBufferPoints(Points, 5.0f);
	vector <Point> temp = Points;
	//temp.push_back(Points[0]);

	Points = BubbleSortPoints(Points);
	temp = Points;
	temp.push_back(Points[0]);
	AddBufferLines(temp, 1.0f);
	CloseGLplot();

}

void Test_GetConvexHull_IC()//增量法求凸包
{
	vector <Point> Points;
	Points = GenerateRandomPoint(500, 0, 10, 0, 10);
	vector <Point> Points2;
	Points2 = GenerateRandomPoint(0, 10, 10, 5, 5);
	for (int i = 0; i < Points2.size(); i++)
	{
		Points.push_back(Points2[i]);
	}

	OpenGLplot();
	AddBufferPoints(Points, 2.0f);
	Points = GetCHIncrementalConstruction(Points);
	AddBufferPoints(Points, 5.0f);
	vector <Point> temp = Points;
	//temp.push_back(Points[0]);

	Points = BubbleSortPoints(Points);
	temp = Points;
	temp.push_back(Points[0]);
	AddBufferLines(temp, 1.0f);
	CloseGLplot();

}

void main()
{
	//cout << sqrt(3.777);
	//Test_ToLeftTest();
	//Test_InTriangle();
	//Test_GetConvexHull_EP();
	//Test_GetConvexHull_EE();
	Test_GetConvexHull_IC();
}


