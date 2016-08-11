#ifndef MYGLWIDGET_H

#define MYGLWIDGET_H

#include <QOpenGLWidget>

#include <QMatrix4x4>

#include <QOpenGLContext>

#include <QOpenGLFunctions>

#include <QOpenGLShaderProgram>

/* ************************************************************

* QOpenGLFunctions:

*   ʹ�õ���2.0��Ҳ����qtĬ��ʹ�õ�OpenGL ES 2.0

*   �鿴���࣬���Կ����кܶ���ʾ˵Ҫ���ǲ鿴OpenGL ES 2.0 documentation

*   ���鿴�����ľ��幦�ܺ�ʹ��

*

* opengl/es ��opengl�����ϣ�Ϊ�豸���˼򻯣��Ƴ�������������

*   OpenGL ES 2.0 ���Կɱ����ɫ��Ϊ�����ģ�

*   ����ζ��������κ�ͼ�ζ�������һ�����ʵ���ɫ��װ�غͰ�

*

* �ڡ�opengl es 2.0 ���ָ�ϡ���һ��ʼ�и�Hello Triangle����

*   ʹ�� EGL ����һ����ʾ��Ⱦ����ƽ�档

*   װ�ض����Ƭ����ɫ����

*   ����һ����Ŀ����ϵ�����Ƭ����ɫ����������Ŀ��

*   �����Ӵ���

*   �����ɫ��������

*   ���������Ⱦ��

*   �� EGL ������ʾ��ɫ������������

*

* �������ʹ�õ���EGL������ʹ��QT

* ************************************************************ */

class MyGLWidget : public QOpenGLWidget, protected QOpenGLFunctions

{

	Q_OBJECT

public:

	MyGLWidget(QWidget *parent = 0);

	~MyGLWidget();

protected:

	void initializeGL();
	/* [2] �ص��滭 */
	void paintGL();
	void resizeGL(int  w, int h);

private:

	/* [1] ��Ҫ������ɫ����Ƭ����ɫ������Ȼ�������κ���Ⱦ */

	/*   ���ﶨ����һ����ɫ��������� */

	QOpenGLShaderProgram *program;

	QMatrix4x4 p;

};

#endif // MYGLWIDGET_H