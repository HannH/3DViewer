#include "test.h"
#include <QtWidgets/QApplication>
#include "CPointCloudScene.h"

int main(int argc, char *argv[])
{
	QApplication a(argc, argv);
	CPointCloudScene w;
	w.testFun();
	w.show();
	return a.exec();
}
