#ifndef CCLOUDPOINTSCENE_H
#define CCLOUDPOINTSCENE_H
#include <vector>
#include <QObject>
#include <QOpenGLWidget>
#include <QOpenGLFunctions>
#include <QOpenGLShader>
#include <QOpenGLBuffer>

struct PointCloudEle
{
	double geo[3],value;//x,y,z
};
struct CamaraInfo
{
	double pos[3], ang[3];//外方位元素
};

class CPointCloudScene : public QOpenGLWidget,protected QOpenGLFunctions
{
	Q_OBJECT

public:
	CPointCloudScene(){ initWindow(); };
	CPointCloudScene(QObject *parent);
	~CPointCloudScene();
	void renderScenen();
	void addPointCloud(const PointCloudEle& ele){ m_ptcVec.push_back(ele); };
	void setPointCloud(const std::vector<PointCloudEle>& pcvec){ m_ptcVec = pcvec; };

protected:
	QOpenGLWidget * pgl;
	void initializeGL();
	void resizeGL(int w, int h);
	void paintGL();

private slots:
	void motion(int x, int y);//旋转
	void move(int x, int y);//平移
	void zoom(double zoomV){ m_scale *= zoomV; };//缩放

private:
	//旋转角度，缩放倍数
	double m_rx, m_ry, m_scale;
	//上一次鼠标位置
	double m_mx, m_my;
	//场景中心
	double m_sw, m_sh;
	CamaraInfo m_cmr;//相机参数
	std::vector<PointCloudEle> m_ptcVec;//点云数组
	//qopenglWidget
	QOpenGLShaderProgram *m_program;
	QMatrix4x4 m_proj;

	//glut
	void reshape(int w, int h);
	void initWindow();
};

#endif // CCLOUDPOINTSCENE_H
