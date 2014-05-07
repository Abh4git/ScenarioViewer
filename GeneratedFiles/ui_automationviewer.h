/********************************************************************************
** Form generated from reading UI file 'automationviewer.ui'
**
** Created: Thu Sep 19 18:51:45 2013
**      by: Qt User Interface Compiler version 4.8.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_AUTOMATIONVIEWER_H
#define UI_AUTOMATIONVIEWER_H

#include <QtCore/QVariant>
#include <QAction>
#include <QApplication>
#include <QButtonGroup>
#include <QHeaderView>
#include <QMainWindow>
#include <QMenuBar>
#include <QStatusBar>
#include <QToolBar>
#include <QWidget>

QT_BEGIN_NAMESPACE

class Ui_AutomationViewerClass
{
public:
    QMenuBar *menuBar;
    QToolBar *mainToolBar;
    QWidget *centralWidget;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *AutomationViewerClass)
    {
        if (AutomationViewerClass->objectName().isEmpty())
            AutomationViewerClass->setObjectName(QString::fromUtf8("AutomationViewerClass"));
        AutomationViewerClass->resize(600, 400);
        menuBar = new QMenuBar(AutomationViewerClass);
        menuBar->setObjectName(QString::fromUtf8("menuBar"));
        AutomationViewerClass->setMenuBar(menuBar);
        mainToolBar = new QToolBar(AutomationViewerClass);
        mainToolBar->setObjectName(QString::fromUtf8("mainToolBar"));
        AutomationViewerClass->addToolBar(mainToolBar);
        centralWidget = new QWidget(AutomationViewerClass);
        centralWidget->setObjectName(QString::fromUtf8("centralWidget"));
        AutomationViewerClass->setCentralWidget(centralWidget);
        statusBar = new QStatusBar(AutomationViewerClass);
        statusBar->setObjectName(QString::fromUtf8("statusBar"));
        AutomationViewerClass->setStatusBar(statusBar);

        retranslateUi(AutomationViewerClass);

        QMetaObject::connectSlotsByName(AutomationViewerClass);
    } // setupUi

    void retranslateUi(QMainWindow *AutomationViewerClass)
    {
        AutomationViewerClass->setWindowTitle(QApplication::translate("AutomationViewerClass", "ScenarioViewer", 0));
    } // retranslateUi

};

namespace Ui {
    class AutomationViewerClass: public Ui_AutomationViewerClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_AUTOMATIONVIEWER_H
