#include "Visualization.h"

vector<double> GLplotPointsXData;
vector<double> GLplotPointsYData;
vector<double> GLplotPointsZData;
vector<float> GLplotPointsize;//��Ӧ�ĵ�Ĵ�С

void OpenGLplot(void)
{
	int argc = 1;
	char ** argv = { 0 };
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGB | GLUT_SINGLE);
	glutInitWindowPosition(100, 0);
	glutInitWindowSize(600, 600);
	glutCreateWindow("OpenGL���ӻ���ʾ");
	glClear(GL_COLOR_BUFFER_BIT);
}
void Display(void)
{
	float Size = GLplotPointsize[0];
	int Curenti = 0;

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