#include "ConvexHull.h"
#include "Visualization.h"
#include <time.h>
#include <math.h>

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
	//还存在的问题：偶尔会出现vector的错误
	//同时加上竖直和水平的很多点，就会出现找到好几个切点的情况而出现错误，可能与数值计算有关
	vector <Point> Points;
	Points = GenerateRandomPoint(13000, 0, 10, 0, 10); //可在可接受的时间内找到73000的点 但是会出现vector错误

	//vector <Point> Points2;
	//Points2 = GenerateRandomPoint(500, 9.99, 9.99, 0, 10);
	//for (int i = 0; i < Points2.size(); i++)
	//{
	//	Points.push_back(Points2[i]);
	//}
	//Points2 = GenerateRandomPoint(500, 0, 9.99, 10, 10);
	//for (int i = 0; i < Points2.size(); i++)
	//{
	//	Points.push_back(Points2[i]);
	//}

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

void Test_ICPT()
{
	vector <Point> Points;
	Points.push_back(Point(0, 0, 0));
	Points.push_back(Point(5, 0, 0));
	Points.push_back(Point(0, 5, 0));
	Points.push_back(Point(5, 5, 0));

	vector <Point> Points2;
	Points2.push_back(Point(0, 4, 0));
	cout<< InConvexPolygonTest(Points, Points2[0]);
	//for (int i = 0; i < Points2.size(); i++)
	//{
	//	int result = InConvexPolygonTest(Points, Points2[i]);
	//	if (result == 0|| result==1)
	//		cout<<"e";
	//}
	system("pause");
}

void Test_GetConvexHull_JM()//jarvis march算法
{
	vector <Point> Points;
	

	Points = GenerateRandomPoint(280000, 0, 10, 1, 10);
	//Points.push_back(Point(11, 5, 0));
	//Points.push_back(Point(10, 0.5, 0));
	//

	/*Points.push_back(Point(0.1, 0.5, 0));
	Points.push_back(Point(0.2, 0.5, 0));
	Points.push_back(Point(0.3, 0.5, 0));
	Points.push_back(Point(0.3, 0.5, 0));
	Points.push_back(Point(0.2, 0.5, 0));
	Points.push_back(Point(0.1, 0.5, 0));*/
	/*for (double i = 0; i < 10; i=i+0.1)
	{
		Points.push_back(Point(i, 0.5, 0));
	}
	for (double i = 10; i > 0; i = i - 0.1)
	{
		Points.push_back(Point(i, 0.5, 0));
	}
	*/

	vector <Point> Points2;
	Points2 = GenerateRandomPoint(1335,0, 9.99, 0.5, 0.5);
	for (int i = 0; i < Points2.size(); i++)
	{
		Points.push_back(Points2[i]);
	}
	//Points.push_back(Point(-1, 0.5, 0));
	Points2 = GenerateRandomPoint(1500, 11,11, 1, 10);
	for (int i = 0; i < Points2.size(); i++)
	{
		Points.push_back(Points2[i]);
	}

	OpenGLplot();
	AddBufferPoints(Points, 2.0f);
	Points = GetCHJarvisMarch(Points);
	AddBufferPoints(Points, 5.0f);
	vector <Point> temp = Points;
	//temp.push_back(Points[0]);

	//Points = BubbleSortPoints(Points);
	temp = Points;
	temp.push_back(Points[0]);
	AddBufferLines(temp, 1.0f);
	cout << Points.size() - 1 << endl;
	CloseGLplot();

}

void Test_GetConvexHull_GS()//GrahamScan算法
{
	clock_t start, end;
	
	vector <Point> Points;


	Points = GenerateRandomPoint(5000, 0, 10, 1, 10);
	//Points.push_back(Point(11, 5, 0));
	//Points.push_back(Point(10, 0.5, 0));
	//

	/*Points.push_back(Point(0.1, 0.5, 0));
	Points.push_back(Point(0.2, 0.5, 0));
	Points.push_back(Point(0.3, 0.5, 0));
	Points.push_back(Point(0.3, 0.5, 0));
	Points.push_back(Point(0.2, 0.5, 0));
	Points.push_back(Point(0.1, 0.5, 0));*/
	/*for (double i = 0; i < 10; i=i+0.1)
	{
	Points.push_back(Point(i, 0.5, 0));
	}
	for (double i = 10; i > 0; i = i - 0.1)
	{
	Points.push_back(Point(i, 0.5, 0));
	}
	*/

	vector <Point> Points2;
	Points2 = GenerateRandomPoint(850, 0, 9.99, 0.5, 0.5);
	for (int i = 0; i < Points2.size(); i++)
	{
		Points.push_back(Points2[i]);
	}
	//Points.push_back(Point(-1, 0.5, 0));
	Points2 = GenerateRandomPoint(850, 9, 9, 0.5, 10);
	for (int i = 0; i < Points2.size(); i++)
	{
		Points.push_back(Points2[i]);
	}
	

	OpenGLplot();
	AddBufferPoints(Points, 2.0f);
	start = clock();
	cout << "求" << Points.size() << "个点的凸包" << endl;
	Points = GetCHGrahamScan(Points);
	end = clock();

	double endtime = (double)(end - start) / CLOCKS_PER_SEC;
	cout << "GrahamScan算法用时" << endtime << "s" << endl;

	AddBufferPoints(Points, 5.0f);
	vector <Point> temp = Points;
	//temp.push_back(Points[0]);

	//Points = BubbleSortPoints(Points);
	temp = Points;
	temp.push_back(Points[0]);
	AddBufferLines(temp, 1.0f);
	cout <<"凸包的顶点个数："<< Points.size() - 1 << endl;
	CloseGLplot();

}

void main()
{
	//cout << sqrt(3.777);
	//Test_ToLeftTest();
	//Test_InTriangle();
	//Test_GetConvexHull_EP();
	//Test_GetConvexHull_EE();
	//Test_GetConvexHull_IC();
	//Test_ICPT();
	//Test_GetConvexHull_JM();
	Test_GetConvexHull_GS();
}

	
