#ifndef VISUALIZATION
#define VISUALIZATION
#include "ConvexHull.h"
#include <algorithm>
#include <GL/glut.h>
#include <math.h>
#include <vector>

//ģ��Buffer,�洢���Ƶĵ�
extern vector<double> GLplotPointsXData;
extern vector<double> GLplotPointsYData;
extern vector<double> GLplotPointsZData;
extern vector<float> GLplotPointsize;//��Ӧ�ĵ�Ĵ�С

//ģ��Buffer���洢���Ƶ�ֱ��
extern vector<double> GLplotLineXData;
extern vector<double> GLplotLineYData;
extern vector<double> GLplotLineZData;
extern vector<float> GLplotLineWidth;//��Ӧ��ֱ�ߵĿ��
extern vector<int> GLplotLineType;//�ߵ����� 

void OpenGLplot(void);
void CloseGLplot();

void AddBufferPoints(vector<Point> Points, float sizepoint);
void AddBufferLines(vector<Point> Points, float LineWidth);

#endif