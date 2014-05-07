#ifndef AUTOMATIONVIEWER_H
#define AUTOMATIONVIEWER_H

#include <QMainWindow>
#include "ui_automationviewer.h"
#include <QGraphicsView>
#include <QGraphicsScene>

//! AutomationViewer
	/*!
		Responsibility: Acts as a container for GraphicsView
	*/
class AutomationViewer : public QMainWindow
{
	Q_OBJECT

public:
    AutomationViewer(QWidget *parent = 0, Qt::WindowFlags flags = 0);
	~AutomationViewer();

private:
	Ui::AutomationViewerClass ui;
	QGraphicsView* m_currentView;
	QGraphicsScene* m_currentScene;
};

#endif // AUTOMATIONVIEWER_H
