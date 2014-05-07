#include "automationviewer.h"
#include <QApplication>

int main(int argc, char *argv[])
{
	QApplication a(argc, argv);
	AutomationViewer w;
	w.showMaximized();
	return a.exec();
}
