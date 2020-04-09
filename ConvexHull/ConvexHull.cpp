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

vector<Point> DeleteRepeatPoints(vector<Point> Points) //ɾ���㼯���ظ��ĵ�
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
int CheckSorted(vector<Point> Points)
//�ж�Points�Ƿ�Sorted���� ������е㶼�ظ�����ôSorted�ж���Ϊ1 
//�������ĳ�ʼ����Щ�ظ����Գ�������ܲ�Ӱ�졣
//O(n)�ĸ��Ӷ�
{
	if (Points.size() < 3)
		return 1;
	vector <Point> Points1; //��ȥ�ظ�Points[0],ֻ����һ��Points[0]�ĵ㼯
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
//ð����������㼯 O(n^2) ��һ���Ǽ��㼯
//��Ȼ��һ���Ǽ��㼯������ֻ�м��㼯����������壬����ͨ�㼯����������û��ɶ������������
//ȥ����һ�����ظ������
{
	if (CheckSorted(Points) == 1) //˵���Ѿ��ź�����
		return Points;
	vector <Point> Points1; //��ȥ�ظ�Points[0],ֻ����һ��Points[0]�ĵ㼯
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
			else if (compareresult == -2) //�����������������ĳ�ʼ�����غ�,��һ��ʼ�Ĵ����Ѿ���֤�˲���������������
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
	vector<Point> EE;//����EE��
	Points.push_back(Points[0]);
	int i,j;
	for (i = 0; i < Points.size()-1; i++)
	{
		for (j = i + 1; j < Points.size(); j++)
		{
			if (Points[i] == Points[j]) //���ȥ����������г���
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
//�жϵ�A�Ƿ���Points���ɵ�͹�������
//Points������Ǽ��㼯����Ҫ���ظ�
//O(n)
//���ڲ�return1 �ڱ��� return0 ���ⲿ return-1 Error return-2 
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
		if (testresult[i] != 0 && testresult[i] != last)
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

double normPoints(Point A, Point B)
//����A B֮��ľ���
{
	return sqrt((A.Point_X - B.Point_X)*(A.Point_X - B.Point_X)+ \
		(A.Point_Y - B.Point_Y)*(A.Point_Y - B.Point_Y)+\
		(A.Point_Z - B.Point_Z)*(A.Point_Z - B.Point_Z));
}
vector <Point> GetCHIncrementalConstruction(vector <Point> Points)
//���������õ�͹�� ����δ��������
{
	//Points = DeleteRepeatPoints(Points);
	if (Points.size() <= 3)
		return Points;
	vector <Point> CHPoints;
	CHPoints.push_back(Points[0]);
	for (int i = 1; i < Points.size(); i++)
	{
		if (*Points.end() == Points[i])
			continue;
		//CHPoints = BubbleSortPoints(CHPoints); //�ƺ��������ò�������
		int Testresult = InConvexPolygonTest(CHPoints, Points[i]); //O(n)
		if (Testresult == 1 || Testresult == 0)
			continue;
		else if (Testresult == -2)
		{
			printf("���ִ���\n");
			return CHPoints;
		}
		int j;
		//����һ���Ļ��͸��������ܳ���CHPoints�����غϵ�����
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
			if (((L == 1 || L == 0) && (R == 1 || R == 0)) || ((L == -1 || L == 0) && (R == -1 || R == 0)))
				Tangent.push_back(j);
		}
		vector <int> eraseIndex;
		for (j = 0; j < Tangent.size(); j++)
		{
			int last, next;
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
		if (eraseIndex.empty() == 0)
		{
			int Index = Tangent[eraseIndex[0]];
			Tangent.erase(Tangent.begin() + eraseIndex[0]);//��ʱtangentӦ��ֻ�������Ŷ� erase֮ǰ������Ԫ��
			CHPoints.erase(CHPoints.begin() + Index);
		}
		int storeindex;
		for (j = 0; j < CHPoints.size()-1; j++)
		{
			if ((ComparePoint(CHPoints[0], Points[i], CHPoints[j]) == 1) && (ComparePoint(CHPoints[0], Points[i], CHPoints[j + 1]) == -1))
			{
				storeindex = j;
				break;
			}
		}
		CHPoints.insert(CHPoints.begin() + j + 1,Points[i]);
		CHPoints.push_back(Points[i]);
	}
}