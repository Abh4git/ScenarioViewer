/********************************************************************************
** Form generated from reading UI file 'automationelementsview.ui'
**
** Created: Thu Sep 19 18:51:49 2013
**      by: Qt User Interface Compiler version 4.8.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_AUTOMATIONELEMENTSVIEW_H
#define UI_AUTOMATIONELEMENTSVIEW_H

#include <QtCore/QVariant>
#include <QAction>
#include <QApplication>
#include <QButtonGroup>
#include <QHeaderView>
#include <QWidget>

QT_BEGIN_NAMESPACE

class Ui_AutomationElementsView
{
public:

    void setupUi(QWidget *AutomationElementsView)
    {
        if (AutomationElementsView->objectName().isEmpty())
            AutomationElementsView->setObjectName(QString::fromUtf8("AutomationElementsView"));
        AutomationElementsView->resize(400, 300);

        retranslateUi(AutomationElementsView);

        QMetaObject::connectSlotsByName(AutomationElementsView);
    } // setupUi

    void retranslateUi(QWidget *AutomationElementsView)
    {
        AutomationElementsView->setWindowTitle(QApplication::translate("AutomationElementsView", "AutomationElementsView", 0));
    } // retranslateUi

};

namespace Ui {
    class AutomationElementsView: public Ui_AutomationElementsView {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_AUTOMATIONELEMENTSVIEW_H
