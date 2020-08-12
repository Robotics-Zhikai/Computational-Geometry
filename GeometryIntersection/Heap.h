#ifndef HEAP_H
#define HEAP_H

#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <vector>
#include <math.h>
using namespace std;

typedef double ElemenType;
#define ElemenTypical  NULL


class HeapOperate
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
