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
	double pos[3], ang[3];//�ⷽλԪ��
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
	//��ת�Ƕȣ�ƽ�ƾ��룬���ű���
	double m_rx, m_ry, m_dx, m_dy, m_scale;
	//������С
	double m_sw, m_sh;
	CamaraInfo m_cmr;//�������
	vector<CloudPointEle> m_cptVec;//��������

	void initWindow();
};

#endif // CCLOUDPOINTSCENE_H
