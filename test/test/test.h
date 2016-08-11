#ifndef MYGLWIDGET_H

#define MYGLWIDGET_H

#include <QOpenGLWidget>

#include <QMatrix4x4>

#include <QOpenGLContext>

#include <QOpenGLFunctions>

#include <QOpenGLShaderProgram>

/* ************************************************************

* QOpenGLFunctions:

*   使用的是2.0，也就是qt默认使用的OpenGL ES 2.0

*   查看此类，看以看到有很多提示说要我们查看OpenGL ES 2.0 documentation

*   来查看函数的具体功能和使用

*

* opengl/es 在opengl基础上，为设备做了简化，移除大多数冗余设计

*   OpenGL ES 2.0 是以可编程着色器为基础的，

*   这意味着你绘制任何图形都必须有一个合适的着色器装载和绑定

*

* 在《opengl es 2.0 编程指南》中一开始有个Hello Triangle例子

*   使用 EGL 创造一个显示渲染窗口平面。

*   装载顶点和片段着色器。

*   创造一个项目，联系顶点和片段着色器，链接项目。

*   设置视窗。

*   清除颜色缓冲区。

*   最基本的渲染。

*   在 EGL 窗口显示颜色缓冲区的内容

*

* 这个例子使用的是EGL，这里使用QT

* ************************************************************ */

class MyGLWidget : public QOpenGLWidget, protected QOpenGLFunctions

{

	Q_OBJECT

public:

	MyGLWidget(QWidget *parent = 0);

	~MyGLWidget();

protected:

	void initializeGL();
	/* [2] 回调绘画 */
	void paintGL();
	void resizeGL(int  w, int h);

private:

	/* [1] 需要定点着色器和片段着色器，不然做不了任何渲染 */

	/*   这里定义了一个着色器编译对象 */

	QOpenGLShaderProgram *program;

	QMatrix4x4 p;

};

#endif // MYGLWIDGET_H