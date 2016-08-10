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
#include "scenemodifier.h"

C3DViewer::C3DViewer(QWidget *parent)
	: QMainWindow(parent)
{
	ui.setupUi(this);
	initWindow();
#ifdef _DEBUG
	SceneModifier t_modifier(&m_entity);
	t_modifier.addPoint(QVector3D(-5.0f, -4.0f, 0.0f), 3);
#endif // _DEBUG
	
}

C3DViewer::~C3DViewer()
{

}

void C3DViewer::initWindow(){
	ui.widget = QWidget::createWindowContainer(&m_3Dwindow);
	m_engine.registerAspect(new Qt3DRender::QRenderAspect());
	Qt3DInput::QInputAspect *input = new Qt3DInput::QInputAspect();
	m_engine.registerAspect(input);
	QVariantMap data;
	data.insert(QStringLiteral("surface"), QVariant::fromValue(static_cast<QSurface *>(&m_3Dwindow)));
	data.insert(QStringLiteral("eventSource"), QVariant::fromValue(&m_3Dwindow));
	m_engine.setData(data);
	// Camera
	Qt3DCore::QCamera *cameraEntity = new Qt3DCore::QCamera(&m_entity);
	cameraEntity->setObjectName(QStringLiteral("cameraEntity"));
	cameraEntity->lens()->setPerspectiveProjection(45.0f, 16.0f / 9.0f, 0.1f, 1000.0f);
	cameraEntity->setPosition(QVector3D(0, 0, -20.0f));
	cameraEntity->setUpVector(QVector3D(0, 1, 0));
	cameraEntity->setViewCenter(QVector3D(0, 0, 0));
	input->setCamera(cameraEntity);

	// FrameGraph
	Qt3DRender::QFrameGraph *frameGraph = new Qt3DRender::QFrameGraph();
	Qt3DRender::QForwardRenderer *forwardRenderer = new Qt3DRender::QForwardRenderer();

	forwardRenderer->setCamera(cameraEntity);
	forwardRenderer->setClearColor(QColor(QRgb(0x4d4d4f)));
	frameGraph->setActiveFrameGraph(forwardRenderer);

	// Setting the FrameGraph
	m_entity.addComponent(frameGraph);
	// Set root object of the scene
	m_engine.setRootEntity(&m_entity);

	// Update the aspect ratio//???
	QSize widgetSize = ui.widget->size();
	float aspectRatio = float(widgetSize.width()) / float(widgetSize.height());
	cameraEntity->lens()->setPerspectiveProjection(45.0f, aspectRatio, 0.1f, 1000.0f);
}

void C3DViewer::inputPointCloud(){
	QString t_filename=QFileDialog::getOpenFileName(this, "选择点云txt文件", "",  "*.txt");
	SceneModifier t_modifier(&m_entity);
	QFile t_file(t_filename);
	t_file.open(QIODevice::ReadOnly);
	while (!t_file.atEnd()){
		QVector3D t_3dp;
		QString pointName = QString::fromLocal8Bit(t_file.read(20));
		for (int i = 0; i < 3 ; i++){
			t_3dp[0] = t_file.read(10).toDouble();
		}
		t_modifier.addPoint(t_3dp, 3);
	}
}
