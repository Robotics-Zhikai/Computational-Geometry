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

vector <int> SegmentsID;//������з����Segment��ID
class Segment
{
public:
	int ID;
	Point L;
	Point R;

	int DistributeUniqueID()//����һ���е�ID
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