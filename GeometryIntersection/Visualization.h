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

//ģ��Buffer,�洢���Ƶĵ�
//extern vector<double> GLplotPointsXData;
//extern vector<double> GLplotPointsYData;
//extern vector<double> GLplotPointsZData;
//extern vector<float> GLplotPointsize;//��Ӧ�ĵ�Ĵ�С

//ģ��Buffer���洢���Ƶ�ֱ��
//extern vector<double> GLplotLineXData;
//extern vector<double> GLplotLineYData;
//extern vector<double> GLplotLineZData;
//extern vector<float> GLplotLineWidth;//��Ӧ��ֱ�ߵĿ��
//extern vector<int> GLplotLineType;//�ߵ����� 

//ģ��Buffer���洢����ͷ��ֱ��
//extern vector<double> GLplotLineArrowXData;
//extern vector<double> GLplotLineArrowYData;
//extern vector<double> GLplotLineArrowZData;
//extern vector<float> GLplotLineArrowWidth;//��Ӧ��ֱ�ߵĿ��
//extern vector<int> GLplotLineArrowType;//�ߵ����� 

void OpenGLplot(void);
void CloseGLplot();

void AddBufferPoints(vector<Point> Points, float sizepoint);
void AddBufferSequenceLine(vector<Point> Points, float LineWidth);
void AddBufferLinesArrows(Segment seg, float LineWidth);
void AddBufferHollowSquare(vector<Point> Points, float SquareSize);
void AddBufferSegment(Segment seg, float LineWidth);

#endif