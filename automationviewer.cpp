#include "automationviewer.h"
#include "automationelementsview.h"
AutomationViewer::AutomationViewer(QWidget *parent, Qt::WindowFlags flags)
	: QMainWindow(parent, flags)
{
	ui.setupUi(this);
	
	AutomationElementsView* view = new AutomationElementsView(this);
	this->setCentralWidget(view);
}

AutomationViewer::~AutomationViewer()
{

}
