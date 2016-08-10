#include <iostream>  
#include <stdlib.h>  
#include <opencv.hpp>
#include <math.h>  
#include <glut.h>  
using namespace std;
using namespace cv;

float imgdata[450][620];
int w = 0;
int h = 0;
float scalar = 50;//scalar of converting pixel color to float coordinates  

#define pi 3.1415926  
bool mouseisdown = false;
bool loopr = false;
int mx, my;
int ry = 10;
int rx = 10;

void timer(int p)
{
	ry -= 5;
	//marks the current window as needing to be redisplayed.  
	glutPostRedisplay();
	if (loopr)
		glutTimerFunc(200, timer, 0);
}


void mouse(int button, int state, int x, int y)
{
	if (button == GLUT_LEFT_BUTTON)
	{
		if (state == GLUT_DOWN)
		{
			mouseisdown = true;
			loopr = false;
		}
		else
		{
			mouseisdown = false;
		}
	}

	if (button == GLUT_RIGHT_BUTTON)
		if (state == GLUT_DOWN)
		{
			loopr = true; glutTimerFunc(200, timer, 0);
		}
}

void motion(int x, int y)
{
	if (mouseisdown == true)
	{
		ry += x - mx;
		rx += y - my;
		mx = x;
		my = y;
		glutPostRedisplay();
	}
}

void special(int key, int x, int y)
{
	switch (key)
	{
	case GLUT_KEY_LEFT:
		ry -= 5;
		glutPostRedisplay();
		break;
	case GLUT_KEY_RIGHT:
		ry += 5;
		glutPostRedisplay();
		break;
	case GLUT_KEY_UP:
		rx += 5;
		glutPostRedisplay();
		break;
	case GLUT_KEY_DOWN:
		rx -= 5;
		glutPostRedisplay();
		break;
	}
}
void renderScene(void) {

	glClear(GL_COLOR_BUFFER_BIT);
	glLoadIdentity();// Reset the coordinate system before modifying  
	gluLookAt(0.0, 0.0, 7.0, 0.0, 0.0, 1.0, 0.0, 1.0, 0.0);
	//to invert the image  
	glRotatef(ry, 0, 1, 0);
	glRotatef(rx - 180, 1, 0, 0);

	float imageCenterX = w*.5;
	float imageCenterY = h*.5;
	float x, y, z;

	glPointSize(1.0);
	glBegin(GL_POINTS);//GL_POINTS  
	for (int i = 0; i < h; i++){
		for (int j = 0; j < w; j++){
			// color interpolation  
			glColor3f(1 - imgdata[i][j] / 255, imgdata[i][j] / 255, imgdata[i][j] / 255);//red,green,blue  
			x = ((float)j - imageCenterX) / scalar;
			y = ((float)i - imageCenterY) / scalar;
			z = (255 - imgdata[i][j]) / scalar;
			glVertex3f(x, y, z);
		}
	}
	glEnd();
	glFlush();
}

void reshape(int w, int h) {
	glViewport(0, 0, (GLsizei)w, (GLsizei)h);//set viewpoint  
	glMatrixMode(GL_PROJECTION);//specify which matrix is the current matrix  
	glLoadIdentity();//replace the current matrix with the identity matrix  
	gluPerspective(60, (GLfloat)w / (GLfloat)h, 1.0, 100.0);
	glMatrixMode(GL_MODELVIEW);
}

void displayDisparity(InputArray disparity){
	//double xyscale=100;  
	int j = 0;
	int i = 0;
	Mat t_dis = disparity.getMat();

	//accessing the image pixels  
	for (i = 0; i < h; i++){
		for (j = 0; j < w; j++){
			imgdata[i][j] = t_dis.at<char>(i, j);//for disparity is a grey image.  
			//cout << imgdata[i][j]<<endl;  
		}
	}
}
char *name1 = R"(E:\DATA\Pic\gray3.jpg)";

int main(int argc, char *argv[])
{
	cout << "OpenCV and OpenGL works together!" << endl;
	char* filename = argv[1];
#ifdef _DEBUG
	filename = name1;
#endif // _DEBUG
	Mat src = imread(filename, 0); //read image as a grey one  
	if (src.empty()){
		cout << "No valid image input." << endl;
		return 1;
	}
	w = src.cols;
	h = src.rows;

	displayDisparity(src);
	imshow("org", src);

	//------------------OpenGL-------------------------  
	glutInit(&argc, argv);//initialize the GLUT library  
	glutInitDisplayMode(GLUT_DEPTH | GLUT_SINGLE | GLUT_RGBA);//sets the initial display mode  
	glutInitWindowPosition(100, 100);
	glutInitWindowSize(500, 500);
	glutCreateWindow("3D disparity image");
	glutDisplayFunc(renderScene);

	glutReshapeFunc(reshape);
	glutMouseFunc(mouse);
	glutMotionFunc(motion);
	glutSpecialFunc(special);
	glutMainLoop();


	waitKey(0);

	return 0;
}