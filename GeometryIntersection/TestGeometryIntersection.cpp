#include "GeometryIntersection.h"
#include "Visualization.h"
#include <time.h>
#include <math.h>

vector<Point> GenerateRandomPoint(int pointsNum, float RangeXmin, float RangeXmax, float RangeYmin, float RangeYmax)
//generate pointsNum random points in [RangeXmin,RangeXmax,RangeYmin,RangeYmax]
{
	vector<Point> Points;
	srand((int)time(0));  // 产生随机种子  把0换成NULL也行
	for (int i = 0; i < pointsNum; i++)
	{
		Point Pointtemp;
		float a = RangeXmin;
		float b = RangeXmax;
		Pointtemp.Point_X = a + (rand() / double(RAND_MAX))*(b - a);
		a = RangeYmin;
		b = RangeYmax;
		Pointtemp.Point_Y = a + (rand() / double(RAND_MAX))*(b - a);
		Pointtemp.Point_Z = 0;
		Points.push_back(Pointtemp);
	}
	return Points;
}










void main()
{

}

	
