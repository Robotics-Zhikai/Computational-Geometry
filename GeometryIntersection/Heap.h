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
