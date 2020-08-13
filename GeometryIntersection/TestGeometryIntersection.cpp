#include "GeometryIntersection.h"
#include "Visualization.h"
#include <time.h>
#include <math.h>
#include "Heap.h"


void main()
{
	OpenGLplot();
	vector <Point> test;
	test = GenerateRandomPoint(100, -10, 10, -5, 5);
	vector <Segment> SegmentSet;
	for (int i = 0; i < test.size(); i=i+2)
	{
		Segment tmp(test[i], test[i + 1]);
		//AddBufferLinesArrows(tmp, 1);
		AddBufferSegment(tmp, 1);
		SegmentSet.push_back(tmp);
	}
	HeapOperate heapOperator(2, 2 * test.size() + pow(test.size(),2));

	vector <HeapData> PriorityQueue;
	for (int i = 0; i < SegmentSet.size(); i++)
	{
		PriorityQueue.push_back(HeapData(SegmentSet[i].GetLPoint(), SegmentSet[i].GetID(), 1));
		PriorityQueue.push_back(HeapData(SegmentSet[i].GetRPoint(), SegmentSet[i].GetID(), 2));
	}
	heapOperator.CreateHeap(PriorityQueue);


	CloseGLplot();
}

	
