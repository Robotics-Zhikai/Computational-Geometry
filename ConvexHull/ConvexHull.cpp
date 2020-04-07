#include "ConvexHull.h"

int ToLeftTest(Point PointA, Point PointB, Point PointC)
//From PointA to PointB,Test PointC.Left return 1,right return -1,on return 0
//Erro return -2 including z not equal and PointA==PointB
{
	if ((!(PointA.Point_Z == PointB.Point_Z && PointB.Point_Z == PointC.Point_Z)) || (PointA == PointB))
	{
		return -2;
	}
	double Area = PointA.Point_X * PointB.Point_Y - PointA.Point_Y * PointB.Point_X + PointB.Point_X * PointC.Point_Y \
		- PointB.Point_Y * PointC.Point_X + PointC.Point_X * PointA.Point_Y - PointC.Point_Y * PointA.Point_X;
	if (Area > 0)
		return 1;
	else if (Area < 0)
		return -1;
	else
		return 0;
}

int InTriangle(Point PointA, Point PointB, Point PointC,Point PointD) 
//Is D in Triangle ABC.
//if in,return 1.if not a triangle,return -2.if on triangle,return 0.if out of triangle,return -1.
{
	int partA = ToLeftTest(PointA, PointB, PointD);
	int partB = ToLeftTest(PointB, PointC, PointD);
	int partC = ToLeftTest(PointC, PointA, PointD);
	if (partA == -2 || partB == -2 || partC == -2)
		return -2;
	if (partA == 1 && partB == 1 && partC == 1)
		return 1;
	else
	{
		if ((partA == 0 && partB==1 && partC==1 )|| (partB == 0 && partA == 1 && partC == 1) ||\
			(partC == 0 && partA == 1 && partB == 1)|| (partA == 0 && partB == 0 && partC == 1) ||\
			(partA == 0 && partC == 0 && partB == 1)|| (partB == 0 && partC == 0 && partA == 1))
			return 0;
		else
			return -1;
	}		
}

vector<Point> DeleteRepeatPoints(vector<Point> Points) //删除点集中重复的点
{
	vector <Point> uniquePoints;
	for (int i = 0; i < Points.size(); i++)
	{
		int equal = 0;
		for (int j = 0; j < uniquePoints.size(); j++)
		{
			if (Points[i] == uniquePoints[j])
			{
				equal = 1;
				break;
			}
		}
		if (equal == 0)
			uniquePoints.push_back(Points[i]);
	}

	//vector<int> type;
	//for (int i = 0; i < Points.size(); i++)
	//	type.push_back(0);
	//int num = 0;
	//for (int i = 0; i < Points.size()-1; i++)
	//{
	//	if (type[i] == 0)
	//	{
	//		num++;
	//		type[i] = num;
	//		for (int j = i + 1; j < Points.size(); j++)
	//		{
	//			if (type[j] == 0)
	//			{
	//				if (Points[i] == Points[j])
	//					type[j] = num;
	//			}
	//		}
	//	}
	//}
	//for (int i = 0; i < Points.size()-1; i++)
	//{
	//	num = type[i];
	//	for (int j = i + 1; j < Points.size(); j++)
	//	{
	//		int flag = 0;
	//		while (num == type[j])
	//		{
	//			if (Points.begin() + j != Points.end())
	//			{
	//				Points.erase(Points.begin() + j);
	//				flag = 1;
	//			}
	//			else
	//				break;
	//		}
	//		if (flag == 1)
	//			j--;
	//	}
	//}
	return uniquePoints;
}

vector<Point> GetConvexHull_EP(vector <Point> Points)
//From Points,get ConvexHull.O(n^4) Extreme Point
{
	Points = DeleteRepeatPoints(Points);
	if (Points.size() <= 3)
		return Points;

	vector <int> True;
	for (int i = 0; i < Points.size(); i++)
		True.push_back(1);
	for (int i = 0; i < Points.size(); i++)
	{
		for (int j = i + 1; j < Points.size(); j++)
		{
			for (int k = j + 1; k < Points.size(); k++)
			{
				for (int m = 0; m < Points.size(); m++)
				{
					if (m != i&&m != j&&m != k)
					{
						int Pnum = InTriangle(Points[i], Points[j], Points[k], Points[m]);
						if (Pnum == 1 || Pnum == 0)
						{
							True[m] = 0;
						}
					}
				}
			}
		}
	}

	vector<Point> Result;
	for (int i = 0; i < True.size(); i++)
	{
		if (True[i] == 1)
			Result.push_back(Points[i]);
	}
	return Result;
}

int ComparePoint(Point A, Point B1, Point B2)
//compare vector(AB1) to vector(AB2) 
//AB1 greater than AB2 return 1
//equal return 0
//smaller return -1
//Erro return -2
{
	int result = ToLeftTest(A, B1, B2);
	if (result == 1)
	{
		return -1;
	}
	else if (result == -1)
	{
		return 1; //greater
	}
	else if (result == 0)
	{
		return 0;
	}
	else
		return -2;
}
vector<Point> BubbleSortExtremePoints(vector <Point> Points)
//冒泡排序排序极点 O(n^2)
//输入必须得是极点
{
	for (int num = 1; num < Points.size() - 1; num++)
	{
		for (int i = 1; i < Points.size() - num; i++)
		{
			int compareresult = ComparePoint(Points[0], Points[i], Points[i + 1]);
			if (compareresult == 1)
			{
				Point temp = Points[i];
				Points[i] = Points[i + 1];
				Points[i + 1] = temp;
			}
			else if (compareresult == -2)
				printf("sort erro");
		}
	}
	return Points;
}

vector<Point> GetConvexHull_EE(vector<Point>Points)
//O(n^3)
{
	//Points = DeleteRepeatPoints(Points);
	vector<Point> EE;//储存EE边
	Points.push_back(Points[0]);
	int i,j;
	for (i = 0; i < Points.size()-1; i++)
	{
		for (j = i + 1; j < Points.size(); j++)
		{
			if (Points[i] == Points[j]) //如果去掉这个，运行出错
				continue;
			int flag = 0;
			int init;
			int k;
			int breakflag = 0;
			for (k = 0; k < Points.size() - 1; k++)
			{
				if (k != i&&k != j)
				{
					if (flag == 0)
					{
						init = ToLeftTest(Points[i], Points[j], Points[k]);
						flag = 1;
					}
					else
					{
						int thistest = ToLeftTest(Points[i], Points[j], Points[k]);
						/*if (thistest == -2)
						{
							cout << Points[i].Point_X << " " << Points[i].Point_Y << " " << Points[i].Point_Z << endl;
							cout << Points[j].Point_X << " " << Points[j].Point_Y << " " << Points[j].Point_Z << endl;
							cout << Points[k].Point_X << " " << Points[k].Point_Y << " " << Points[k].Point_Z << endl;
							cout << (Points[i] == Points[j])<<endl;
							cout << -2<<endl;
						}*/
						//cout << thistest<<endl;
						if (thistest != init && init != 0 && thistest != 0)
						{
							//IsEE.push_back(0);
							breakflag = 1;
							break;
						}
						if (thistest!=0)
							init = thistest;
					}
				}
			}
			if (breakflag!=1)
			{
				EE.push_back(Points[i]);
				EE.push_back(Points[j]);
			}
		}
	}
	Points = DeleteRepeatPoints(EE);
	//Points = EE;
	return Points;
}