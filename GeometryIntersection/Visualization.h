#ifndef VISUALIZATION
#define VISUALIZATION

#include <algorithm>
#include <GL/glut.h>
#include <stdio.h>
#include <math.h>
#include <vector>
#include "CustomizeDataType.h"

using namespace std;

#define PI 3.14159265

//模拟Buffer,存储绘制的点
//extern vector<double> GLplotPointsXData;
//extern vector<double> GLplotPointsYData;
//extern vector<double> GLplotPointsZData;
//extern vector<float> GLplotPointsize;//对应的点的大小

//模拟Buffer，存储绘制的直线
//extern vector<double> GLplotLineXData;
//extern vector<double> GLplotLineYData;
//extern vector<double> GLplotLineZData;
//extern vector<float> GLplotLineWidth;//对应的直线的宽度
//extern vector<int> GLplotLineType;//线的种类 

//模拟Buffer，存储带箭头的直线
//extern vector<double> GLplotLineArrowXData;
//extern vector<double> GLplotLineArrowYData;
//extern vector<double> GLplotLineArrowZData;
//extern vector<float> GLplotLineArrowWidth;//对应的直线的宽度
//extern vector<int> GLplotLineArrowType;//线的种类 

void OpenGLplot(void);
void CloseGLplot();

void AddBufferPoints(vector<Point> Points, float sizepoint);
void AddBufferSequenceLine(vector<Point> Points, float LineWidth);
void AddBufferLinesArrows(Segment seg, float LineWidth);
void AddBufferHollowSquare(vector<Point> Points, float SquareSize);
void AddBufferSegment(Segment seg, float LineWidth);

#endif