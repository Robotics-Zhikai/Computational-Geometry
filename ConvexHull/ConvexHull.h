#ifndef CONVEXHULL
#define CONVEXHULL

#include <iostream>
#include <math.h>
#include <stdlib.h>
#include <stdio.h>
#include <vector>
#include <ctime>
#include <algorithm>
using namespace std;

class Point
{
public:
	double Point_X;
	double Point_Y;
	double Point_Z;
	Point(double x, double y, double z)
	{
		Point_X = x;
		Point_Y = y;
		Point_Z = z;
	}
	Point()
	{
		Point_X = 0;
		Point_Y = 0;
		Point_Z = 0;
	}
	int operator == (Point P2)
	{
		if (this->Point_X == P2.Point_X&&this->Point_Y == P2.Point_Y&&this->Point_Z == P2.Point_Z)
			return 1;
		else
			return 0;
	}
	int operator !=(Point P2)
	{
		return !(operator == (P2));
	}
};




int ToLeftTest(Point PointA, Point PointB, Point PointC); //From PointA to PointB,Test PointC.Left return 1,right return -1,on return 0
														 //Erro return -2 including z not equal and so on 
int InTriangle(Point PointA, Point PointB, Point PointC, Point PointD);

int InConvexPolygonTest(vector<Point> Points, Point A);

vector<Point> GetConvexHull_EP(vector <Point> Points);

vector<Point> BubbleSortPoints(vector <Point> Points);

vector<Point> GetConvexHull_EE(vector<Point>Points);

vector <Point> GetCHIncrementalConstruction(vector <Point> Points);

vector <Point> GetCHJarvisMarch(vector <Point> Points);
#endif
