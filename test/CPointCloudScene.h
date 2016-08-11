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
	double pos[3], ang[3];//�ⷽλԪ��
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
	void motion(int x, int y);//��ת
	void move(int x, int y);//ƽ��
	void zoom(double zoomV){ m_scale *= zoomV; };//����

private:
	//��ת�Ƕȣ����ű���
	double m_rx, m_ry, m_scale;
	//��һ�����λ��
	double m_mx, m_my;
	//��������
	double m_sw, m_sh;
	CamaraInfo m_cmr;//�������
	std::vector<PointCloudEle> m_ptcVec;//��������
	//qopenglWidget
	QOpenGLShaderProgram *m_program;
	QMatrix4x4 m_proj;

	//glut
	void reshape(int w, int h);
	void initWindow();
};

#endif // CCLOUDPOINTSCENE_H
