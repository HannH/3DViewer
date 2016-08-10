#ifndef C3DVIEWER_H
#define C3DVIEWER_H

#include <QtWidgets/QMainWindow>
#include <Qt3DCore/qentity.h>
#include <Qt3DCore/qaspectengine.h>
#include "window.h"
#include "ui_c3dviewer.h"

class C3DViewer : public QMainWindow
{
	Q_OBJECT

public:
	C3DViewer(QWidget *parent = 0);
	~C3DViewer();

private:
	Ui::C3DViewerClass ui;
	Qt3DCore::QAspectEngine m_engine;
	Qt3DCore::QEntity m_entity;
	Window m_3Dwindow;
	void initWindow();//Ë¢ÐÂ´°¿Ú

private slots:
	void inputPointCloud();

};

#endif // C3DVIEWER_H
