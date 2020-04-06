#ifndef VISUALIZATION
#define VISUALIZATION
#include "ConvexHull.h"
#include <algorithm>
#include <GL/glut.h>
#include <math.h>
#include <vector>

//模拟Buffer
extern vector<double> GLplotPointsXData;
extern vector<double> GLplotPointsYData;
extern vector<double> GLplotPointsZData;
extern vector<float> GLplotPointsize;//对应的点的大小
void OpenGLplot(void);
void CloseGLplot();
void AddBufferPoints(vector<Point> Points, float sizepoint);

#endif