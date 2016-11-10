/********************************************************************************
** Form generated from reading UI file 'testqt.ui'
**
** Created by: Qt User Interface Compiler version 5.7.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_TESTQT_H
#define UI_TESTQT_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_testQtClass
{
public:
    QWidget *centralWidget;
    QLabel *label_pic;
    QMenuBar *menuBar;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *testQtClass)
    {
        if (testQtClass->objectName().isEmpty())
            testQtClass->setObjectName(QStringLiteral("testQtClass"));
        testQtClass->resize(737, 533);
        centralWidget = new QWidget(testQtClass);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        label_pic = new QLabel(centralWidget);
        label_pic->setObjectName(QStringLiteral("label_pic"));
        label_pic->setGeometry(QRect(40, 40, 231, 141));
        testQtClass->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(testQtClass);
        menuBar->setObjectName(QStringLiteral("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 737, 21));
        testQtClass->setMenuBar(menuBar);
        mainToolBar = new QToolBar(testQtClass);
        mainToolBar->setObjectName(QStringLiteral("mainToolBar"));
        testQtClass->addToolBar(Qt::TopToolBarArea, mainToolBar);
        statusBar = new QStatusBar(testQtClass);
        statusBar->setObjectName(QStringLiteral("statusBar"));
        testQtClass->setStatusBar(statusBar);

        retranslateUi(testQtClass);

        QMetaObject::connectSlotsByName(testQtClass);
    } // setupUi

    void retranslateUi(QMainWindow *testQtClass)
    {
        testQtClass->setWindowTitle(QApplication::translate("testQtClass", "testQt", 0));
        label_pic->setText(QString());
    } // retranslateUi

};

namespace Ui {
    class testQtClass: public Ui_testQtClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_TESTQT_H
