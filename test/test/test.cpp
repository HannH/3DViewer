#include "test.h"
#include <QPainter>
#include <QPen>
#include <QDebug>
MyGLWidget::MyGLWidget(QWidget *parent)
	: QOpenGLWidget(parent)
{
	setWindowTitle("My OpenGL Widget");
	resize(600, 400);
}
MyGLWidget::~MyGLWidget()
{
}
/* 1.1 ��ɫ������ */
/* ���Կ���֮�����Ͽ���֪����in�����룬��Ҫ������������ */
/* *********************************************
* ժ¼�� �����ָ�ϡ�
*   ������ɫ������һ�����룬���� 4 ����Ա��ʸ�� vPosition��
*   ������������ɫ��������ɫ����ʼִ�С���ɫ������ǳ��򵥣�
*   ���������� vPosition ���Ե� gl_Position ��������С�
*   ÿ��������ɫ���������λ��ֵ�� gl_Position �����У�
*   ����������뵽���ߵ���һ���׶��С�
* ******************************************** */
/* ������ɫ�� */
static const char *vertexShaderSourceCore =
"#version 150\n"
"in vec4 vPosition;\n"
"in vec4 vertex;\n"
"out vec3 vert;\n"
"void main() {\n"
"   vert = vertex.xyz;\n"
"   gl_Position = vPosition;\n"
"}\n";
/* �������˼�ɾ�� */
/* *********************************************
* ժ¼�� �����ָ�ϡ�
*   main�������������ֵ(1.0, 0.0, 0.0, 1.0)��������
*   gl_FragColor��gl_FragColor��Ƭ����ɫ�����յ����ֵ��
*   ���������ֵ�Ǻ�ɫ��
* ******************************************** */
/* �����һ������hellogl2�е�һ�䣬����˵��һ��������� */
/* �����벻֪���������˲�֪��
* warning C7533:
*   global variable gl_FragColor is deprecated after version 120
* ��Ȼ����һ����ע��Ļ�Ҳ��֪��
*   error C1008: undefined variable "col"
*/
/* ����out������˵�����ڶ�����ɫ���ϣ�Ҳ����ΪfragColor��hellogl2������û��ȥ��ȡ */
#if 0
static const char *fragmentShaderSourceCore =
"#version 150\n"
"out highp vec4 fragColor;\n"
"void main() {\n"
"   gl_FragColor = vec4(1.0, 0.0, 0.0, 1.0);\n"
"   fragColor = vec4(col, 1.0);\n"
"}\n";
#else
/* Ƭ����ɫ�� */
static const char *fragmentShaderSourceCore =
"#version 150\n"
"out highp vec4 fragColor;\n"
"void main() {\n"
"   fragColor = vec4(1.0, 0.0, 0.0, 1.0);\n"
"}\n";
#endif
void MyGLWidget::initializeGL()
{
	qDebug("+++ initializeGL +++");
	/* 0. ��ʼ��������ʹ�ú�������ʹ�� */
	initializeOpenGLFunctions();
	/* ������Ŀ����������ɫ�� */
	/* 1. ��ʼ������������װ�ض����Ƭ����ɫ�� */
	program = new QOpenGLShaderProgram;
	/* һ��Ӧ�ó����Ѿ������˶��㡢Ƭ����ɫ������
	* ����Ҫȥ������Ŀ������Ŀ�����յ����Ӷ���
	* ÿ����ɫ���ڱ�����ǰ��Ӧ����ϵ����Ŀ������Ŀ����
	* ***************************************** */
	/* 1.2 ���� */
	program->addShaderFromSourceCode(QOpenGLShader::Vertex, vertexShaderSourceCore);
	program->addShaderFromSourceCode(QOpenGLShader::Fragment, fragmentShaderSourceCore);
	/* 1.3 ��ֵ ������˵������֪���ϲ����ʣ� */ /* ����˵�� */
	/* 1.3 ��������λ�ã���vPosition��������Ϊλ��0, vertexΪλ��1 */
	program->bindAttributeLocation("vertex", 1);
	program->bindAttributeLocation("vPosition", 0);
	/* 1.4 ������Ŀ������ */
	program->link();
	/* 1.5 Ϊʹ����Ŀ����ȥ��Ⱦ����Ҫ�� */
	program->bind();
	int vert = program->uniformLocation("vert");
	qDebug("[1] vert=%d", vert);
	/* ��ɫ����������д���������ԣ�û����˼�ģ����Խ��Ϊvertex����Ϊ0,1,2...
	�õ���vert����-1 */
}
/* 2. �ص��滭 */
void MyGLWidget::paintGL()
{
	/* 2.1 viewport �趨���ڵ�ԭ�� origin (x, y)����Ⱥ͸߶� */
	glViewport(0, 0, width(), height());
	/* 2.2 ������������ glClearColor ��������ɫ����ֵ��� */
	glClear(GL_COLOR_BUFFER_BIT);
	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
	/* 2.3 �����ζ�������� */
	GLfloat vVertices[] = { 0.0f, 0.5f, 0.0f,
		-0.5f, -0.5f, 0.0f,
		0.5f, -0.5f, 0.0f };
	/* 2.4 Load the vertex data */
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, vVertices);
	/* ժ¼�� �����ָ�ϡ�
	*   ����λ����Ҫ��װ�ص� GL ��ϵ�� vPosition��
	*   ���Ƿ��뵽��ǰ���ǰ� vPosition ����������λ�� 0��
	*   ÿ��������ɫ���е����Զ���һ��Ψһ�����޷�����������ʾ��λ�ã�
	*   ����glVertexAttribPointer ���������ǰ�����װ�ص�λ�� 0
	* ***************************************************** */
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, vVertices);
	glEnableVertexAttribArray(0);
	glPointSize(2.0);
	glBegin(GL_POINTS);//GL_POINTS  
	double x, y, z;
	for (int i = 0; i < 100; i++){
		glColor3f(255, i, 0);
		x = i / 25.0;
		y = i / 24.0;
		z = i;
		glVertex3f(x, y, z);
	}
	glEnd();
	glFlush();
	int vert = program->uniformLocation("vert");
	qDebug("[2] vert=%d", vert);
	program->release();
}
void MyGLWidget::resizeGL(int  w, int h)
{
	p.setToIdentity();
	p.perspective(35.0f, float(w) / float(h), 1.0f, 30.0f);
}