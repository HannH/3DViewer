/********************************************************************************
** Form generated from reading UI file 'c3dviewer.ui'
**
** Created by: Qt User Interface Compiler version 5.6.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_C3DVIEWER_H
#define UI_C3DVIEWER_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenu>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_C3DViewerClass
{
public:
    QAction *actionDakai;
    QWidget *centralWidget;
    QVBoxLayout *verticalLayout_2;
    QVBoxLayout *verticalLayout;
    QMenuBar *menuBar;
    QMenu *menu;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *C3DViewerClass)
    {
        if (C3DViewerClass->objectName().isEmpty())
            C3DViewerClass->setObjectName(QStringLiteral("C3DViewerClass"));
        C3DViewerClass->resize(663, 512);
        actionDakai = new QAction(C3DViewerClass);
        actionDakai->setObjectName(QStringLiteral("actionDakai"));
        centralWidget = new QWidget(C3DViewerClass);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        verticalLayout_2 = new QVBoxLayout(centralWidget);
        verticalLayout_2->setSpacing(6);
        verticalLayout_2->setContentsMargins(11, 11, 11, 11);
        verticalLayout_2->setObjectName(QStringLiteral("verticalLayout_2"));
        verticalLayout = new QVBoxLayout();
        verticalLayout->setSpacing(6);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));

        verticalLayout_2->addLayout(verticalLayout);

        C3DViewerClass->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(C3DViewerClass);
        menuBar->setObjectName(QStringLiteral("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 663, 27));
        menu = new QMenu(menuBar);
        menu->setObjectName(QStringLiteral("menu"));
        C3DViewerClass->setMenuBar(menuBar);
        mainToolBar = new QToolBar(C3DViewerClass);
        mainToolBar->setObjectName(QStringLiteral("mainToolBar"));
        C3DViewerClass->addToolBar(Qt::TopToolBarArea, mainToolBar);
        statusBar = new QStatusBar(C3DViewerClass);
        statusBar->setObjectName(QStringLiteral("statusBar"));
        C3DViewerClass->setStatusBar(statusBar);

        menuBar->addAction(menu->menuAction());
        menu->addAction(actionDakai);

        retranslateUi(C3DViewerClass);
        QObject::connect(actionDakai, SIGNAL(triggered()), C3DViewerClass, SLOT(inputPointCloud()));

        QMetaObject::connectSlotsByName(C3DViewerClass);
    } // setupUi

    void retranslateUi(QMainWindow *C3DViewerClass)
    {
        C3DViewerClass->setWindowTitle(QApplication::translate("C3DViewerClass", "C3DViewer", 0));
        actionDakai->setText(QApplication::translate("C3DViewerClass", "\346\211\223\345\274\200", 0));
        menu->setTitle(QApplication::translate("C3DViewerClass", "\350\217\234\345\215\225", 0));
    } // retranslateUi

};

namespace Ui {
    class C3DViewerClass: public Ui_C3DViewerClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_C3DVIEWER_H
