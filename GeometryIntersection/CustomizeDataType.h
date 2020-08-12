#ifndef CUSTOMIZEDATATYPE_H
#define CUSTOMIZEDATATYPE_H
//���ƻ�����

#include <math.h>
#include <vector>
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
	Point operator + (Point P2)
	{
		Point result;
		result.Point_X = this->Point_X + P2.Point_X;
		result.Point_Y = this->Point_Y + P2.Point_Y;
		result.Point_Z = this->Point_Z + P2.Point_Z;
		return result;
	}
	Point operator - (Point P2)
	{
		Point result;
		result.Point_X = this->Point_X - P2.Point_X;
		result.Point_Y = this->Point_Y - P2.Point_Y;
		result.Point_Z = this->Point_Z - P2.Point_Z;
		return result;
	}
	Point operator / (double num)
	{
		if (num == 0)
			return (*this);
		Point result;
		result.Point_X = this->Point_X / num;
		result.Point_Y = this->Point_Y / num;
		result.Point_Z = this->Point_Z / num;
		return result;
	}
	Point multiple(double num)
	{
		Point result;
		result.Point_X = num * this->Point_X;
		result.Point_Y = num * this->Point_Y;
		result.Point_Z = num * this->Point_Z;
		return result;
	}
	double dot(Point P2)
	{
		double result;
		result = this->Point_X * P2.Point_X + this->Point_Y * P2.Point_Y + this->Point_Z * P2.Point_Z;
		return result;
	}
	double norm()
	{
		return sqrt(pow(this->Point_X, 2) + pow(this->Point_Y, 2) + pow(this->Point_Z, 2));
	}
};

int DistributeUniqueID();

class Segment
{
public:
	int ID;
	Point L;
	Point R;

	vector <int> SegmentsID;//������з����Segment��ID

	Segment(Point A, Point B)
	{
		Segment::L = A;
		Segment::R = B;
		Segment::ID = DistributeUniqueID();
	}

	Segment()
	{
		Point A;
		Segment::L = A;
		Segment::R = A;
		Segment::ID = -1; //������ʼ���Ļ��͸�һ��Ĭ��ֵ
	}

	Segment operator = (Segment tmp)//��һ��segment��ֵ����һ��segment,ID�ξ��Ǳ���unique��
	{
		this->L = tmp.L;
		this->R = tmp.R;
	}

	int operator == (Segment tmp)//ȫ��
	{
		if (this->L == tmp.L && this->R == tmp.R)
			return 1;
		else
			return 0;
	}

	int operator != (Segment tmp) //��ȫ��
	{
		if ((this->operator==(tmp)) == 0)
			return 1;
		else
			return 0;
	}
};



#endif