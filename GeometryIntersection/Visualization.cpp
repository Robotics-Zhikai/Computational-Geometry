#include "Visualization.h"

vector<Point> GLplotPointsData;
vector<float> GLplotPointsize;//对应的点的大小

vector<Point> GLplotSequenceLineData;//sequence的意思是画一系列直线，画路径时更方便了
vector<float> GLplotSequenceLineWidth;//对应的直线的宽度
vector<int> GLplotSequenceLineType;//线的种类 

vector<Point> GLplotLineArrowData;
vector<float> GLplotLineArrowWidth;//对应的带箭头线段的宽度
vector<int> GLplotLineArrowType;//线的种类 

vector <Point> GLplotHollowSquareData;
vector <float> GLplotHollowSquareSize;//对应的空心框的大小
vector <int> GLplotHollowSquareType;//线的种类

vector<Point> GLplotSegmentData; //必须是成对出现的 线段数据
vector<float> GLplotSegmentWidth;//对应的线段的宽度
vector<int> GLplotSegmentType;//线的种类 

int numplotLineType = 0;

vector <double> ScalePointsx(vector <double> PointsX)
//将所有待画的点按比例缩放
{
	double maxIndexX = *max_element(PointsX.begin(), PointsX.end());
	double minIndexX = *min_element(PointsX.begin(), PointsX.end());

	if (maxIndexX - minIndexX < 0.0000001)
		return PointsX;

	double scaleXmin = -0.9;
	double scaleXmax = 0.9;
	double scaleYmin = -0.9;
	double scaleYmax = 0.9;

	for (int i = 0; i < PointsX.size(); i++)
		PointsX[i] = scaleXmin + ((PointsX[i] - (minIndexX)) / ((maxIndexX)-(minIndexX)))*(scaleXmax - scaleXmin);
	return PointsX;
}

vector <Point> ScalePoints(vector <Point> Points)
{
	vector <double> PointsX;
	vector <double> PointsY;
	vector <double> PointsZ;
	for (int i = 0; i < Points.size(); i++)
	{
		PointsX.push_back(Points[i].Point_X);
		PointsY.push_back(Points[i].Point_Y);
		PointsZ.push_back(Points[i].Point_Z);
	}
	PointsX = ScalePointsx(PointsX);
	PointsY = ScalePointsx(PointsY);
	PointsZ = ScalePointsx(PointsZ);
	for (int i = 0; i < Points.size(); i++)
	{
		Points[i].Point_X = PointsX[i];
		Points[i].Point_Y = PointsY[i];
		Points[i].Point_Z = PointsZ[i];
	}
	return Points;
}

void MergePointsx(vector <double> & result, vector <double> addPointsX)
{
	for (int i = 0; i < addPointsX.size(); i++)
		result.push_back(addPointsX[i]);
}

void MergePoints(vector <Point> & result, vector <Point> addPoints)
{
	for (int i = 0; i < addPoints.size(); i++)
		result.push_back(addPoints[i]);
}

void OpenGLplot(void)
{
	int argc = 1;
	char ** argv = { 0 };
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGB | GLUT_SINGLE);
	glutInitWindowPosition(100, 0);
	glutInitWindowSize(800, 800);
	glutCreateWindow("OpenGL可视化显示");
	glClear(GL_COLOR_BUFFER_BIT);
}
void Display(void)
{

	//首先融合所有vector<double>的值，进行放缩
	vector <Point> AllPoints;
	MergePoints(AllPoints, GLplotPointsData);
	MergePoints(AllPoints, GLplotSequenceLineData);
	MergePoints(AllPoints, GLplotLineArrowData);
	MergePoints(AllPoints, GLplotHollowSquareData);
	MergePoints(AllPoints, GLplotSegmentData);
	//若要添加新的Buffer，在这里加,一定要注意顺序统一

	//

	AllPoints = ScalePoints(AllPoints);

	vector <int> Numplotdata;
	Numplotdata.push_back(GLplotPointsData.size());
	Numplotdata.push_back(GLplotSequenceLineData.size());
	Numplotdata.push_back(GLplotLineArrowData.size());
	Numplotdata.push_back(GLplotHollowSquareData.size());
	Numplotdata.push_back(GLplotSegmentData.size());
	//若要添加新的Buffer，在这里加

	//

	int sumthis = 0;
	vector <vector <Point> > tmpvector;
	for (int i = 0; i < Numplotdata.size(); i++)
	{
		vector <Point> tmp;
		for (int j = sumthis; j < sumthis + Numplotdata[i]; j++)
			tmp.push_back(AllPoints[j]);
		tmpvector.push_back(tmp);
		sumthis += Numplotdata[i];
	}

	GLplotPointsData = tmpvector[0];
	GLplotSequenceLineData = tmpvector[1];
	GLplotLineArrowData = tmpvector[2];
	GLplotHollowSquareData = tmpvector[3];
	GLplotSegmentData = tmpvector[4];
	//若要添加新的Buffer，在这里加

	//


	float Size;
	int Curenti = 0;
	if (GLplotPointsData.empty() == 0)
	{
		Size = GLplotPointsize[0];
		while (1)
		{
			glPointSize(Size);
			glBegin(GL_POINTS);
			int i;
			for (i = Curenti; i < GLplotPointsize.size(); i++)
			{
				if (Size != GLplotPointsize[i])
				{
					Size = GLplotPointsize[i];
					Curenti = i;
					break;
				}

				glVertex2d(GLplotPointsData[i].Point_X, GLplotPointsData[i].Point_Y);
			}
			glEnd();
			if (i >= GLplotPointsize.size())
				break;
		}
	}

	if (GLplotSequenceLineData.empty() == 0)
		//这个是画所有点首尾相接的直线
	{
		int linetype = GLplotSequenceLineType[0];
		Size = GLplotSequenceLineWidth[0];
		Curenti = 0;
		while (1)
		{
			glLineWidth(Size);
			glBegin(GL_LINES);
			int i;
			for (i = Curenti; i < GLplotSequenceLineWidth.size() - 1; i++)
			{
				if ((Size != GLplotSequenceLineWidth[i]) || (linetype != GLplotSequenceLineType[i]))
				{
					Size = GLplotSequenceLineWidth[i];
					linetype = GLplotSequenceLineType[i];
					Curenti = i;
					break;
				}
				glVertex2d(GLplotSequenceLineData[i].Point_X, GLplotSequenceLineData[i].Point_Y);
				glVertex2d(GLplotSequenceLineData[i + 1].Point_X, GLplotSequenceLineData[i + 1].Point_Y);
			}
			glEnd();
			if (i >= GLplotSequenceLineWidth.size() - 1)
				break;
		}
	}

	if (GLplotLineArrowData.empty() == 0)
		//必须得保证LineArrow里的数据是成对出现的 这样才好画箭头
	{

		int linetype = GLplotLineArrowType[0];

		for (int i = 0; i < GLplotLineArrowData.size(); i = i + 2)
		{
			Size = GLplotLineArrowWidth[i];
			glLineWidth(Size);
			glBegin(GL_LINES);
			glVertex2d(GLplotLineArrowData[i].Point_X, GLplotLineArrowData[i].Point_Y);
			glVertex2d(GLplotLineArrowData[i + 1].Point_X, GLplotLineArrowData[i + 1].Point_Y);
			glEnd();
			if (GLplotLineArrowData[i] != GLplotLineArrowData[i + 1])
			{
				Point Direction = GLplotLineArrowData[i] - GLplotLineArrowData[i + 1];
				Direction = Direction / Direction.norm();//归一化
				double rotdeg = PI / 8.7;
				Point RotateDirection45 = Point(cos(rotdeg)*Direction.Point_X - sin(rotdeg)*Direction.Point_Y, sin(rotdeg)*Direction.Point_X + cos(rotdeg)*Direction.Point_Y, Direction.Point_Z);
				rotdeg = -PI / 8.7;
				Point RotateDirectionMinus45 = Point(cos(rotdeg)*Direction.Point_X - sin(rotdeg)*Direction.Point_Y, sin(rotdeg)*Direction.Point_X + cos(rotdeg)*Direction.Point_Y, Direction.Point_Z);

				double ArrowLength = 0.022;//定义箭头长度为0.01

				Point InitPoint = GLplotLineArrowData[i] + ((GLplotLineArrowData[i + 1] - GLplotLineArrowData[i]).multiple(double(2.0 / 3.0))); //在线的靠近末端指一个箭头
				Point tmp = InitPoint + RotateDirection45.multiple(ArrowLength);
				glLineWidth(1.5*Size);
				glBegin(GL_LINES);
				glVertex2d(InitPoint.Point_X, InitPoint.Point_Y);
				glVertex2d(tmp.Point_X, tmp.Point_Y);
				glEnd();

				tmp = InitPoint + RotateDirectionMinus45.multiple(ArrowLength);
				glBegin(GL_LINES);
				glVertex2d(InitPoint.Point_X, InitPoint.Point_Y);
				glVertex2d(tmp.Point_X, tmp.Point_Y);
				glEnd();
			}
		}
	}

	if (GLplotSegmentData.empty() == 0)
	{
		int linetype = GLplotSegmentType[0];
		for (int i = 0; i < GLplotSegmentData.size(); i = i + 2)
		{
			Size = GLplotSegmentWidth[i];
			glLineWidth(Size);
			glBegin(GL_LINES);
			glVertex2d(GLplotSegmentData[i].Point_X, GLplotSegmentData[i].Point_Y);
			glVertex2d(GLplotSegmentData[i + 1].Point_X, GLplotSegmentData[i + 1].Point_Y);
			glEnd();
		}
	}

	if (GLplotHollowSquareData.empty() == 0)
	{
		for (int i = 0; i < GLplotHollowSquareData.size(); i++)
		{
			float size = GLplotHollowSquareSize[i];
			float linewidth = 1;
			glLineWidth(linewidth);
			glBegin(GL_LINES);
			glVertex2d(GLplotHollowSquareData[i].Point_X - size / 2.0, GLplotHollowSquareData[i].Point_Y - size / 2.0);
			glVertex2d(GLplotHollowSquareData[i].Point_X + size / 2.0, GLplotHollowSquareData[i].Point_Y - size / 2.0);
			glEnd();

			//glLineWidth(linewidth);
			glBegin(GL_LINES);
			glVertex2d(GLplotHollowSquareData[i].Point_X - size / 2.0, GLplotHollowSquareData[i].Point_Y - size / 2.0);
			glVertex2d(GLplotHollowSquareData[i].Point_X - size / 2.0, GLplotHollowSquareData[i].Point_Y + size / 2.0);
			glEnd();

			//glLineWidth(linewidth);
			glBegin(GL_LINES);
			glVertex2d(GLplotHollowSquareData[i].Point_X + size / 2.0, GLplotHollowSquareData[i].Point_Y - size / 2.0);
			glVertex2d(GLplotHollowSquareData[i].Point_X + size / 2.0, GLplotHollowSquareData[i].Point_Y + size / 2.0);
			glEnd();

			//glLineWidth(linewidth);
			glBegin(GL_LINES);
			glVertex2d(GLplotHollowSquareData[i].Point_X - size / 2.0, GLplotHollowSquareData[i].Point_Y + size / 2.0);
			glVertex2d(GLplotHollowSquareData[i].Point_X + size / 2.0, GLplotHollowSquareData[i].Point_Y + size / 2.0);
			glEnd();
		}
	}

	
	glFlush();

	//GLfloat x;
	//GLfloat factor = 0.1f;


	/*glLineWidth(5.0f);*/
	//glBegin(GL_LINES);
	//glVertex2f(-1.0f, 0.0f);
	//glVertex2f(1.0f, 0.0f);         // 以上两个点可以画x轴
	//glVertex2f(0.0f, -1.0f);
	//glVertex2f(0.0f, 1.0f);         // 以上两个点可以画y轴
	//glEnd();

	//glBegin(GL_LINE_STRIP);
	//for (x = -1.0f / factor; x<1.0f / factor; x += 0.01f)
	//{
	//	glVertex2f(x*factor, sin(x)*factor);
	//}
	//glEnd();

}
void CloseGLplot()//不算是严格意义上的关闭GL，只是必须对称的调用Open Close GLplot
{
	glutDisplayFunc(&Display);
	glutMainLoop();
}

//void AddBufferPoints(vector<Point> Points, float sizepoint)
//{
//	vector <double> PointsX;
//	vector <double> PointsY;
//	vector <double> PointsZ;
//	for (int i = 0; i < Points.size(); i++)
//	{
//		PointsX.push_back(Points[i].Point_X);
//		PointsY.push_back(Points[i].Point_Y);
//		PointsZ.push_back(Points[i].Point_Z);
//	}
//
//	double maxIndexX = *max_element(PointsX.begin(), PointsX.end());
//	double minIndexX = *min_element(PointsX.begin(), PointsX.end());
//	double maxIndexY = *max_element(PointsY.begin(), PointsY.end());
//	double minIndexY = *min_element(PointsY.begin(), PointsY.end());
//
//	double scaleXmin = -0.9;
//	double scaleXmax = 0.9;
//	double scaleYmin = -0.9;
//	double scaleYmax = 0.9;
//
//	for (int i = 0; i < PointsX.size(); i++)
//	{
//		PointsX[i] = scaleXmin + ((PointsX[i] - (minIndexX)) / ((maxIndexX)-(minIndexX)))*(scaleXmax - scaleXmin);
//		PointsY[i] = scaleYmin + ((PointsY[i] - (minIndexY)) / ((maxIndexY)-(minIndexY)))*(scaleYmax - scaleYmin);
//		PointsZ[i] = 0;
//	}
//
//	for (int i = 0; i < PointsX.size(); i++)
//	{
//		GLplotPointsXData.push_back(PointsX[i]);
//		GLplotPointsYData.push_back(PointsY[i]);
//		GLplotPointsZData.push_back(PointsZ[i]);
//		GLplotPointsize.push_back(sizepoint);
//	}
//}

void AddBufferPoints(vector<Point> Points, float sizepoint)
{
	for (int i = 0; i < Points.size(); i++)
		GLplotPointsData.push_back(Points[i]);

	//numplotLineType = 0;
	numplotLineType = numplotLineType + 1;
	for (int i = 0; i < Points.size(); i++)
		GLplotPointsize.push_back(sizepoint);
}

//void AddBufferLines(vector<Point> Points, float LineWidth)
//{
//	vector <double> PointsX;
//	vector <double> PointsY;
//	vector <double> PointsZ;
//	for (int i = 0; i < Points.size(); i++)
//	{
//		PointsX.push_back(Points[i].Point_X);
//		PointsY.push_back(Points[i].Point_Y);
//		PointsZ.push_back(Points[i].Point_Z);
//	}
//
//	double maxIndexX = *max_element(PointsX.begin(), PointsX.end());
//	double minIndexX = *min_element(PointsX.begin(), PointsX.end());
//	double maxIndexY = *max_element(PointsY.begin(), PointsY.end());
//	double minIndexY = *min_element(PointsY.begin(), PointsY.end());
//
//	double scaleXmin = -0.9;
//	double scaleXmax = 0.9;
//	double scaleYmin = -0.9;
//	double scaleYmax = 0.9;
//
//	for (int i = 0; i < PointsX.size(); i++)
//	{
//		PointsX[i] = scaleXmin + ((PointsX[i] - (minIndexX)) / ((maxIndexX)-(minIndexX)))*(scaleXmax - scaleXmin);
//		PointsY[i] = scaleYmin + ((PointsY[i] - (minIndexY)) / ((maxIndexY)-(minIndexY)))*(scaleYmax - scaleYmin);
//		PointsZ[i] = 0;
//	}
//	numplotLineType = numplotLineType + 1;
//	for (int i = 0; i < PointsX.size(); i++)
//	{
//		GLplotLineXData.push_back(PointsX[i]);
//		GLplotLineYData.push_back(PointsY[i]);
//		GLplotLineZData.push_back(PointsZ[i]);
//		GLplotLineWidth.push_back(LineWidth);
//		GLplotLineType.push_back(numplotLineType);
//	}
//	//GLplotLineXData.push_back(PointsX[0]);
//	//GLplotLineYData.push_back(PointsY[0]);
//	//GLplotLineZData.push_back(PointsZ[0]);
//	//GLplotLineWidth.push_back(LineWidth);
//	//GLplotLineType.push_back(numplotLineType);
//}


void AddBufferSequenceLine(vector<Point> Points, float LineWidth)
{
	for (int i = 0; i < Points.size(); i++)
		GLplotSequenceLineData.push_back(Points[i]);

	numplotLineType = 0;
	numplotLineType = numplotLineType + 1;
	for (int i = 0; i < Points.size(); i++)
	{
		GLplotSequenceLineWidth.push_back(LineWidth);
		GLplotSequenceLineType.push_back(numplotLineType);
	}
}

void AddBufferLinesArrows(Segment seg, float LineWidth)
{
	vector<Point> Points;
	Points.push_back(seg.GetLPoint());
	Points.push_back(seg.GetRPoint());

	for (int i = 0; i < Points.size(); i++)
		GLplotLineArrowData.push_back(Points[i]);

	numplotLineType = 0;
	numplotLineType = numplotLineType + 1;
	for (int i = 0; i < Points.size(); i++)
	{
		GLplotLineArrowWidth.push_back(LineWidth);
		GLplotLineArrowType.push_back(numplotLineType);
	}
}

void AddBufferHollowSquare(vector<Point> Points, float SquareSize)
{
	for (int i = 0; i < Points.size(); i++)
	{
		GLplotHollowSquareData.push_back(Points[i]);
		GLplotHollowSquareSize.push_back(SquareSize);
		GLplotHollowSquareType.push_back(1);
	}
}

void AddBufferSegment(Segment seg, float LineWidth)
{
	vector<Point> Points;
	Points.push_back(seg.GetLPoint());
	Points.push_back(seg.GetRPoint());

	for (int i = 0; i < Points.size(); i++)
	{
		GLplotSegmentData.push_back(Points[i]);
	}

	numplotLineType = 0;
	numplotLineType = numplotLineType + 1;
	for (int i = 0; i < Points.size(); i++)
	{
		GLplotSegmentWidth.push_back(LineWidth);
		GLplotSegmentType.push_back(numplotLineType);
	}
}