#include "Visualization.h"

vector<double> GLplotPointsXData;
vector<double> GLplotPointsYData;
vector<double> GLplotPointsZData;
vector<float> GLplotPointsize;//对应的点的大小

vector<double> GLplotLineXData;
vector<double> GLplotLineYData;
vector<double> GLplotLineZData;
vector<float> GLplotLineWidth;//对应的直线的宽度
vector<int> GLplotLineType;//线的种类 
int numplotLineType = 0;

void OpenGLplot(void)
{
	int argc = 1;
	char ** argv = { 0 };
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGB | GLUT_SINGLE);
	glutInitWindowPosition(100, 0);
	glutInitWindowSize(600, 600);
	glutCreateWindow("OpenGL可视化显示");
	glClear(GL_COLOR_BUFFER_BIT);
}
void Display(void)
{
	float Size = GLplotPointsize[0];
	int Curenti = 0;
	if (GLplotPointsize.empty() == 0)
	{
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
				glVertex2d(GLplotPointsXData[i], GLplotPointsYData[i]);
			}
			glEnd();
			if (i >= GLplotPointsize.size())
				break;
		}
	}

	if (GLplotLineWidth.empty() == 0)
	{
		int linetype = GLplotLineType[0];
		Size = GLplotLineWidth[0];
		Curenti = 0;
		while (1)
		{
			glLineWidth(Size);
			glBegin(GL_LINES);
			int i;
			for (i = Curenti; i < GLplotLineWidth.size() - 1; i++)
			{
				if ((Size != GLplotLineWidth[i])||(linetype != GLplotLineType[i]))
				{
					Size = GLplotLineWidth[i];
					linetype = GLplotLineType[i];
					Curenti = i;
					break;
				}
				glVertex2d(GLplotLineXData[i], GLplotLineYData[i]);
				glVertex2d(GLplotLineXData[i + 1], GLplotLineYData[i + 1]);
			}
			glEnd();
			if (i >= GLplotLineWidth.size() - 1)
				break;
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
void AddBufferPoints(vector<Point> Points, float sizepoint)
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

	double maxIndexX = *max_element(PointsX.begin(), PointsX.end());
	double minIndexX = *min_element(PointsX.begin(), PointsX.end());
	double maxIndexY = *max_element(PointsY.begin(), PointsY.end());
	double minIndexY = *min_element(PointsY.begin(), PointsY.end());

	double scaleXmin = -0.9;
	double scaleXmax = 0.9;
	double scaleYmin = -0.9;
	double scaleYmax = 0.9;

	for (int i = 0; i < PointsX.size(); i++)
	{
		PointsX[i] = scaleXmin + ((PointsX[i] - (minIndexX)) / ((maxIndexX)-(minIndexX)))*(scaleXmax - scaleXmin);
		PointsY[i] = scaleYmin + ((PointsY[i] - (minIndexY)) / ((maxIndexY)-(minIndexY)))*(scaleYmax - scaleYmin);
		PointsZ[i] = 0;
	}

	for (int i = 0; i < PointsX.size(); i++)
	{
		GLplotPointsXData.push_back(PointsX[i]);
		GLplotPointsYData.push_back(PointsY[i]);
		GLplotPointsZData.push_back(PointsZ[i]);
		GLplotPointsize.push_back(sizepoint);
	}
}

void AddBufferLines(vector<Point> Points, float LineWidth)
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

	double maxIndexX = *max_element(PointsX.begin(), PointsX.end());
	double minIndexX = *min_element(PointsX.begin(), PointsX.end());
	double maxIndexY = *max_element(PointsY.begin(), PointsY.end());
	double minIndexY = *min_element(PointsY.begin(), PointsY.end());

	double scaleXmin = -0.9;
	double scaleXmax = 0.9;
	double scaleYmin = -0.9;
	double scaleYmax = 0.9;

	for (int i = 0; i < PointsX.size(); i++)
	{
		PointsX[i] = scaleXmin + ((PointsX[i] - (minIndexX)) / ((maxIndexX)-(minIndexX)))*(scaleXmax - scaleXmin);
		PointsY[i] = scaleYmin + ((PointsY[i] - (minIndexY)) / ((maxIndexY)-(minIndexY)))*(scaleYmax - scaleYmin);
		PointsZ[i] = 0;
	}
	numplotLineType = numplotLineType + 1;
	for (int i = 0; i < PointsX.size(); i++)
	{
		GLplotLineXData.push_back(PointsX[i]);
		GLplotLineYData.push_back(PointsY[i]);
		GLplotLineZData.push_back(PointsZ[i]);
		GLplotLineWidth.push_back(LineWidth);
		GLplotLineType.push_back(numplotLineType);
	}
	//GLplotLineXData.push_back(PointsX[0]);
	//GLplotLineYData.push_back(PointsY[0]);
	//GLplotLineZData.push_back(PointsZ[0]);
	//GLplotLineWidth.push_back(LineWidth);
	//GLplotLineType.push_back(numplotLineType);
}