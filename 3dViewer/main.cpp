
#include "c3dviewer.h"
#include <QtWidgets/QApplication>
#include <Qt3DCore/qcamera.h>

int main(int argc, char *argv[])
{
	QApplication a(argc, argv);
	C3DViewer w;
	w.show();
	return a.exec();
}
