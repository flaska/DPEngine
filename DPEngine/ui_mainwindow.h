/********************************************************************************
** Form generated from reading ui file 'mainwindow.ui'
**
** Created: Thu 1. Oct 18:44:03 2009
**      by: Qt User Interface Compiler version 4.5.0
**
** WARNING! All changes made in this file will be lost when recompiling ui file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QHeaderView>
#include <QtGui/QMainWindow>
#include <QtGui/QMenu>
#include <QtGui/QMenuBar>
#include <QtGui/QStatusBar>
#include <QtGui/QWidget>

QT_BEGIN_NAMESPACE

class Ui_DicomPresenter
{
public:
    QAction *actionOtev_t;
    QAction *actionO_Aplikaci;
    QAction *actionZobrazovan_tagy;
    QAction *actionSaveSnapshot;
    QAction *actionSaveSequence;
    QAction *actionExit;
    QAction *actionHelp;
	QAction *actionPlugins;
    QWidget *centralwidget;
    QMenuBar *menubar;
    QMenu *menuSoubor;
    QMenu *menuN_pov_da;
	QMenu *menuPlugins;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *DicomPresenter)
    {
        if (DicomPresenter->objectName().isEmpty())
            DicomPresenter->setObjectName(QString::fromUtf8("DicomPresenter"));
        DicomPresenter->resize(1024, 868);
      /*  QPalette palette;
        QBrush brush(QColor(99, 240, 165, 255));
        brush.setStyle(Qt::SolidPattern);
        palette.setBrush(QPalette::Active, QPalette::Button, brush);
        QBrush brush1(QColor(247, 255, 94, 255));
        brush1.setStyle(Qt::SolidPattern);
        palette.setBrush(QPalette::Active, QPalette::Light, brush1);
        QBrush brush2(QColor(51, 227, 57, 255));
        brush2.setStyle(Qt::SolidPattern);
        palette.setBrush(QPalette::Active, QPalette::Midlight, brush2);
        QBrush brush3(QColor(192, 255, 234, 255));
        brush3.setStyle(Qt::SolidPattern);
        palette.setBrush(QPalette::Active, QPalette::BrightText, brush3);
        QBrush brush4(QColor(102, 227, 255, 255));
        brush4.setStyle(Qt::SolidPattern);
        palette.setBrush(QPalette::Active, QPalette::Base, brush4);
        QBrush brush5(QColor(49, 240, 71, 255));
        brush5.setStyle(Qt::SolidPattern);
        palette.setBrush(QPalette::Active, QPalette::Window, brush5);
        QBrush brush6(QColor(169, 255, 112, 255));
        brush6.setStyle(Qt::SolidPattern);
        palette.setBrush(QPalette::Active, QPalette::HighlightedText, brush6);
        QBrush brush7(QColor(255, 130, 249, 255));
        brush7.setStyle(Qt::SolidPattern);
        palette.setBrush(QPalette::Active, QPalette::AlternateBase, brush7);
        QBrush brush8(QColor(72, 153, 146, 255));
        brush8.setStyle(Qt::SolidPattern);
        palette.setBrush(QPalette::Active, QPalette::NoRole, brush8);
        palette.setBrush(QPalette::Inactive, QPalette::Button, brush);
        palette.setBrush(QPalette::Inactive, QPalette::Light, brush1);
        palette.setBrush(QPalette::Inactive, QPalette::Midlight, brush2);
        palette.setBrush(QPalette::Inactive, QPalette::BrightText, brush3);
        palette.setBrush(QPalette::Inactive, QPalette::Base, brush4);
        palette.setBrush(QPalette::Inactive, QPalette::Window, brush5);
        palette.setBrush(QPalette::Inactive, QPalette::HighlightedText, brush6);
        palette.setBrush(QPalette::Inactive, QPalette::AlternateBase, brush7);
        palette.setBrush(QPalette::Inactive, QPalette::NoRole, brush8);
        palette.setBrush(QPalette::Disabled, QPalette::Button, brush);
        palette.setBrush(QPalette::Disabled, QPalette::Light, brush1);
        palette.setBrush(QPalette::Disabled, QPalette::Midlight, brush2);
        palette.setBrush(QPalette::Disabled, QPalette::BrightText, brush3);
        palette.setBrush(QPalette::Disabled, QPalette::Base, brush5);
        palette.setBrush(QPalette::Disabled, QPalette::Window, brush5);
        palette.setBrush(QPalette::Disabled, QPalette::HighlightedText, brush6);
        palette.setBrush(QPalette::Disabled, QPalette::AlternateBase, brush7);
        palette.setBrush(QPalette::Disabled, QPalette::NoRole, brush8);
        DicomPresenter->setPalette(palette);*/
        actionOtev_t = new QAction(DicomPresenter);
        actionOtev_t->setObjectName(QString::fromUtf8("actionOtev_t"));
        actionO_Aplikaci = new QAction(DicomPresenter);
        actionO_Aplikaci->setObjectName(QString::fromUtf8("actionO_Aplikaci"));
        actionZobrazovan_tagy = new QAction(DicomPresenter);
        actionZobrazovan_tagy->setObjectName(QString::fromUtf8("actionZobrazovan_tagy"));
        actionSaveSnapshot = new QAction(DicomPresenter);
        actionSaveSnapshot->setObjectName(QString::fromUtf8("actionSaveSnapshot"));
        actionSaveSequence = new QAction(DicomPresenter);
        actionSaveSequence->setObjectName(QString::fromUtf8("actionSaveSequence"));
        actionExit = new QAction(DicomPresenter);
        actionExit->setObjectName(QString::fromUtf8("actionExit"));
        actionHelp = new QAction(DicomPresenter);
        actionHelp->setObjectName(QString::fromUtf8("actionHelp"));
		actionPlugins = new QAction(DicomPresenter);
		actionPlugins->setObjectName(QString::fromUtf8("actionPlugins"));
        centralwidget = new QWidget(DicomPresenter);
        centralwidget->setObjectName(QString::fromUtf8("centralwidget"));
        DicomPresenter->setCentralWidget(centralwidget);
        menubar = new QMenuBar(DicomPresenter);
        menubar->setObjectName(QString::fromUtf8("menubar"));
        menubar->setGeometry(QRect(0, 0, 1024, 22));
        menuSoubor = new QMenu(menubar);
        menuSoubor->setObjectName(QString::fromUtf8("menuSoubor"));
        menuN_pov_da = new QMenu(menubar);
        menuN_pov_da->setObjectName(QString::fromUtf8("menuN_pov_da"));
		menuPlugins = new QMenu(menubar);
        menuPlugins->setObjectName(QString::fromUtf8("menuPlugins"));
        DicomPresenter->setMenuBar(menubar);
        statusbar = new QStatusBar(DicomPresenter);
        statusbar->setObjectName(QString::fromUtf8("statusbar"));
        DicomPresenter->setStatusBar(statusbar);

        menubar->addAction(menuSoubor->menuAction());
        menubar->addAction(menuN_pov_da->menuAction());
		menubar->addAction(menuPlugins->menuAction());
        menuSoubor->addAction(actionOtev_t);
        menuSoubor->addAction(actionSaveSnapshot);
        menuSoubor->addAction(actionSaveSequence);
        menuSoubor->addAction(actionExit);
		menuPlugins->addAction(actionPlugins);
        menuN_pov_da->addAction(actionO_Aplikaci);

        retranslateUi(DicomPresenter);

        QMetaObject::connectSlotsByName(DicomPresenter);
    } // setupUi

    void retranslateUi(QMainWindow *DicomPresenter)
    {
        DicomPresenter->setWindowTitle(QApplication::translate("DicomPresenter", "DicomPresenter", 0, QApplication::UnicodeUTF8));
        actionOtev_t->setText(QApplication::translate("DicomPresenter", "Open...", 0, QApplication::UnicodeUTF8));
        actionO_Aplikaci->setText(QApplication::translate("DicomPresenter", "About", 0, QApplication::UnicodeUTF8));
        actionZobrazovan_tagy->setText(QApplication::translate("DicomPresenter", "Zobrazovan\303\251 tagy", 0, QApplication::UnicodeUTF8));
        actionSaveSnapshot->setText(QApplication::translate("DicomPresenter", "Save workspace as bitmap...", 0, QApplication::UnicodeUTF8));
        actionSaveSequence->setText(QApplication::translate("DicomPresenter", "Save workspace animation...", 0, QApplication::UnicodeUTF8));
        actionExit->setText(QApplication::translate("DicomPresenter", "Exit", 0, QApplication::UnicodeUTF8));
        actionHelp->setText(QApplication::translate("DicomPresenter", "Help", 0, QApplication::UnicodeUTF8));
		actionPlugins->setText(QApplication::translate("DicomPresenter", "Image Segmentation", 0, QApplication::UnicodeUTF8));
        menuSoubor->setTitle(QApplication::translate("DicomPresenter", "File", 0, QApplication::UnicodeUTF8));
        menuN_pov_da->setTitle(QApplication::translate("DicomPresenter", "Help", 0, QApplication::UnicodeUTF8));
		menuPlugins->setTitle(QApplication::translate("DicomPresenter", "Plugins", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class DicomPresenter: public Ui_DicomPresenter {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
