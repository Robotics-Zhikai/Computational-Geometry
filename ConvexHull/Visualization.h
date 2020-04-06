#ifndef VISUALIZATION
#define VISUALIZATION
#include "ConvexHull.h"
#include <algorithm>
#include <GL/glut.h>
#include <math.h>
#include <vector>

//ģ��Buffer
extern vector<double> GLplotPointsXData;
extern vector<double> GLplotPointsYData;
extern vector<double> GLplotPointsZData;
extern vector<float> GLplotPointsize;//��Ӧ�ĵ�Ĵ�С
void OpenGLplot(void);
void CloseGLplot();
void AddBufferPoints(vector<Point> Points, float sizepoint);

#endif