#ifndef HEAP_H
#define HEAP_H

#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <vector>
#include <math.h>
#include "CustomizeDataType.h"
using namespace std;

class HeapData:public Point
{
public:
	int SegmentID; //ָ���������߶α��
	int LorR; //ָ�����߶ε���˻����Ҷˣ����ڴ�ֱ�ں�����߶Σ���Ϊ����Ϊ��
	HeapData()
	{
		this->Point_X = 0;
		this->Point_Y = 0;
		this->Point_Z = 0;
		this->SegmentID = -1;
		this->LorR = 0;
	}
	HeapData(Point tmp,int Segmentid,int LorR)
	{
		this->Point_X = tmp.Point_X;
		this->Point_Y = tmp.Point_Y;
		this->Point_Z = tmp.Point_Z;
		this->SegmentID = Segmentid;
		this->LorR = LorR;
	}
	int operator < (HeapData P2)
	{
		if (this->Point_X < P2.Point_X)
			return 1;
		else
			return 0;
	}
	int operator <= (HeapData P2)
	{
		if (this->Point_X <= P2.Point_X)
			return 1;
		else
			return 0;
	}
	int operator >= (HeapData P2)
	{
		if (this->Point_X >= P2.Point_X)
			return 1;
		else
			return 0;
	}
	int operator > (HeapData P2)
	{
		if (this->Point_X > P2.Point_X)
			return 1;
		else
			return 0;
	}
	int operator == (HeapData P2)
	{
		if (this->Point_X == P2.Point_X)
			return 1;
		else
			return 0;
	}
	int operator != (HeapData P2)
	{
		if (this->Point_X != P2.Point_X)
			return 1;
		else
			return 0;
	}

}; //�����ǳ����Ԫ�أ�����Ҫ����Ƚ���


typedef HeapData ElemenType;
//#define ElemenTypical  NULL


class HeapOperate //��Ϊһ��������ִ����
{
public:
	int IsFullHeap(vector <ElemenType>  HeapData);
	int IsEmptyHeap(vector <ElemenType>  HeapData);
	HeapOperate(int MaxorMin, int MaxSize)
	{
		SetMaxorMin(MaxorMin);
		SetMaxsizeHeap(MaxSize);
	}
	void InsertHeapElement(vector <ElemenType> & HeapData, ElemenType Element);
	ElemenType DeleteHeapRoot(vector <ElemenType> & HeapData);
	void CreateHeap(vector <ElemenType> & RandomElement);//����Ϊ�������У������������õ���Ӧ�Ķ�����
	void Change2Heap(vector <ElemenType> & RandomElement, int root, int maxormin);//��rootΪ���ڵ㣬������Ӧ������ΪHeap,��Ȼ��������һ�������ϵ���

private:
	void SetMaxsizeHeap(int MaxSize);
	void SetMaxorMin(int MaxorMin);
	int MaxSize;
	int MaxorMin;//��־�����ѻ�����С��
				 //vector <ElemenType> HeapData;//ȡֵ��0��ʼ���������ڱ�

};




#endif
