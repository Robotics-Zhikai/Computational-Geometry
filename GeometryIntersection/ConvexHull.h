#ifndef CONVEXHULL
#define CONVEXHULL

#include <iostream>
#include <math.h>
#include <stdlib.h>
#include <stdio.h>
#include <vector>
#include <ctime>
#include <algorithm>
#include "CustomizeDataType.h"
using namespace std;



vector<Point> GenerateRandomPoint(int pointsNum, float RangeXmin, float RangeXmax, float RangeYmin, float RangeYmax);

int ToLeftTest(Point PointA, Point PointB, Point PointC); //From PointA to PointB,Test PointC.Left return 1,right return -1,on return 0
														  //Erro return -2 including z not equal and so on 
int InTriangle(Point PointA, Point PointB, Point PointC, Point PointD);

int InConvexPolygonTest(vector<Point> Points, Point A);

vector<Point> GetConvexHull_EP(vector <Point> Points);

vector<Point> BubbleSortPoints(vector <Point> Points);

vector<Point> GetConvexHull_EE(vector<Point>Points);

vector <Point> GetCHIncrementalConstruction(vector <Point> Points);

vector <Point> GetCHJarvisMarch(vector <Point> Points);

vector <Point> GetCHGrahamScan(vector<Point> Points);

vector <Point> GetCHDivideMerge(vector <Point> Points);
#endif