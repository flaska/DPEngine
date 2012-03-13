/********************************************************************************
** Form generated from reading UI file 'dpengine.ui'
**
** Created: Mon Mar 12 21:55:18 2012
**      by: Qt User Interface Compiler version 4.7.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_DPENGINE_H
#define UI_DPENGINE_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QHeaderView>
#include <QtGui/QMainWindow>
#include <QtGui/QMenuBar>
#include <QtGui/QStatusBar>
#include <QtGui/QToolBar>
#include <QtGui/QWidget>

QT_BEGIN_NAMESPACE

class Ui_DPEngineClass
{
public:
    QMenuBar *menuBar;
    QToolBar *mainToolBar;
    QWidget *centralWidget;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *DPEngineClass)
    {
        if (DPEngineClass->objectName().isEmpty())
            DPEngineClass->setObjectName(QString::fromUtf8("DPEngineClass"));
        DPEngineClass->resize(600, 400);
        menuBar = new QMenuBar(DPEngineClass);
        menuBar->setObjectName(QString::fromUtf8("menuBar"));
        DPEngineClass->setMenuBar(menuBar);
        mainToolBar = new QToolBar(DPEngineClass);
        mainToolBar->setObjectName(QString::fromUtf8("mainToolBar"));
        DPEngineClass->addToolBar(mainToolBar);
        centralWidget = new QWidget(DPEngineClass);
        centralWidget->setObjectName(QString::fromUtf8("centralWidget"));
        DPEngineClass->setCentralWidget(centralWidget);
        statusBar = new QStatusBar(DPEngineClass);
        statusBar->setObjectName(QString::fromUtf8("statusBar"));
        DPEngineClass->setStatusBar(statusBar);

        retranslateUi(DPEngineClass);

        QMetaObject::connectSlotsByName(DPEngineClass);
    } // setupUi

    void retranslateUi(QMainWindow *DPEngineClass)
    {
        DPEngineClass->setWindowTitle(QApplication::translate("DPEngineClass", "DPEngine", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class DPEngineClass: public Ui_DPEngineClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_DPENGINE_H
