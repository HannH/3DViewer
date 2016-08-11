#include "CPointCloudScene.h"
const char *CPointCloudScene::vertexShaderSourceCore =
"#version 150\n"
"in vec4 vPosition;\n"
"in vec4 vertex;\n"
"out vec3 vert;\n"
"void main() {\n"
"   vert = vertex.xyz;\n"
"   gl_Position = vPosition;\n"
"}\n";
/* Ƭ����ɫ�� */
const char *CPointCloudScene::fragmentShaderSourceCore =
"#version 150\n"
"out highp vec4 fragColor;\n"
"void main() {\n"
"   fragColor = vec4(1.0, 0.0, 0.0, 1.0);\n"
"}\n";
CPointCloudScene::CPointCloudScene(QObject *parent)
{
	initializeGL();
	/* ������ɫ�� */
	
}

CPointCloudScene::~CPointCloudScene()
{

}

void CPointCloudScene::renderScenen(){
	/*glClear(GL_COLOR_BUFFER_BIT);
	glLoadIdentity();// Reset the coordinate system before modifying  
	double objCor[3] = { 0, 0, 1 };
	gluLookAt(m_cmr.pos[0] + objCor[0], m_cmr.pos[1] + objCor[1], m_cmr.pos[2] + objCor[2],
		objCor[0], objCor[1], objCor[2], m_cmr.ang[0], m_cmr.ang[1], m_cmr.ang[2]);
	//to invert the image  
	glRotatef(m_ry, 0, 1, 0);
	glRotatef(m_rx - 180, 1, 0, 0);

	float imageCenterX = m_sw;
	float imageCenterY = m_sh;
	float imageCenterZ = 1.0;
	float x, y, z;

	glPointSize(1.0);
	glBegin(GL_POINTS);//GL_POINTS  
	for (int i = 0; i < m_ptcVec.size() ; i++){
		glColor3f(m_ptcVec[i].value, 0, 0);
		x = (m_ptcVec[i].geo[0] - imageCenterX) / m_scale;
		y = (m_ptcVec[i].geo[1] - imageCenterY) / m_scale;
		z = (m_ptcVec[i].geo[2] - imageCenterZ) / m_scale;
		glVertex3f(x, y, z);
	}
	glEnd();
	glFlush();*/
}
void CPointCloudScene::reshape(int w, int h){
	/*glViewport(0, 0, (GLsizei)w, (GLsizei)h);//set viewpoint  
	glMatrixMode(GL_PROJECTION);//specify which matrix is the current matrix  
	glLoadIdentity();//replace the current matrix with the identity matrix  
	gluPerspective(60, (GLfloat)w / (GLfloat)h, 1.0, 100.0);
	glMatrixMode(GL_MODELVIEW);*/
}
void CPointCloudScene::motion(int x, int y){
	m_ry += x - m_mx;
	m_rx += y - m_my;
	m_mx = x;
	m_my = y;
	//glutPostRedisplay();
}
void CPointCloudScene::move(int x, int y){
	m_sw += x - m_mx;
	m_sh += y - m_my;
	m_mx = x;
	m_my = y;
	glFlush();
}
void CPointCloudScene::initWindow(){
}
void CPointCloudScene::initializeGL(){
	initializeOpenGLFunctions();
	glClearColor(0,0,0,0);
	m_program = new QOpenGLShaderProgram;
	/* һ��Ӧ�ó����Ѿ������˶��㡢Ƭ����ɫ������
	* ����Ҫȥ������Ŀ������Ŀ�����յ����Ӷ���
	* ÿ����ɫ���ڱ�����ǰ��Ӧ����ϵ����Ŀ������Ŀ����
	* ***************************************** */
	/* 1.2 ���� */
	m_program->addShaderFromSourceCode(QOpenGLShader::Vertex, vertexShaderSourceCore);
	m_program->addShaderFromSourceCode(QOpenGLShader::Fragment, fragmentShaderSourceCore);
	/* 1.3 ��ֵ ������˵������֪���ϲ����ʣ� */ /* ����˵�� */
	/* 1.3 ��������λ�ã���vPosition��������Ϊλ��0, vertexΪλ��1 */
	m_program->bindAttributeLocation("vertex", 1);
	m_program->bindAttributeLocation("vPosition", 0);
	/* 1.4 ������Ŀ������ */
	m_program->link();
	/* 1.5 Ϊʹ����Ŀ����ȥ��Ⱦ����Ҫ�� */
	m_program->bind();
	int vert = m_program->uniformLocation("vert");
	qDebug("[1] vert=%d", vert);
	/* ��ɫ����������д���������ԣ�û����˼�ģ����Խ��Ϊvertex����Ϊ0,1,2...
	�õ���vert����-1 */
}
void CPointCloudScene::resizeGL(int w, int h){
	glViewport(0, 0, (GLsizei)w, (GLsizei)h);//set viewpoint  
	m_proj.setToIdentity();
	m_proj.perspective(45.0f, GLfloat(w) / h, 0.01f, 100.0f);
}
void CPointCloudScene::paintGL(){
	/* 2.2 ������������ glClearColor ��������ɫ����ֵ��� */
	glClear(GL_COLOR_BUFFER_BIT);
	glLoadIdentity();// Reset the coordinate system before modifying  
	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
	glClear(GL_DEPTH_BUFFER_BIT);
	glEnable(GL_DEPTH_TEST);
	/* ��ת�����ַ�ʽ��1. ������ת������������ 2. ������������������岻�����������ת */
	QMatrix4x4 world;
	world.setToIdentity();
	m_rx = 20, m_ry = 70;
	world.rotate(m_rx - 180, 1, 0, 0);/* ��X�� */
	world.rotate(m_ry, 0, 1, 0);/* ��Y�� */
	QMatrix4x4 m_camera;
	m_camera.setToIdentity();
	m_camera.translate(0, 0);
	m_program->setUniformValue(m_program->uniformLocation("projMatrix"), m_proj);
	m_program->setUniformValue(m_program->uniformLocation("mvMatrix"), m_camera * world);

	float imageCenterX = m_sw;
	float imageCenterY = m_sh;
	float imageCenterZ = 1.0;
	float x, y, z;

	/*glPointSize(1.0);
	glBegin(GL_POINTS);//GL_POINTS  
	for (int i = 0; i < 100; i++){
		glColor3f(255, 0, 0);
		x = i / 5.0;
		y = i / 4.0;
		z = 1.0;
		glVertex3f(x, y, z);
	}
	glEnd();
	glFlush();*/
	glPointSize(1.0);
	m_scale = 50;
	glBegin(GL_POINTS);//GL_POINTS  
	for (int i = 0; i < m_ptcVec.size(); i++){
		glColor3f(m_ptcVec[i].value, 0, 0);
		x = (m_ptcVec[i].geo[0] - imageCenterX) / m_scale;
		y = (m_ptcVec[i].geo[1] - imageCenterY) / m_scale;
		z = (m_ptcVec[i].geo[2] - imageCenterZ) / m_scale;
		glVertex3f(x, y, z);
	}
	glEnd();
	glFlush();
	m_program->release();
}
const char *name1 = R"(E:\DATA\Pic\gray1.jpg)";
#include <opencv.hpp>
#include <fstream>
using namespace cv;
using namespace std;
void CPointCloudScene::testFun(){
	Mat src = imread(name1, IMREAD_GRAYSCALE);
	int summ = 0;
	m_ptcVec.resize(src.size().area()+2);
	ofstream f;
	f.open(R"(E:\c++ excise\3dViewer\3dViewer\cp3.txt)");
	bool m=f.is_open();
	for (int i = 0; i < src.cols; i++){
		for (int j = 0; j < src.rows ; j++){
			f << "pcd003_" << i << " " << i << " " << j << " " << int(src.at<char>(j, i)) << endl;
			m_ptcVec[summ].geo[0] = i;
			m_ptcVec[summ].geo[1] = j;
			m_ptcVec[summ].geo[2] = src.at<char>(j,i);
			m_ptcVec[summ].value = m_ptcVec[summ].geo[2];
			summ++;
		}
	}
	f.close();
}
