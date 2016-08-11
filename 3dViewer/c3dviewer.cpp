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

C3DViewer::C3DViewer(QWidget *parent)
	: QMainWindow(parent)
{
	ui.setupUi(this);
	initWindow();
#ifdef _DEBUG
#endif // _DEBUG
	
}

C3DViewer::~C3DViewer()
{

}

void C3DViewer::initWindow(){
	
}

void C3DViewer::inputPointCloud(){
	QString t_filename=QFileDialog::getOpenFileName(this, "选择点云txt文件", "",  "*.txt");
	
	QFile t_file(t_filename);
	t_file.open(QIODevice::ReadOnly);
	while (!t_file.atEnd()){
		QVector3D t_3dp;
		QString pointName = QString::fromLocal8Bit(t_file.read(20));
		for (int i = 0; i < 3 ; i++){
			t_3dp[0] = t_file.read(10).toDouble();
		}
		
	}
}
