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
	int SegmentID; //指明所述的线段编号
	int LorR; //指明是线段的左端还是右端，对于垂直于横轴的线段，下为左，上为右
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

}; //若不是常规的元素，则需要定义比较器


typedef HeapData ElemenType;
//#define ElemenTypical  NULL


class HeapOperate //作为一个操作的执行者
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
	void CreateHeap(vector <ElemenType> & RandomElement);//输入为任意序列，经过堆整理后得到对应的堆序列
	void Change2Heap(vector <ElemenType> & RandomElement, int root, int maxormin);//以root为根节点，调整对应的子树为Heap,当然必须是在一定基础上调整

private:
	void SetMaxsizeHeap(int MaxSize);
	void SetMaxorMin(int MaxorMin);
	int MaxSize;
	int MaxorMin;//标志是最大堆还是最小堆
				 //vector <ElemenType> HeapData;//取值从0开始，不设置哨兵

};




#endif
