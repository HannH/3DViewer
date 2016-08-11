#ifndef C3DVIEWER_H
#define C3DVIEWER_H

#include <QtWidgets/QMainWindow>
#include "glwidget.h"
#include "ui_c3dviewer.h"

class C3DViewer : public QMainWindow
{
	Q_OBJECT

public:
	C3DViewer(QWidget *parent = 0);
	~C3DViewer();

private:
	Ui::C3DViewerClass ui;
	GLWidget m_pcScene;
	
	void initWindow();//Ë¢ÐÂ´°¿Ú
private slots:
	void inputPointCloud();

};

#endif // C3DVIEWER_H
