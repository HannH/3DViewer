#ifndef CCLOUDPOINTSCENE_H
#define CCLOUDPOINTSCENE_H
#include <vector>
using namespace std;

struct CloudPointEle
{
	double geo[3],value;//x,y,z
};
struct CamaraInfo
{
	double pos[3], ang[3];//外方位元素
};

#include <QObject>

class CCloudPointScene : public QObject
{
	Q_OBJECT

public:
	CCloudPointScene(QObject *parent);
	~CCloudPointScene();
	void renderScenen();
	void reshape(int w, int h);
	void mouse(int button, int state, int x, int y);
	void motion(int x, int y);
	void special(int key, int x, int y);

private:
	//旋转角度，平移距离，缩放倍数
	double m_rx, m_ry, m_dx, m_dy, m_scale;
	//场景大小
	double m_sw, m_sh;
	CamaraInfo m_cmr;//相机参数
	vector<CloudPointEle> m_cptVec;//点云数组

	void initWindow();
};

#endif // CCLOUDPOINTSCENE_H
