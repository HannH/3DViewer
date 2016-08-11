#include "ccloudpointscene.h"
#include <glut.h>  

CCloudPointScene::CCloudPointScene(QObject *parent)
	: QObject(parent)
{

}

CCloudPointScene::~CCloudPointScene()
{

}

void CCloudPointScene::renderScenen(){
	glClear(GL_COLOR_BUFFER_BIT);
	glLoadIdentity();// Reset the coordinate system before modifying  
	double objCor[3] = { 0, 0, 1 };
	gluLookAt(m_cmr.pos[0] + objCor[0], m_cmr.pos[1] + objCor[1], m_cmr.pos[2] + objCor[2],
		objCor[0], objCor[1], objCor[2], m_cmr.ang[0], m_cmr.ang[1], m_cmr.ang[2]);
	//to invert the image  
	glRotatef(m_ry, 0, 1, 0);
	glRotatef(m_rx - 180, 1, 0, 0);

	float imageCenterX = m_sw*.5;
	float imageCenterY = m_sh*.5;
	float imageCenterZ = 1.0;
	float x, y, z;

	glPointSize(1.0);
	glBegin(GL_POINTS);//GL_POINTS  
	for (int i = 0; i < m_cptVec.size() ; i++){
		glColor3f(m_cptVec[i].value, 0, 0);
		x = (m_cptVec[i].geo[0] - imageCenterX) / m_scale;
		y = (m_cptVec[i].geo[1] - imageCenterY) / m_scale;
		z = (m_cptVec[i].geo[2] - imageCenterZ) / m_scale;
		glVertex3f(x, y, z);
	}
	glEnd();
	glFlush();
}
void CCloudPointScene::reshape(int w, int h){
	glViewport(0, 0, (GLsizei)w, (GLsizei)h);//set viewpoint  
	glMatrixMode(GL_PROJECTION);//specify which matrix is the current matrix  
	glLoadIdentity();//replace the current matrix with the identity matrix  
	gluPerspective(60, (GLfloat)w / (GLfloat)h, 1.0, 100.0);
	glMatrixMode(GL_MODELVIEW);
}
void CCloudPointScene::mouse(int button, int state, int x, int y){
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
void CCloudPointScene::motion(int x, int y){
	if (mouseisdown == true)
	{
		ry += x - mx;
		rx += y - my;
		mx = x;
		my = y;
		glutPostRedisplay();
	}
}
void CCloudPointScene::special(int key, int x, int y){
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
void CCloudPointScene::initWindow(){
	glutInit(&argc, argv);//initialize the GLUT library  
	glutInitDisplayMode(GLUT_DEPTH | GLUT_SINGLE | GLUT_RGBA);//sets the initial display mode  
	glutInitWindowPosition(100, 100);
	glutInitWindowSize(500, 500);
	glutCreateWindow("3D disparity image");
	glutDisplayFunc(this->renderScenen);

	glutReshapeFunc(this->reshape);
	glutMouseFunc(this->mouse);
	glutMotionFunc(this->motion);
	glutSpecialFunc(this->special);
	glutMainLoop();
}