#ifndef GEOMETRYINTERSECTION
#define GEOMETRYINTERSECTION

#include <iostream>
#include <math.h>
#include <stdlib.h>
#include <stdio.h>
#include <vector>
#include <ctime>
#include <algorithm>
#include "ConvexHull.h"
using namespace std;

vector <int> SegmentsID;//存放所有分配的Segment的ID
class Segment
{
public:
	int ID;
	Point L;
	Point R;

	int DistributeUniqueID()//分配一独有的ID
	{
		if (SegmentsID.empty() == 1)
		{
			SegmentsID.push_back(0);
			return 0;
		}
		else
		{
			SegmentsID.push_back(SegmentsID.size());
			return SegmentsID.size();
		}
	}

	Segment(Point A,Point B)
	{
		Segment::L = A;
		Segment::R = B; 
		Segment::ID = Segment::DistributeUniqueID();
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
};


#endif 