#include "c3dviewer.h"
#include <QScreen>
#include <Qt3DInput/QInputAspect>
#include <Qt3DCore/qcamera.h>

#include <Qt3DRender/qtorusmesh.h>
#include <Qt3DRender/qmesh.h>
#include <Qt3DRender/qtechnique.h>
#include <Qt3DRender/qmaterial.h>
#include <Qt3DRender/qeffect.h>
#include <Qt3DRender/qtexture.h>
#include <Qt3DRender/qrenderpass.h>
#include <Qt3DRender/qsceneloader.h>

#include <Qt3DCore/qtransform.h>
#include <Qt3DCore/qaspectengine.h>

#include <Qt3DRender/qrenderaspect.h>
#include <Qt3DRender/qframegraph.h>
#include <Qt3DRender/qforwardrenderer.h>
#include <QFileDialog>
#include <QStringList>
# pragma execution_character_set("utf-8")

C3DViewer::C3DViewer(QWidget *parent)
	: QMainWindow(parent), m_pcScene(parent)
{
	ui.setupUi(this);
	//ui.scrollArea->setWidget(m_pcScene);
	initWindow();
#ifdef _DEBUG
#endif // _DEBUG
	
}

C3DViewer::~C3DViewer()
{

}

void C3DViewer::initWindow(){
	ui.verticalLayout->addWidget(&m_pcScene);
}

void C3DViewer::inputPointCloud(){
	QString t_filename=QFileDialog::getOpenFileName(this, "选择点云txt文件", "",  "*.txt");
	
	QFile t_file(t_filename);
	t_file.open(QIODevice::ReadOnly);
	PointCloudEle t_3dp;
	m_pcScene.clearCpd();
	while (!t_file.atEnd()){
		QStringList context = QString::fromLocal8Bit(t_file.readLine()).split(" ");
		QString pointName = context[0];
		for (int i = 0; i < 3 ; i++){
			t_3dp.geo[i] = context[i+1].toDouble();
		}
		t_3dp.value = context[3].toDouble();
		m_pcScene.addPointCloud(t_3dp);
	}
	m_pcScene.reset();
}
