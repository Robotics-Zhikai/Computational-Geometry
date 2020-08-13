#ifndef CUSTOMIZEDATATYPE_H
#define CUSTOMIZEDATATYPE_H
//定制化数据

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

	Segment(Point A, Point B)
	{
		if (A.Point_X > B.Point_X)
		{
			Segment::L = B;
			Segment::R = A;
		}
		else if (A.Point_X == B.Point_X)
		{
			if (A.Point_Y <= B.Point_Y)
			{
				Segment::L = A;
				Segment::R = B;
			}
			else
			{
				Segment::L = B;
				Segment::R = A;
			}
		}
		else
		{
			Segment::L = A;
			Segment::R = B;
		}
		Segment::ID = DistributeUniqueID();
	}

	Segment()
	{
		Point A;
		Segment::L = A;
		Segment::R = A;
		Segment::ID = -1; //若不初始化的话就给一个默认值
	}

	Segment operator = (Segment tmp)//把一个segment赋值给另一个segment,ID任旧是保持unique的
	{
		this->L = tmp.L;
		this->R = tmp.R;
	}

	int operator == (Segment tmp)//全等
	{
		if (this->L == tmp.L && this->R == tmp.R)
			return 1;
		else
			return 0;
	}

	int operator != (Segment tmp) //不全等
	{
		if ((this->operator==(tmp)) == 0)
			return 1;
		else
			return 0;
	}

	int GetID()
	{
		return this->ID;
	}

	Point GetLPoint()
	{
		return this->L;
	}

	Point GetRPoint()
	{
		return this->R;
	}
private:
	int ID;
	Point L;
	Point R;
};



#endif