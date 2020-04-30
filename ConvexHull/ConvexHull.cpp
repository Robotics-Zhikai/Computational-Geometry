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
	double yuzhi = 1e-10;
	if (Area > yuzhi)
		return 1;
	else if (Area < -yuzhi)
		return -1;
	else if (Area<yuzhi && Area>-yuzhi)
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

int CheckSortedCW(vector <Point> Points) 
//判断是否是逆时针有序  
//是返回1，否则返回0
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
	if (lastcomresult == 1)
		return 0;

	for (int i = 2; i < Points.size() - 1; i++)
	{
		int comresult = ComparePoint(Points[0], Points[i], Points[i + 1]);
		if  ((lastcomresult == -1 || lastcomresult == 0) && (comresult == -1 || comresult == 0))
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

vector<Point> BubbleSortPointsCW(vector <Point> Points)
//逆时针冒泡排序
//冒泡排序排序点集 O(n^2) 不一定是极点集
//虽然不一定是极点集，但是只有极点集排序才有意义，若普通点集排序则会出现没有啥几何意义的情况
//去掉第一个点重复的情况
{
	if (CheckSortedCW(Points) == 1) //说明已经逆时针排好序了
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
		{
			result = yminPoints[i];
			xmin = yminPoints[i].Point_X;
		}
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

Point FindLowestThenLeftmostPoint(vector <Point> Points)
//找到最低和最左的点
{
	if (Points.size() == 0)
		return Point(0, 0, 0);
		//return -1;
	if (Points.size() == 1)
		return Points[0];
		//return 0;
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
		{
			result = yminPoints[i];
			xmin = yminPoints[i].Point_X;
		}
	}
	/*int Index = 0;
	for (int i = 0; i < Points.size(); i++)
	{
		if (Points[i] == result)
		{
			Index = i;
			break;
		}
	}*/
	return result;
	//return Index;
}
vector <Point> GetCHJarvisMarch(vector <Point> Points)
////jarvismarch算法
//O(hn) output sensitive h为凸包顶点数
{
	Point LTL = FindLowestThenLeftmostPoint(Points);
	Point Last = LTL;
	vector <Point> ResultPoints;
	ResultPoints.push_back(Last);

	int k;
	for (k = 0; k < Points.size(); k++)
	{
		Point MaxIndex;
		int num = 0;
		for (int i = 0; i < Points.size(); i++)
		{
			if (Points[i] == Last)
				continue;
			num++;
			if (num == 1)
				MaxIndex = Points[i];
			else
			{
				if (Last != MaxIndex)
				{
					int test = ToLeftTest(Last, MaxIndex, Points[i]);
					if (test == -1)
					{
						MaxIndex = Points[i];
					}
				/*	else if(test!=1)
					{
						cout << test << endl;
					}*/
				}
			}
		}
		if (MaxIndex == LTL)
			break;	
		ResultPoints.push_back(MaxIndex);
		Last = MaxIndex;
	}
	if (k >= Points.size())
	{
		printf("erro");
		return Points;
	}
	/*vector<Point> ReusltPoints;
	for (int i = 0; i < Result.size(); i++)
	{
		ReusltPoints.push_back(Points[Result[i]]);
	}*/
	vector<int> eraseIndex;
	for (int i = 0; i < ResultPoints.size()-2; i++)
	{
		if (ToLeftTest(ResultPoints[i], ResultPoints[i + 1], ResultPoints[i + 2]) == 0)
		{
			eraseIndex.push_back(i + 1);
		}
	}
	ResultPoints = EraseVectorPoints(ResultPoints, eraseIndex);

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
	return ResultPoints;
}

Point FindLowestThenRightmostPoint(vector <Point> Points)
//找到最低和最右的点
{
	if (Points.size() == 0)
		return Point(0, 0, 0);
	//return -1;
	if (Points.size() == 1)
		return Points[0];
	//return 0;
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
	double xmax = yminPoints[0].Point_X;
	Point result = yminPoints[0];
	for (int i = 1; i < yminPoints.size(); i++)
	{
		if (yminPoints[i].Point_X > xmax)
		{
			result = yminPoints[i];
			xmax = yminPoints[i].Point_X;
		}
	}
	/*int Index = 0;
	for (int i = 0; i < Points.size(); i++)
	{
	if (Points[i] == result)
	{
	Index = i;
	break;
	}
	}*/
	return result;
	//return Index;
}

void TwoSplitMerge(Point & ref,vector<Point> & Points, vector<Point> & tmp, int split1Left, int split1Right, int split2Left, int split2Right)
{
	//if (Left == Right)
	//	return;

	//int split1Left = Left;
	//int split1Right = Left + ceil(double((Right - Left + 1) / 2.0)) - 1;
	//int split2Left = split1Right + 1;
	//int split2Right = Right;

	int split1 = split1Left;
	int split2 = split2Left;
	int tmpzz = 0;
	while (split1 <= split1Right && split2 <= split2Right)
	{
		int test = ToLeftTest(ref, Points[split1], Points[split2]);
		if (test == 1)
		{
			tmp[split1Left + tmpzz] = Points[split2];
			split2++;
			tmpzz++;
		}
		else if (test == -1)
		{
			tmp[split1Left + tmpzz] = Points[split1];
			split1++;
			tmpzz++;
		}
		else if (test == 0)
		{
			tmp[split1Left + tmpzz] = Points[split1];
			split1++;
			tmpzz++;
			tmp[split1Left + tmpzz] = Points[split2];
			split2++;
			tmpzz++;
		}
		/*if (Data[split2] < Data[split1])
		{
			tmp[split1Left + tmpzz] = Data[split2];
			split2++;
			tmpzz++;
		}*/
		/*else if (Data[split2] > Data[split1])
		{
			tmp[split1Left + tmpzz] = Data[split1];
			split1++;
			tmpzz++;
		}*/
		/*else
		{
			tmp[split1Left + tmpzz] = Data[split1];
			split1++;
			tmpzz++;
			tmp[split1Left + tmpzz] = Data[split2];
			split2++;
			tmpzz++;
		}*/
	}
	while (split1 <= split1Right)
	{
		tmp[split1Left + tmpzz] = Points[split1];
		tmpzz++;
		split1++;
	}
	while (split2 <= split2Right)
	{
		tmp[split1Left + tmpzz] = Points[split2];
		tmpzz++;
		split2++;
	}
	tmpzz--;
	while (tmpzz >= 0) //需要把融合后的一段序列返回到Data中
	{
		Points[split1Left + tmpzz] = tmp[split1Left + tmpzz];
		tmpzz--;
	}
}

void Merge(Point & ref,vector <Point> & Points, vector<Point> & tmp, int Left, int Right)
{
	if (Right - Left == 1)
	{
		int test = ToLeftTest(ref, Points[Left], Points[Right]);
		if (test == 1)
		{
			Point temp;
			temp = Points[Left];
			Points[Left] = Points[Right];
			Points[Right] = temp;
		}
		return;
	}
	else if (Right == Left)
		return;
	int split1Left = Left;
	int split1Right = Left + ceil(double((Right - Left + 1) / 2.0)) - 1;
	int split2Left = split1Right + 1;
	int split2Right = Right;

	Merge(ref,Points, tmp, Left, split1Right);
	Merge(ref,Points, tmp, split2Left, split2Right);

	TwoSplitMerge(ref,Points, tmp, split1Left, split1Right, split2Left, split2Right);
	return;
}

vector <Point> MergeSortRecur(Point ref,vector <Point> Points, int Left, int Right)
{
	if (Points.size() <= 1)
		return Points;
	vector <Point> tmp = Points;
	Merge(ref,Points, tmp, Left, Right);
	return Points;
}

vector <Point> PreSorting(vector <Point> Points, Point LTL)
{
	vector <Point> DeleteRepeatPoint;
	for (int i = 0; i < Points.size(); i++) 
	{
		if (Points[i] == LTL)
			continue;
		DeleteRepeatPoint.push_back(Points[i]);
	}

	//用n的时间复杂度判断是否已经是排序完成
	DeleteRepeatPoint.insert(DeleteRepeatPoint.begin(), LTL);
	if ((DeleteRepeatPoint.size()>=2)&&(CheckSorted(DeleteRepeatPoint) == 1))
	{
		int test = ToLeftTest(LTL, DeleteRepeatPoint[0], DeleteRepeatPoint[1]);
		int i = 1;
		while ((test == 0) && (DeleteRepeatPoint.size() >= 3) && (i + 1 < DeleteRepeatPoint.size()))
		{
			test = ToLeftTest(LTL, DeleteRepeatPoint[i], DeleteRepeatPoint[i+1]);
			i = i + 1;
		}
		if (test == -1)
		{
			return DeleteRepeatPoint;
		}
	}
	DeleteRepeatPoint.erase(DeleteRepeatPoint.begin());

	DeleteRepeatPoint = MergeSortRecur(LTL, DeleteRepeatPoint, 0, DeleteRepeatPoint.size()-1);//归并排序
	//for (int num = 1; num < DeleteRepeatPoint.size() ; num++)
	//{
	//	for (int i = 0; i < DeleteRepeatPoint.size()-num; i++)
	//	{
	//		int test = ToLeftTest(LTL, DeleteRepeatPoint[i], DeleteRepeatPoint[i+1]);
	//		if (test == 1)
	//		{
	//			Point temp;
	//			temp = DeleteRepeatPoint[i];
	//			DeleteRepeatPoint[i] = DeleteRepeatPoint[i + 1];
	//			DeleteRepeatPoint[i + 1] = temp;
	//		}
	//	}
	//} //冒泡排序
	return DeleteRepeatPoint;
}
int IfInLine(Point A, Point B,Point C) 
//判断C在共AB组成的直线的基础上是否在两端点内
//如果在，那么return 1
//否则 如果在AB方向上之外 return -1
//如果在BA方向上之外，return -3
//如果等于A或者B return -2
{
	if (A == C || B == C)
		return -2;
	if (A.Point_X == B.Point_X)
	{
		if ((C.Point_Y<B.Point_Y && C.Point_Y>A.Point_Y) || (C.Point_Y<A.Point_Y && C.Point_Y>B.Point_Y))
			return 1;
		else if (C.Point_Y > B.Point_Y)
			return -1;
		else if (C.Point_Y < A.Point_Y)
			return -3;
	}
	else
	{
		if ((C.Point_X<B.Point_X && C.Point_X>A.Point_X) || (C.Point_X<A.Point_X && C.Point_X>B.Point_X))
			return 1;
		else if (C.Point_X > B.Point_X)
			return -1;
		else if (C.Point_X < A.Point_X)
			return -3;
	}
}
vector <Point> GetCHGrahamScan(vector<Point> Points)
{
	Point LTL = FindLowestThenLeftmostPoint(Points);
	vector <Point> T_Stack;

	T_Stack = PreSorting(Points, LTL); //主要耗费时间耗费在排序这里了

	Point NextEP = *(T_Stack.end()-1);
	T_Stack.pop_back();
	vector <Point> S_Stack;
	S_Stack.push_back(LTL);
	S_Stack.push_back(NextEP);
	while (T_Stack.empty() == 0)
	{
		Point A = *(S_Stack.end() - 2);
		Point B = *(S_Stack.end() - 1);
		Point C = *(T_Stack.end() - 1);
		int test = ToLeftTest(A, B, C);
		if (test == 0)
		{
			int ifinli = IfInLine(A, B, C);
			if (ifinli == 1 || ifinli == -2 || ifinli == -3)
				T_Stack.pop_back();
			else if (ifinli == -1)
			{
				S_Stack.push_back(C);
				T_Stack.pop_back();
			}
		}
		else if (test == 1)
		{
			S_Stack.push_back(C);
			T_Stack.pop_back();
		}
		else if (test == -1)
		{
			S_Stack.pop_back();
		}
	}
	vector<int> eraseIndex; //删除共线的点内部的所有点
	for (int i = 0; i < S_Stack.size() - 2; i++)
	{
		if (ToLeftTest(S_Stack[i], S_Stack[i + 1], S_Stack[i + 2]) == 0)
		{
			eraseIndex.push_back(i + 1);
		}
	}
	S_Stack = EraseVectorPoints(S_Stack, eraseIndex);
	return S_Stack;
}

vector <Point> ModifyFirEle(vector <Point> Points,int pos)
//保持逆时针顺序不变，将pos位置的元素放置到首位
{
	if (pos == 0)
		return Points;
	vector <Point> Result = Points;
	int movvalue = pos;
	for (int i = 0; i < Points.size(); i++)
	{
		int fakepos = i - movvalue;
		if (fakepos < 0)
			fakepos = Points.size() + fakepos;
		Result[fakepos] = Points[i];
	}
	return Result;
}

vector <Point> GetCHGrahamScanWithoutSort(vector<Point> Points)
//不包括排序的GS算法
//输入应该是Points排好序的 应该保证逆时针的顺序
{
	//int LTLindex = FindLowestThenLeftmost(Points);
	//Point LTL = FindLowestThenLeftmostPoint(Points);

	vector <Point> T_Stack;
	for (int i = Points.size() - 1; i >= 1; i--)
		T_Stack.push_back(Points[i]);


	//for (int i = LTLindex - 1; i >= 0; i--)
	//	if (Points[i]!=Points[LTLindex])
	//		T_Stack.push_back(Points[i]);
	//for (int i = Points.size()-1; i >= LTLindex + 1; i--)
	//	if (Points[i] != Points[LTLindex])
	//		T_Stack.push_back(Points[i]);

	//T_Stack = Points;
	//T_Stack = PreSorting(Points, LTL); //主要耗费时间耗费在排序这里了

	Point NextEP = *(T_Stack.end() - 1);
	T_Stack.pop_back();
	vector <Point> S_Stack;
	S_Stack.push_back(Points[0]);
	S_Stack.push_back(NextEP);
	while (T_Stack.empty() == 0)
	{
		Point A = *(S_Stack.end() - 2);
		Point B = *(S_Stack.end() - 1);
		Point C = *(T_Stack.end() - 1);
		int test = ToLeftTest(A, B, C);
		if (test == 0)
		{
			int ifinli = IfInLine(A, B, C);
			if (ifinli == 1 || ifinli == -2 || ifinli == -3)
				T_Stack.pop_back();
			else if (ifinli == -1)
			{
				S_Stack.push_back(C);
				T_Stack.pop_back();
			}
		}
		else if (test == 1)
		{
			S_Stack.push_back(C);
			T_Stack.pop_back();
		}
		else if (test == -1)
		{
			S_Stack.pop_back();
			if (S_Stack.size() == 1 && T_Stack.empty()==0)
			{
				S_Stack.push_back(*(T_Stack.end() - 1));
				T_Stack.pop_back();
			}
		}
	}
	vector<int> eraseIndex; //删除共线的点内部的所有点
	for (int i = 0; i < S_Stack.size() - 2; i++)
	{
		if (ToLeftTest(S_Stack[i], S_Stack[i + 1], S_Stack[i + 2]) == 0)
		{
			eraseIndex.push_back(i + 1);
		}
	}
	S_Stack = EraseVectorPoints(S_Stack, eraseIndex); 
	
	Point tmp1 = S_Stack[S_Stack.size() - 2];
	Point tmp2 = S_Stack[S_Stack.size() - 1];
	Point tmp3 = S_Stack[0];
	while (ToLeftTest(tmp1, tmp2, tmp3) == -1)
	{
		S_Stack.pop_back();
		tmp1 = S_Stack[S_Stack.size() - 2];
		tmp2 = S_Stack[S_Stack.size() - 1];
		tmp3 = S_Stack[0];
	}
	//对某种特殊情况的处理

	return S_Stack;
}

void TwoWayMergeStar(vector <Point> & resulttmp,Point center,vector <Point> & CH1, vector <Point> & CH2)
//两个星星多边形的归并
//两个逆时针顺序凸包二路归并
//最终结果储存在resulttmp中
{
	
	int index1 = 0;
	int index2 = 0;
	while (index1 < CH1.size() && index2 < CH2.size())
	{
		
		int test = ToLeftTest(center, CH1[index1], CH2[index2]);
		if (test == -1)
		{
			resulttmp.push_back(CH2[index2]);
			index2++;
		}
		else if (test == 1)
		{
			resulttmp.push_back(CH1[index1]);
			index1++;
		}
		else
		{
			if (CH1[index1] == CH2[index2])
			{
				resulttmp.push_back(CH1[index1]);
				//resulttmp.push_back(CH2[index2]);
				index1++;
				index2++;
			}
			else
			{
				double r = (CH1[index1] - center).dot(CH2[index2] - center);
				if (r >= 0)
				{
					resulttmp.push_back(CH1[index1]);
					resulttmp.push_back(CH2[index2]);
					index1++;
					index2++;
				}
				else
				{
					int result1 = ToLeftTest(center, resulttmp[resulttmp.size() - 1], CH1[index1]);
					if (result1 == 1)
					{
						resulttmp.push_back(CH1[index1]);
						index1++;
					}
					else if (result1 == 0)
					{
						double r1 = (CH1[index1] - center).dot(resulttmp[resulttmp.size() - 1] - center);
						if (r1 >= 0)
						{
							resulttmp.push_back(CH1[index1]);
							index1++;
						}
					}
					int result2 = ToLeftTest(center, resulttmp[resulttmp.size() - 1], CH2[index2]);
					if (result2 == 1)
					{
						resulttmp.push_back(CH2[index2]);
						index2++;
					}
					else if (result2 == 0)
					{
						double r2 = (CH2[index2] - center).dot(resulttmp[resulttmp.size() - 1] - center);
						if (r2 >= 0)
						{
							resulttmp.push_back(CH2[index2]);
							index2++;
						}
					}
				}
			}
		}
	}
	while (index1 < CH1.size())
	{
		resulttmp.push_back(CH1[index1]);
		index1++;
	}
	while (index2 < CH2.size())
	{
		resulttmp.push_back(CH2[index2]);
		index2++;
	}

}

void TwoWayMergeNew(vector <Point> & resulttmp, vector <Point> & CH1, vector <Point> & CH2)
//上边那个函数按照center去归并似乎是不行的，最后归并的点集并不是按照极角顺序
//按这个函数排序还是不行的，还是需要用上边的那个排！
{
	if (CH1.size() == 0 && CH2.size() != 0)
	{
		for (int i = 0;i<CH2.size();i++)
			resulttmp.push_back(CH2[i]);
		return;
	}
	else if (CH2.size() == 0 && CH1.size() != 0)
	{
		for (int i = 0; i<CH1.size(); i++)
			resulttmp.push_back(CH1[i]);
		return;
	}
	else if (CH1.size() == 0 && CH2.size() == 0)
	{
		return;
	}

	int ltlch1 = FindLowestThenLeftmost(CH1);
	int mov = CH1.size() - ltlch1;
	vector <Point> New = CH1;
	for (int i = 0; i < CH1.size(); i++)
	{
		int nmov;
		if (i + mov >= CH1.size())
			nmov = i + mov - CH1.size();
		New[nmov] = CH1[i];
	}
	CH1 = New;

	int ltlch2 = FindLowestThenLeftmost(CH2);
	mov = CH2.size() - ltlch2;
	New = CH2;
	for (int i = 0; i < CH2.size(); i++)
	{
		int nmov;
		if (i + mov >= CH2.size())
			nmov = i + mov - CH2.size();
		New[nmov] = CH2[i];
	}
	CH2 = New;

	vector <Point> LTL;
	LTL.push_back(CH1[0]);
	LTL.push_back(CH2[0]);
	int ltltmp = FindLowestThenLeftmost(LTL);
	Point ref;
	int index1 =0;
	int index2 =0;
	if (ltltmp == 0)
	{
		ref = CH1[0];
		index1++;
	}
	else if (ltltmp == 1)
	{
		ref = CH2[0];
		index2++;
	}

	resulttmp.push_back(ref);
	
	while (index1 < CH1.size() && index2 < CH2.size())
	{
		int test = ToLeftTest(ref, CH1[index1], CH2[index2]);
		if (test == -1)
		{
			resulttmp.push_back(CH2[index2]);
			index2++;
		}
		else if (test == 1)
		{
			resulttmp.push_back(CH1[index1]);
			index1++;
		}
		else
		{
			resulttmp.push_back(CH1[index1]);
			resulttmp.push_back(CH2[index2]);
			index1++;
			index2++;
		}
	}
	while (index1 < CH1.size())
	{
		resulttmp.push_back(CH1[index1]);
		index1++;
	}
	while (index2 < CH2.size())
	{
		resulttmp.push_back(CH2[index2]);
		index2++;
	}
}

void TwoWayMerge1dot5(vector <Point> & resulttmp, Point center, vector <Point> & CH1, vector <Point> & CH2)
//包含一个完整的星星多边形 和一个不完整的线段
//CH1是一个完整的多边形 CH2是切点切割后的局部线段
//默认CH2没有共线的三个点 也没有重复的点
{
	//ModifyFirEle(vector <Point> Points, int pos)
	int  i;

	//for (i = 0; i < CH2.size(); i++)
	//{
	//	if (CH2[i] == tangentpoint[0])
	//		break;
	//}
	//CH2 = ModifyFirEle(CH2, i);

	int test1;
	int test2;
	//int type = 0; //把线段分成两种类型，类似于手性分子
	//if (CH2.size() == 2)
	//	type = 1;
	//else
	//{
	//	if ((CH2[1] - CH2[0]).dot(CH2[2] - CH2[1]) > 0)
	//		type = 1;
	//	else
	//		type = 2;
	//}

	//int i;
	//if (type == 1)
	//{
	//}
	//else if (type == 2)
	//{
	//	CH2 = ModifyFirEle(CH2, 1);
	//}

	for (i = 0; i < CH1.size(); i++)
	{
		test1 = ToLeftTest(center, CH1[i], CH2[0]);
		if (test1 == 1 || test1 == 0)
			break;
	}
	CH1 = ModifyFirEle(CH1, i);

	int CH2i = 0;
	for (i = 0; i < CH1.size(); i++)//360度扫一遍把二者融合
	{
		int leftindex = i;
		int rightindex = i + 1;
		if (rightindex >= CH1.size())
			rightindex = 0;
		resulttmp.push_back(CH1[i]);
		test1 = ToLeftTest(center, CH1[leftindex], CH2[CH2i]);
		test2 = ToLeftTest(center, CH1[rightindex], CH2[CH2i]);
		int flag = 0;
		while ((test1 == 1 || test1 == 0) && (test2 == -1 || test2 == 0))
		{
			flag = 1;
			resulttmp.push_back(CH2[CH2i]);
			CH2i++;
			if (CH2i < CH2.size())
			{
				test1 = ToLeftTest(center, CH1[leftindex], CH2[CH2i]);
				test2 = ToLeftTest(center, CH1[rightindex], CH2[CH2i]);
			}
			else
			{
				flag = -1;
				break;
			}
		}
		if (flag == 1);
		else if (flag == -1)
			break;
	}
	i++;
	while (i < CH1.size())
	{
		resulttmp.push_back(CH1[i]);
		i++;
	}
	return;
}

vector <Point> DivideAndMergeCH(vector <Point> & Points, int Left, int Right)
{
	vector <Point> Result;
	if (Right - Left <= 2)
	{
		for (int i = Left; i <= Right; i++)
		{
			Result.push_back(Points[i]);
		}
		
		if (Result.size() == 3)
		{
			int flagthis = 0;
			if (ToLeftTest(Result[0], Result[1], Result[2]) == 0)//对共线情况进行处理
			{
				if (flagthis == 0)
				{
					int test = IfInLine(Result[0], Result[1], Result[2]);
					if (test == 1 || test == -2)
					{
						Result.erase(Result.begin() + 2);
						flagthis = 1;
					}
				}
				if (flagthis == 0)
				{
					int test = IfInLine(Result[0], Result[2], Result[1]);
					if (test == 1 || test == -2)
					{
						Result.erase(Result.begin() + 1);
						flagthis = 1;
					}
				}
				if (flagthis == 0)
				{
					int test = IfInLine(Result[1], Result[2], Result[0]);
					if (test == 1 || test == -2)
					{
						Result.erase(Result.begin());
						flagthis = 1;
					}
				}
			}
		}
		if (Result.size()==2)
		{
			if (Result[0] == Result[1])
			{
				Result.pop_back();
			}
		}
		Result = BubbleSortPointsCW(Result);//逆时针排序
		return Result;
	}
	int split1Left = Left;
	int split1Right = Left + ceil(double((Right - Left + 1) / 2.0)) - 1;
	int split2Left = split1Right + 1;
	int split2Right = Right;

	vector <Point> CH1, CH2;
	CH1 = DivideAndMergeCH(Points, split1Left, split1Right);
	CH2 = DivideAndMergeCH(Points, split2Left, split2Right);

	Point Start1 = CH1[0];
	Point Start2 = CH2[0];
	auto  i = CH1.begin()+1;
	while (i!=CH1.end())
	{
		if (*i == Start1)
			i = CH1.erase(i);
		else
		{
			Start1 = *i;
			i++;
		}
	}
	i = CH2.begin() + 1;
	while (i != CH2.end())
	{
		if (*i == Start2)
			i = CH2.erase(i);
		else
		{
			Start2 = *i;
			i++;
		}
	}//首先要去除重复点。由于是逆时针排好序的，所以线性复杂度即可去除完毕重复点

	//然后是二路归并
	Point center;
	int whichc = 0;
	if (CH1.size() == 1 && CH2.size() == 1)
	{
		Result.push_back(CH1[0]);
		Result.push_back(CH2[0]);
		return Result;
	}
	else if (CH1.size() == 1 && CH2.size() != 1)
	{
		if (CH2.size() == 2)
			center = (CH2[0] + CH2[1]).multiple(double(1.0 / 2.0));
		else
			center = (CH2[0] + CH2[ceil(double((CH2.size() - 1) / 2.0))] + CH2[CH2.size() - 1]).multiple(double(1.0 / 3.0));
		whichc = 2;
		if (center == CH1[0])
			return CH2;
	}
	else if (CH1.size() != 1 && CH2.size() == 1)
	{
		if (CH1.size() == 2)
			center = (CH1[0] + CH1[1]).multiple(double(1.0 / 2.0));
		else
			center = (CH1[0] + CH1[ceil(double((CH1.size() - 1) / 2.0))] + CH1[CH1.size() - 1]).multiple(double(1.0 / 3.0));
		whichc = 3;
		if (center == CH2[0])
			return CH1;
	}
	else
	{
		if (CH1.size() == 2)
			center = (CH1[0] + CH1[1]).multiple(double(1.0 / 2.0));
		else
			center = (CH1[0] + CH1[ceil(double((CH1.size() - 1) / 2.0))] + CH1[CH1.size() - 1]).multiple(double(1.0 / 3.0));
		whichc = 4;
	}//把特殊和非特殊情况分出来

	
	vector <Point> resulttmp;
	if (((whichc == 4) && (InConvexPolygonTest(CH2, center) != -1)) || whichc == 2 || whichc == 3)
	{
		TwoWayMergeStar(resulttmp, center ,CH1, CH2);
	}
	else //if ((whichc == 4) && (InConvexPolygonTest(CH2, center) == -1))
	{
		if (CH2.size() <= 2)
		{

			TwoWayMerge1dot5(resulttmp, center, CH1, CH2);

			//resulttmp.push_back(center);
			//for (int i = 0; i < CH2.size(); i++)
			//{
			//	resulttmp.push_back(CH2[i]);
			//}
			//resulttmp = BubbleSortPointsCW(resulttmp);//逆时针排序
		}
		else
		{
			vector <int> TangentpIndex;
			for (int i = 0; i < CH2.size(); i++)
			{
				Point Leftp;
				Point Rightp;
				if (i == 0)
				{
					Leftp = CH2[CH2.size() - 1];
					Rightp = CH2[i + 1];
				}
				else if (i == CH2.size() - 1)
				{
					Leftp = CH2[i - 1];
					Rightp = CH2[0];
				}
				else
				{
					Leftp = CH2[i - 1];
					Rightp = CH2[i + 1];
				}
				int test1 = ToLeftTest(center, CH2[i], Leftp);
				int test2 = ToLeftTest(center, CH2[i], Rightp);
				if ((test1 == 1 && test2 == 1) || (test1 == -1 && test2 == -1))
					TangentpIndex.push_back(i);
				else if ((test1 == 0 && test2 == 1) || (test1 == 0 && test2 == -1))
					TangentpIndex.push_back(i);
				else if ((test2 == 0 && test1 == 1) || (test2 == 0 && test1 == -1))
					TangentpIndex.push_back(i);
			}

			if (TangentpIndex.size() > 2)//当切点有好几个时有如下处理措施
			{
				vector <int> ErasetangentIndex;
				vector <int> ErasePointIndex;
				for (int i = 0; i < TangentpIndex.size(); i++)
				{
					Point A = CH2[TangentpIndex[i]];
					for (int j = 0; j < TangentpIndex.size(); j++)
					{
						if (j != i)
						{
							Point B = CH2[TangentpIndex[j]];
							int flag = 0;
							for (int k = 0; k < ErasePointIndex.size(); k++)
							{
								if (TangentpIndex[i] == ErasePointIndex[k])
								{
									flag = 1;
									break;
								}
								if (TangentpIndex[j] == ErasePointIndex[k])
								{
									flag = 2;
									break;
								}
							}
							if (flag == 1)
								break;
							if (flag == 2)
								continue;
							int testthis = ToLeftTest(center, A, B);
							if (testthis == 0)
							{
								if (normPoints(center, A) <= normPoints(center, B))
								{
									ErasetangentIndex.push_back(i);
									ErasePointIndex.push_back(TangentpIndex[i]);
								}
								else
								{
									ErasetangentIndex.push_back(j);
									ErasePointIndex.push_back(TangentpIndex[j]);
								}
							}
						}
					}
				}
				TangentpIndex = EraseVectorint(TangentpIndex, ErasetangentIndex);
				CH2 = EraseVectorPoints(CH2, ErasePointIndex);
				cout << "大于2" << endl;
			}
			for (int i = 0;i<TangentpIndex.size();i++)
			{
				//cout << TangentpIndex[i] << " ";
			}
			cout << TangentpIndex.size()<<endl;
			if (TangentpIndex.size() == 0)
			{
				cout << "s1";
			}
			
			vector <Point> TangentPoint;
			TangentPoint.push_back(CH2[TangentpIndex[0]]);
			TangentPoint.push_back(CH2[TangentpIndex[1]]);
			vector <int> eraseindex;
			for (int i = 0; i < CH2.size(); i++)
			{
				if (i != TangentpIndex[0] && i != TangentpIndex[1])
				{
					if (CH2[i] == CH2[TangentpIndex[0]] || CH2[i] == CH2[TangentpIndex[1]])
						eraseindex.push_back(i);
				}
			}
			CH2 = EraseVectorPoints(CH2, eraseindex);//去除CH2中与切点重复的点
			
			if (eraseindex.size() != 0)
			{
				int tangsum = 0;
				TangentpIndex.clear();
				for (int i = 0; i < CH2.size(); i++)
				{
					if (CH2[i] == TangentPoint[tangsum])
					{
						TangentpIndex.push_back(i);
						tangsum++;
						if (tangsum >= 2)
							break;
					}
				}//更新TangentpIndex
			}
			CH2 = ModifyFirEle(CH2, TangentpIndex[1]);
			eraseindex.clear();
			for (int i = TangentpIndex[1] + 1; i < CH2.size(); i++)
			{
				eraseindex.push_back(i);
			}
			CH2 = EraseVectorPoints(CH2, eraseindex);

			/*int innerindex = -1;
			int outerindex = -1;
			int leftindex;
			leftindex = TangentpIndex[0] - 1;
			if (leftindex < 0)
				leftindex = CH2.size() - 1;
			if (TangentpIndex[1] - TangentpIndex[0] == 1 )
			{
				innerindex = -1;
				if (CH2.size() == 2)
					outerindex = -1;
				else
					outerindex = leftindex;
			}
			else
			{
				innerindex = TangentpIndex[0] + 1;
				if (leftindex == TangentpIndex[1])
					outerindex = -1;
				else
					outerindex = leftindex;
			}
			
			vector <Point> NewCH2;
			eraseindex.clear();
			if (innerindex == -1 && outerindex == -1)
			{
				NewCH2 = CH2;
			}
			else if (innerindex == -1 && outerindex != -1)
			{
				int testtri = InTriangle(center, CH2[TangentpIndex[0]], CH2[TangentpIndex[1]], CH2[outerindex]);
				if (testtri == 1 || testtri == 0)
				{
					NewCH2.push_back(CH2[TangentpIndex[0]]);
					NewCH2.push_back(CH2[TangentpIndex[1]]);
				}
				else
					NewCH2 = CH2;
			}
			else if (innerindex != -1 && outerindex == -1)
			{
				int testtri = InTriangle(center, CH2[TangentpIndex[0]], CH2[TangentpIndex[1]], CH2[innerindex]);
				if (testtri == 1 || testtri == 0)
				{
					NewCH2.push_back(CH2[TangentpIndex[0]]);
					NewCH2.push_back(CH2[TangentpIndex[1]]);
				}
				else
					NewCH2 = CH2;
			}
			else if (innerindex != -1 && outerindex != -1)
			{
				int testtri = InTriangle(center, CH2[TangentpIndex[0]], CH2[TangentpIndex[1]], CH2[outerindex]);
				if (testtri == 1 || testtri == 0)
					for (int i = TangentpIndex[0]; i <= TangentpIndex[1]; i++)
						NewCH2.push_back(CH2[i]);
				else
				{
					for (int i = TangentpIndex[0] + 1; i < TangentpIndex[1]; i++)
						eraseindex.push_back(i);
					NewCH2 = EraseVectorPoints(CH2, eraseindex);
				}
			}
			CH2 = NewCH2;*/
			
			TwoWayMerge1dot5(resulttmp, center,CH1, CH2);
			
		}
		//TwoWayMerge1dot5(resulttmp, center, CH1, CH2);
	}
	return GetCHGrahamScanWithoutSort(resulttmp);
}

vector <Point> DivideAndMergeCHNew(vector <Point> & Points, int Left, int Right)
//上边那个是待重新理解的东西。这个就是单纯的改了融合的算法
{
	vector <Point> Result;
	if (Right - Left <= 2)
	{
		for (int i = Left; i <= Right; i++)
		{
			Result.push_back(Points[i]);
		}

		if (Result.size() == 3)
		{
			int flagthis = 0;
			if (ToLeftTest(Result[0], Result[1], Result[2]) == 0)//对共线情况进行处理
			{
				if (flagthis == 0)
				{
					int test = IfInLine(Result[0], Result[1], Result[2]);
					if (test == 1 || test == -2)
					{
						Result.erase(Result.begin() + 2);
						flagthis = 1;
					}
				}
				if (flagthis == 0)
				{
					int test = IfInLine(Result[0], Result[2], Result[1]);
					if (test == 1 || test == -2)
					{
						Result.erase(Result.begin() + 1);
						flagthis = 1;
					}
				}
				if (flagthis == 0)
				{
					int test = IfInLine(Result[1], Result[2], Result[0]);
					if (test == 1 || test == -2)
					{
						Result.erase(Result.begin());
						flagthis = 1;
					}
				}
			}
		}
		if (Result.size() == 2)
		{
			if (Result[0] == Result[1])
			{
				Result.pop_back();
			}
		}
		Result = BubbleSortPointsCW(Result);//逆时针排序
		return Result;
	}
	int split1Left = Left;
	int split1Right = Left + ceil(double((Right - Left + 1) / 2.0)) - 1;
	int split2Left = split1Right + 1;
	int split2Right = Right;

	vector <Point> CH1, CH2;
	CH1 = DivideAndMergeCHNew(Points, split1Left, split1Right);
	CH2 = DivideAndMergeCHNew(Points, split2Left, split2Right);

	for (int i = 0; i < CH2.size(); i++)
	{
		CH1.push_back(CH2[i]);
	}
	CH1 = GetCHGrahamScan(CH1);
	return CH1;
}
vector <Point> GetCHDivideMerge(vector <Point> Points)
//通过分治融合得到凸包。
{
	//return DivideAndMergeCH(Points, 0, Points.size() - 1);//这个还需要有时间有机会重新思考
	return DivideAndMergeCHNew(Points, 0, Points.size() - 1);//暂时先用这个简化版的能大体看出思路的方法来做
}