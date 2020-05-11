#ifndef VISUALIZATION
#define VISUALIZATION
#include "ConvexHull.h"
#include <algorithm>
#include <GL/glut.h>
#include <math.h>
#include <vector>

//模拟Buffer,存储绘制的点
extern vector<double> GLplotPointsXData;
extern vector<double> GLplotPointsYData;
extern vector<double> GLplotPointsZData;
extern vector<float> GLplotPointsize;//对应的点的大小

//模拟Buffer，存储绘制的直线
extern vector<double> GLplotLineXData;
extern vector<double> GLplotLineYData;
extern vector<double> GLplotLineZData;
extern vector<float> GLplotLineWidth;//对应的直线的宽度
extern vector<int> GLplotLineType;//线的种类 

void OpenGLplot(void);
void CloseGLplot();

void AddBufferPoints(vector<Point> Points, float sizepoint);
void AddBufferLines(vector<Point> Points, float LineWidth);

#endif