#include "GeometryIntersection.h"
#include "Visualization.h"
#include <time.h>
#include <math.h>


void main()
{
	OpenGLplot();
	vector <Point> test;
	test = GenerateRandomPoint(100, -10, 10, -5, 5);
	for (int i = 0; i < test.size(); i=i+2)
	{
		Segment tmp(test[i], test[i + 1]);
		//AddBufferLinesArrows(tmp, 1);
		AddBufferSegment(tmp, 1);
	}
	CloseGLplot();
}

	
