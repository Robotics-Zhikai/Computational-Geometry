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
int CheckSorted(vector<Point> Points)
//判断Points是否按Sorted排列 如果所有点都重复，那么Sorted判断仍为1 
//如果排序的初始点有些重复，对程序的性能不影响。
//O(n)的复杂度
{
	if (Points.size() < 3)
		return 1;
	vector <Point> Points1; //除去重复Points[0],只保留一个Points[0]的点集
	Points1.push_back(Points[0]);
	for (int i = 1; i < Points.size(); i++)
		if ((Points[i] == Points[0]) == 0)
			Points1.push_back(Points[i]);
	Points = Points1;

	int lastcomresult;
	if (Points.size() >= 3)
		lastcomresult = ComparePoint(Points[0], Points[1], Points[2]);

	for (int i = 2; i < Points.size() - 1; i++)
	{
		int comresult = ComparePoint(Points[0], Points[i], Points[i + 1]);
		if (((lastcomresult == 1 || lastcomresult == 0) && (comresult == 1 || comresult == 0))\
			|| ((lastcomresult == -1 || lastcomresult == 0) && (comresult == -1 || comresult == 0)))
		{
		}
		else
		{
			return 0;
		}
		lastcomresult = comresult;
	}
	return 1;
}

vector<Point> BubbleSortPoints(vector <Point> Points)
//冒泡排序排序点集 O(n^2) 不一定是极点集
//虽然不一定是极点集，但是只有极点集排序才有意义，若普通点集排序则会出现没有啥几何意义的情况
//去掉第一个点重复的情况
{
	if (CheckSorted(Points) == 1) //说明已经排好序了
		return Points;
	vector <Point> Points1; //除去重复Points[0],只保留一个Points[0]的点集
	Points1.push_back(Points[0]);
	for (int i = 1; i < Points.size(); i++)
		if ((Points[i] == Points[0]) == 0)
			Points1.push_back(Points[i]);
	Points = Points1;

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
			else if (compareresult == -2) //出现这种情况是排序的初始点有重合,但一开始的代码已经保证了不会出现这样的情况
			{
				printf("sort erro");
				break;
			}
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

int InConvexPolygonTest(vector<Point> Points,Point A)
//判断点A是否在Points构成的凸多边形内
//Points必须得是极点集，不要求不重复
//O(n)
//在内部return1 在边上 return0 在外部 return-1 Error return-2 
{
	if (Points.size() == 1)
	{
		if (A == Points[0])
			return 0;
		else
			return -1;
	}
	if (Points.size() == 2)
	{
		if (Points[0] == Points[1])
		{
			if (A == Points[0])
				return 0;
			else
				return -1;
		}
		else
		{
			int result = ToLeftTest(Points[0], Points[1],A);
			if (result == 1 || result == -1)
				return -1;
			else if (result == 0)
				return 0;
			else
				return -2;
		}
	}
	if (CheckSorted(Points)==0)
	{
		Points = BubbleSortPoints(Points);
	}
	Points.push_back(Points[0]);
	vector<int> testresult;
	for (int i = 0; i < Points.size()-1; i++)
	{
		if (Points[i] == Points[i + 1])
			continue;
		int currentresult = ToLeftTest(Points[i], Points[i+1], A);
		testresult.push_back(currentresult);
	}
	int last = testresult[0];
	int i;
	int count0 = 0;
	for (i = 0; i < testresult.size(); i++)
	{
		if (testresult[i] == 0)
			count0++;
		if (testresult[i] != 0 && testresult[i] != last && last!=0)
		{
			break;
		}
		if (testresult[i]!=0)
			last = testresult[i];
	}
	if (i >= testresult.size())
	{
		if (count0 >= 1)
			return 0;
		else
			return 1;
	}
	else
		return -1;
}

vector <Point> EraseVectorPoints(vector <Point> Points,vector<int> eraseIndex)
//删除eraseIndex索引的Points点集
{
	if (eraseIndex.size() <= 0)
		return Points;
	sort(eraseIndex.begin(), eraseIndex.end());
	vector<int> uniqueeraseindex;
	uniqueeraseindex.push_back(eraseIndex[0]);
	for (int i = 1; i < eraseIndex.size(); i++)
	{
		if (*(uniqueeraseindex.end()-1) == eraseIndex[i])
			continue;
		uniqueeraseindex.push_back(eraseIndex[i]);
	}

	vector<Point> newpoints;
	int numerase = 0;
	for (int j = 0; j < Points.size(); j++)
	{
		if (j != uniqueeraseindex[numerase])
			newpoints.push_back(Points[j]);
		else
		{
			numerase++;
			if (numerase >= uniqueeraseindex.size())
				numerase = uniqueeraseindex.size() - 1;
		}
	}
	return newpoints;
}

vector <int> EraseVectorint(vector <int> Points, vector<int> eraseIndex)
{
	if (eraseIndex.size() <= 0)
		return Points;
	sort(eraseIndex.begin(), eraseIndex.end());
	vector<int> uniqueeraseindex;
	uniqueeraseindex.push_back(eraseIndex[0]);
	for (int i = 1; i < eraseIndex.size(); i++)
	{
		if (*(uniqueeraseindex.end()-1) == eraseIndex[i])
			continue;
		uniqueeraseindex.push_back(eraseIndex[i]);
	}

	vector<int> newpoints;
	int numerase = 0;
	for (int j = 0; j < Points.size(); j++)
	{
		if (j != uniqueeraseindex[numerase])
			newpoints.push_back(Points[j]);
		else
		{
			numerase++;
			if (numerase >= uniqueeraseindex.size())
				numerase = uniqueeraseindex.size() - 1;
		}
	}
	return newpoints;
}

double normPoints(Point A, Point B)
//返回A B之间的距离
{
	return sqrt((A.Point_X - B.Point_X)*(A.Point_X - B.Point_X)+ \
		(A.Point_Y - B.Point_Y)*(A.Point_Y - B.Point_Y)+\
		(A.Point_Z - B.Point_Z)*(A.Point_Z - B.Point_Z));
}
vector <Point> GetCHIncrementalConstruction(vector <Point> Points)
//用增量法得到凸包 但是未经过排序
{
	//Points = DeleteRepeatPoints(Points);
	if (Points.size() <= 3)
		return Points;
	vector <Point> CHPoints;
	CHPoints.push_back(Points[0]);
	for (int i = 1; i < Points.size(); i++)
	{
		if (*(CHPoints.end()-1) == Points[i])
			continue;
		//CHPoints = BubbleSortPoints(CHPoints); //似乎根本就用不着排序
		int Testresult = InConvexPolygonTest(CHPoints, Points[i]); //O(n)
		if (Testresult == 1 || Testresult == 0)
			continue;
		else if (Testresult == -2)
		{
			printf("出现错误\n");
			return CHPoints;
		}
		int j;
		//到这一步的话就根本不可能出现CHPoints中有重合点的情况
		if (CHPoints.size() <= 2)
		{
			int InsertIndex;
			CHPoints.push_back(Points[i]);
			continue;
		}
		vector <int> Tangent;
		for (j = 0; j < CHPoints.size(); j++)
		{
			int leftnum = j - 1;
			int rightnum = j + 1;
			if (leftnum < 0)
				leftnum = CHPoints.size() - 1;
			if (rightnum >= CHPoints.size())
				rightnum = 0;
			int L = ToLeftTest(Points[i], CHPoints[j], CHPoints[leftnum]);
			int R = ToLeftTest(Points[i], CHPoints[j], CHPoints[rightnum]);
			if (L == 0 || R == 0)
			{
				printf("d");
			}
			if (((L == 1 || L == 0) && (R == 1 || R == 0)) || ((L == -1 || L == 0) && (R == -1 || R == 0)))
				Tangent.push_back(j);
		}
		//if (Tangent.size() > 2)
		//{
		//	printf("s");
		//}

		//对于点判断在多边形外但是与多边形的某条边或某两条边在同一直线上
		vector <int> eraseIndex;
		for (j = 0; j < Tangent.size(); j++)
		{
			int last, next;
		/*	last = j;
			next = k;*/
				
			if (j == Tangent.size() - 1)
			{
				last = j;
				next = 0;
			}
			else
			{
				last = j;
				next = j + 1;
			}
			if (ToLeftTest(CHPoints[Tangent[last]], CHPoints[Tangent[next]], Points[i]) == 0)
			{
				if (normPoints(Points[i], CHPoints[Tangent[last]]) < normPoints(Points[i], CHPoints[Tangent[next]]))
					eraseIndex.push_back(last);
				else
					eraseIndex.push_back(next);
			}
		}

		vector <int> Index;
		if (eraseIndex.size() >= 2)
		{
			printf("s");
		}
		for (j = 0; j < eraseIndex.size(); j++)
			Index.push_back(Tangent[eraseIndex[j]]);
		Tangent = EraseVectorint(Tangent, eraseIndex);
		CHPoints = EraseVectorPoints(CHPoints, Index);

		//去掉新引入点造成的点集在多边形内的点
		vector<int> neweraseindex;
		if (CHPoints.size() >= 3)
		{
			
			vector <Point> newpoints;
			
			newpoints.push_back(CHPoints[Tangent[0]]);
			
			newpoints.push_back(CHPoints[Tangent[1]]);
			newpoints.push_back(Points[i]);
			for (j = 0; j < CHPoints.size(); j++)
			{
				if (j != Tangent[0] && j != Tangent[1] )
				{
					int result = InConvexPolygonTest(newpoints, CHPoints[j]);
					if (result == 1|| result==0 )
						neweraseindex.push_back(j);
				}
			}
		}
		Point TangentPointA = CHPoints[Tangent[0]];
		Point TangentPointB = CHPoints[Tangent[1]];
		CHPoints = EraseVectorPoints(CHPoints, neweraseindex);

		//找到切点，将新点插入二者之间
		for (j = 0; j < CHPoints.size(); j++)
		{
			int last, next;
			if (j == CHPoints.size() - 1)
			{
				last = j;
				next = 0;
			}
			else
			{
				last = j;
				next = j + 1;
			}
			if ((CHPoints[last] == TangentPointA && CHPoints[next] == TangentPointB) || \
				(CHPoints[last] == TangentPointB && CHPoints[next] == TangentPointA))
				break;
		}
		if (j >= CHPoints.size())
			CHPoints.push_back(Points[i]);
		else
			CHPoints.insert(CHPoints.begin() + j + 1,Points[i]);

		//用下边的处理方法复杂、出错、耗时多
		/*int storeindex;
		for (j = 1; j < CHPoints.size()-1; j++)
		{
			int comp1 = ComparePoint(CHPoints[0], Points[i], CHPoints[j]);
			int comp2 = ComparePoint(CHPoints[0], Points[i], CHPoints[j + 1]);
			if (((comp1 == 1) && (comp2 == -1))\
				|| ((comp1 == -1) && (comp2 == 1)))
			{
				storeindex = j;
				break;
			}
		}
		if (j >= CHPoints.size() - 1)
		{
			if (CHPoints.size() >= 3)
			{
				int comp1, comp2;
				comp1 = ComparePoint(CHPoints[0], Points[i], CHPoints[1]);
				comp2 = ComparePoint(CHPoints[0], Points[i], CHPoints[2]);
				if (((comp1 == 1) && (comp2 == 1)) || ((comp1 == -1) && (comp2 == -1)))
					CHPoints.insert(CHPoints.begin()+1 , Points[i]);
				else
					CHPoints.push_back(Points[i]);
			}
			else
			{
				CHPoints.push_back(Points[i]);
			}
		}
		else
			CHPoints.insert(CHPoints.begin() + storeindex + 1,Points[i]);*/
	}
	return CHPoints;
}

int FindLowestThenLeftmost(vector <Point> Points)
//找到最低和最左的点
{
	if (Points.size() == 0)
		//return Point(0, 0, 0);
		return -1;
	if (Points.size() == 1)
		//return Points[0];
		return 0;
	double ymin = Points[0].Point_Y;
	int YminIndex = 0;
	vector <Point> yminPoints;
	yminPoints.push_back(Points[0]);
	for (int i = 1; i < Points.size(); i++)
	{
		if (Points[i].Point_Y < ymin)
		{
			ymin = Points[i].Point_Y;
			YminIndex = i;
			yminPoints.clear();
			yminPoints.push_back(Points[i]);
		}
		else if (Points[i].Point_Y == ymin)
			yminPoints.push_back(Points[i]);
	}
	double xmin = yminPoints[0].Point_X;
	Point result = yminPoints[0];
	for (int i = 1; i < yminPoints.size(); i++)
	{
		if (yminPoints[i].Point_X < xmin)
			result = yminPoints[i];
	}
	int Index = 0;
	for (int i = 0; i < Points.size(); i++)
	{
		if (Points[i] == result)
		{
			Index = i;
			break;
		}
	}
	//return result;
	return Index;
}

vector <Point> GetCHJarvisMarch(vector <Point> Points)
{
	int LTL = FindLowestThenLeftmost(Points);
	//Point Last = Points[LTL];
	int Last = LTL;
	vector <int> Result;
	Result.push_back(Last);

	while (1)
	{
		int MaxIndex;
		int num = 0;
		for (int i = 0; i < Points.size(); i++)
		{
			if (i == Last)
				continue;
			num++;
			if (num == 1)
				MaxIndex = i;
			else
			{
				if (ToLeftTest(Points[Last], Points[MaxIndex], Points[i]) == -1)
				{
					MaxIndex = i;
				}
			}
		}
		if (MaxIndex == LTL)
			break;
		Result.push_back(MaxIndex);
		Last = MaxIndex;
	}
	vector<Point> ReusltPoints;
	for (int i = 0; i < Result.size(); i++)
	{
		ReusltPoints.push_back(Points[i]);
	}









	
	
	/*int lasttest;
	for (int i = 0; i < Points.size(); i++)
	{
		if (Points[i] == Last)
			continue;
		int num = 0;
		int j;
		for (j = 0; j < Points.size(); j++)
		{
			if (j != i&&Points[j] != Last)
			{
				num++;
				int test = ToLeftTest(Last, Points[i], Points[j]);
				if (num == 1)
					lasttest = test;
				if (test != lasttest&&test != 0 && lasttest != 0)
					break;
				lasttest = test;
			}
		}
		if (j >= Points.size())
		{
			Result.push_back(Points[i]);
			Last = Points[i];
		}
	}*/

	return ReusltPoints;
}