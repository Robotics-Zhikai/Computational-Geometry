#include "Visualization.h"

vector<Point> GLplotPointsData;
vector<float> GLplotPointsize;//��Ӧ�ĵ�Ĵ�С

vector<Point> GLplotSequenceLineData;//sequence����˼�ǻ�һϵ��ֱ�ߣ���·��ʱ��������
vector<float> GLplotSequenceLineWidth;//��Ӧ��ֱ�ߵĿ��
vector<int> GLplotSequenceLineType;//�ߵ����� 

vector<Point> GLplotLineArrowData;
vector<float> GLplotLineArrowWidth;//��Ӧ�Ĵ���ͷ�߶εĿ��
vector<int> GLplotLineArrowType;//�ߵ����� 

vector <Point> GLplotHollowSquareData;
vector <float> GLplotHollowSquareSize;//��Ӧ�Ŀ��Ŀ�Ĵ�С
vector <int> GLplotHollowSquareType;//�ߵ�����

vector<Point> GLplotSegmentData; //�����ǳɶԳ��ֵ� �߶�����
vector<float> GLplotSegmentWidth;//��Ӧ���߶εĿ��
vector<int> GLplotSegmentType;//�ߵ����� 

int numplotLineType = 0;

vector <double> ScalePointsx(vector <double> PointsX)
//�����д����ĵ㰴��������
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
	glutCreateWindow("OpenGL���ӻ���ʾ");
	glClear(GL_COLOR_BUFFER_BIT);
}
void Display(void)
{

	//�����ں�����vector<double>��ֵ�����з���
	vector <Point> AllPoints;
	MergePoints(AllPoints, GLplotPointsData);
	MergePoints(AllPoints, GLplotSequenceLineData);
	MergePoints(AllPoints, GLplotLineArrowData);
	MergePoints(AllPoints, GLplotHollowSquareData);
	MergePoints(AllPoints, GLplotSegmentData);
	//��Ҫ����µ�Buffer���������,һ��Ҫע��˳��ͳһ

	//

	AllPoints = ScalePoints(AllPoints);

	vector <int> Numplotdata;
	Numplotdata.push_back(GLplotPointsData.size());
	Numplotdata.push_back(GLplotSequenceLineData.size());
	Numplotdata.push_back(GLplotLineArrowData.size());
	Numplotdata.push_back(GLplotHollowSquareData.size());
	Numplotdata.push_back(GLplotSegmentData.size());
	//��Ҫ����µ�Buffer���������

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
	//��Ҫ����µ�Buffer���������

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
		//����ǻ����е���β��ӵ�ֱ��
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
		//����ñ�֤LineArrow��������ǳɶԳ��ֵ� �����źû���ͷ
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
				Direction = Direction / Direction.norm();//��һ��
				double rotdeg = PI / 8.7;
				Point RotateDirection45 = Point(cos(rotdeg)*Direction.Point_X - sin(rotdeg)*Direction.Point_Y, sin(rotdeg)*Direction.Point_X + cos(rotdeg)*Direction.Point_Y, Direction.Point_Z);
				rotdeg = -PI / 8.7;
				Point RotateDirectionMinus45 = Point(cos(rotdeg)*Direction.Point_X - sin(rotdeg)*Direction.Point_Y, sin(rotdeg)*Direction.Point_X + cos(rotdeg)*Direction.Point_Y, Direction.Point_Z);

				double ArrowLength = 0.022;//�����ͷ����Ϊ0.01

				Point InitPoint = GLplotLineArrowData[i] + ((GLplotLineArrowData[i + 1] - GLplotLineArrowData[i]).multiple(double(2.0 / 3.0))); //���ߵĿ���ĩ��ָһ����ͷ
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
	//glVertex2f(1.0f, 0.0f);         // ������������Ի�x��
	//glVertex2f(0.0f, -1.0f);
	//glVertex2f(0.0f, 1.0f);         // ������������Ի�y��
	//glEnd();

	//glBegin(GL_LINE_STRIP);
	//for (x = -1.0f / factor; x<1.0f / factor; x += 0.01f)
	//{
	//	glVertex2f(x*factor, sin(x)*factor);
	//}
	//glEnd();

}
void CloseGLplot()//�������ϸ������ϵĹر�GL��ֻ�Ǳ���ԳƵĵ���Open Close GLplot
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