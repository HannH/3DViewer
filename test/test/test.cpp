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
/* 1.1 着色器代码 */
/* 粗略看过之后，马上可以知道，in即输入，需要穿参数进来的 */
/* *********************************************
* 摘录自 《编程指南》
*   顶点着色器定义一个输入，它是 4 个成员的矢量 vPosition。
*   主函数声明着色器宣布着色器开始执行。着色器主体非常简单，
*   它复制输入 vPosition 属性到 gl_Position 输出变量中。
*   每个顶点着色器必须输出位置值到 gl_Position 变量中，
*   这个变量传入到管线的下一个阶段中。
* ******************************************** */
/* 顶点着色器 */
static const char *vertexShaderSourceCore =
"#version 150\n"
"in vec4 vPosition;\n"
"in vec4 vertex;\n"
"out vec3 vert;\n"
"void main() {\n"
"   vert = vertex.xyz;\n"
"   gl_Position = vPosition;\n"
"}\n";
/* 这里做了简单删改 */
/* *********************************************
* 摘录自 《编程指南》
*   main函数，它的输出值(1.0, 0.0, 0.0, 1.0)赋给变量
*   gl_FragColor，gl_FragColor是片段着色器最终的输出值，
*   本例中输出值是红色。
* ******************************************** */
/* 这里我还添加了hellogl2中的一句，用来说明一个输出变量 */
/* 不编译不知道，编译了才知道
* warning C7533:
*   global variable gl_FragColor is deprecated after version 120
* 当然还有一个不注意的话也不知道
*   error C1008: undefined variable "col"
*/
/* 所以out变量的说明放在顶点着色器上，也是因为fragColor在hellogl2例子中没有去获取 */
#if 0
static const char *fragmentShaderSourceCore =
"#version 150\n"
"out highp vec4 fragColor;\n"
"void main() {\n"
"   gl_FragColor = vec4(1.0, 0.0, 0.0, 1.0);\n"
"   fragColor = vec4(col, 1.0);\n"
"}\n";
#else
/* 片段着色器 */
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
	/* 0. 初始化函数，使得函数可以使用 */
	initializeOpenGLFunctions();
	/* 创建项目对象链接着色器 */
	/* 1. 初始化最大的任务是装载顶点和片段着色器 */
	program = new QOpenGLShaderProgram;
	/* 一旦应用程序已经创建了顶点、片段着色器对象，
	* 它需要去创建项目对象，项目是最终的链接对象，
	* 每个着色器在被绘制前都应该联系到项目或者项目对象。
	* ***************************************** */
	/* 1.2 加载 */
	program->addShaderFromSourceCode(QOpenGLShader::Vertex, vertexShaderSourceCore);
	program->addShaderFromSourceCode(QOpenGLShader::Fragment, fragmentShaderSourceCore);
	/* 1.3 传值 （这样说明，不知道合不合适） */ /* 错误说明 */
	/* 1.3 设置属性位置，将vPosition属性设置为位置0, vertex为位置1 */
	program->bindAttributeLocation("vertex", 1);
	program->bindAttributeLocation("vPosition", 0);
	/* 1.4 链接项目检查错误 */
	program->link();
	/* 1.5 为使用项目对象去渲染，需要绑定 */
	program->bind();
	int vert = program->uniformLocation("vert");
	qDebug("[1] vert=%d", vert);
	/* 着色器代码那样写，纯属测试，没有意思的，测试结果为vertex设置为0,1,2...
	得到的vert都是-1 */
}
/* 2. 回调绘画 */
void MyGLWidget::paintGL()
{
	/* 2.1 viewport 设定窗口的原点 origin (x, y)、宽度和高度 */
	glViewport(0, 0, width(), height());
	/* 2.2 缓冲区将被用 glClearColor 函数的颜色参数值清除 */
	glClear(GL_COLOR_BUFFER_BIT);
	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
	/* 2.3 三角形顶点的坐标 */
	GLfloat vVertices[] = { 0.0f, 0.5f, 0.0f,
		-0.5f, -0.5f, 0.0f,
		0.5f, -0.5f, 0.0f };
	/* 2.4 Load the vertex data */
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, vVertices);
	/* 摘录自 《编程指南》
	*   顶点位置需要被装载到 GL 联系到 vPosition，
	*   你是否想到先前我们绑定 vPosition 变量到属性位置 0，
	*   每个顶点着色器中的属性都有一个唯一的用无符号整形数标示的位置，
	*   调用glVertexAttribPointer 函数，我们把数据装载到位置 0
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