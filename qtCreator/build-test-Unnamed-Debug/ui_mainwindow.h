/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 4.8.6
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>
#include <QtGui/QLineEdit>
#include <QtGui/QMainWindow>
#include <QtGui/QMenu>
#include <QtGui/QMenuBar>
#include <QtGui/QPushButton>
#include <QtGui/QStatusBar>
#include <QtGui/QToolBar>
#include <QtGui/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QAction *actionMarvin_Elz;
    QWidget *centralWidget;
    QPushButton *b_reset_C;
    QPushButton *b_reset_B;
    QLineEdit *l_b_ist;
    QLineEdit *l_c_ist;
    QLabel *label;
    QLabel *label_2;
    QPushButton *b_B_up;
    QPushButton *b_B_down;
    QPushButton *b_C_up;
    QPushButton *b_C_down;
    QPushButton *Mani_up;
    QPushButton *Mani_down;
    QLabel *label_3;
    QLineEdit *l_b_soll;
    QLineEdit *l_c_soll;
    QLabel *label_4;
    QLabel *label_5;
    QMenuBar *menuBar;
    QMenu *menuManipulator_Steuerung;
    QMenu *menuAbout;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QString::fromUtf8("MainWindow"));
        MainWindow->resize(729, 558);
        actionMarvin_Elz = new QAction(MainWindow);
        actionMarvin_Elz->setObjectName(QString::fromUtf8("actionMarvin_Elz"));
        centralWidget = new QWidget(MainWindow);
        centralWidget->setObjectName(QString::fromUtf8("centralWidget"));
        b_reset_C = new QPushButton(centralWidget);
        b_reset_C->setObjectName(QString::fromUtf8("b_reset_C"));
        b_reset_C->setGeometry(QRect(590, 280, 81, 41));
        b_reset_B = new QPushButton(centralWidget);
        b_reset_B->setObjectName(QString::fromUtf8("b_reset_B"));
        b_reset_B->setGeometry(QRect(500, 280, 81, 41));
        l_b_ist = new QLineEdit(centralWidget);
        l_b_ist->setObjectName(QString::fromUtf8("l_b_ist"));
        l_b_ist->setGeometry(QRect(500, 240, 81, 21));
        QFont font;
        font.setPointSize(12);
        l_b_ist->setFont(font);
        l_c_ist = new QLineEdit(centralWidget);
        l_c_ist->setObjectName(QString::fromUtf8("l_c_ist"));
        l_c_ist->setGeometry(QRect(590, 240, 81, 21));
        l_c_ist->setFont(font);
        label = new QLabel(centralWidget);
        label->setObjectName(QString::fromUtf8("label"));
        label->setGeometry(QRect(510, 180, 71, 20));
        label->setFont(font);
        label_2 = new QLabel(centralWidget);
        label_2->setObjectName(QString::fromUtf8("label_2"));
        label_2->setGeometry(QRect(600, 180, 71, 20));
        label_2->setFont(font);
        b_B_up = new QPushButton(centralWidget);
        b_B_up->setObjectName(QString::fromUtf8("b_B_up"));
        b_B_up->setGeometry(QRect(500, 340, 81, 41));
        b_B_down = new QPushButton(centralWidget);
        b_B_down->setObjectName(QString::fromUtf8("b_B_down"));
        b_B_down->setGeometry(QRect(500, 390, 81, 41));
        b_C_up = new QPushButton(centralWidget);
        b_C_up->setObjectName(QString::fromUtf8("b_C_up"));
        b_C_up->setGeometry(QRect(590, 340, 81, 41));
        b_C_down = new QPushButton(centralWidget);
        b_C_down->setObjectName(QString::fromUtf8("b_C_down"));
        b_C_down->setGeometry(QRect(590, 390, 81, 41));
        Mani_up = new QPushButton(centralWidget);
        Mani_up->setObjectName(QString::fromUtf8("Mani_up"));
        Mani_up->setGeometry(QRect(360, 340, 81, 41));
        Mani_down = new QPushButton(centralWidget);
        Mani_down->setObjectName(QString::fromUtf8("Mani_down"));
        Mani_down->setGeometry(QRect(360, 390, 81, 41));
        label_3 = new QLabel(centralWidget);
        label_3->setObjectName(QString::fromUtf8("label_3"));
        label_3->setGeometry(QRect(460, 240, 31, 20));
        label_3->setFont(font);
        l_b_soll = new QLineEdit(centralWidget);
        l_b_soll->setObjectName(QString::fromUtf8("l_b_soll"));
        l_b_soll->setGeometry(QRect(500, 210, 81, 22));
        l_b_soll->setFont(font);
        l_c_soll = new QLineEdit(centralWidget);
        l_c_soll->setObjectName(QString::fromUtf8("l_c_soll"));
        l_c_soll->setGeometry(QRect(590, 210, 81, 22));
        l_c_soll->setFont(font);
        label_4 = new QLabel(centralWidget);
        label_4->setObjectName(QString::fromUtf8("label_4"));
        label_4->setGeometry(QRect(460, 210, 31, 21));
        label_4->setFont(font);
        label_5 = new QLabel(centralWidget);
        label_5->setObjectName(QString::fromUtf8("label_5"));
        label_5->setGeometry(QRect(380, 310, 41, 16));
        label_5->setFont(font);
        MainWindow->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(MainWindow);
        menuBar->setObjectName(QString::fromUtf8("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 729, 19));
        menuManipulator_Steuerung = new QMenu(menuBar);
        menuManipulator_Steuerung->setObjectName(QString::fromUtf8("menuManipulator_Steuerung"));
        menuAbout = new QMenu(menuBar);
        menuAbout->setObjectName(QString::fromUtf8("menuAbout"));
        MainWindow->setMenuBar(menuBar);
        mainToolBar = new QToolBar(MainWindow);
        mainToolBar->setObjectName(QString::fromUtf8("mainToolBar"));
        MainWindow->addToolBar(Qt::TopToolBarArea, mainToolBar);
        statusBar = new QStatusBar(MainWindow);
        statusBar->setObjectName(QString::fromUtf8("statusBar"));
        MainWindow->setStatusBar(statusBar);

        menuBar->addAction(menuManipulator_Steuerung->menuAction());
        menuBar->addAction(menuAbout->menuAction());
        menuAbout->addAction(actionMarvin_Elz);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "Manipulator - Steuerung", 0, QApplication::UnicodeUTF8));
        actionMarvin_Elz->setText(QApplication::translate("MainWindow", "Marvin Elz", 0, QApplication::UnicodeUTF8));
        b_reset_C->setText(QApplication::translate("MainWindow", "Set", 0, QApplication::UnicodeUTF8));
        b_reset_B->setText(QApplication::translate("MainWindow", "Set", 0, QApplication::UnicodeUTF8));
        label->setText(QApplication::translate("MainWindow", "Winkel B", 0, QApplication::UnicodeUTF8));
        label_2->setText(QApplication::translate("MainWindow", "Winkel C", 0, QApplication::UnicodeUTF8));
        b_B_up->setText(QApplication::translate("MainWindow", "UP", 0, QApplication::UnicodeUTF8));
        b_B_down->setText(QApplication::translate("MainWindow", "DOWN", 0, QApplication::UnicodeUTF8));
        b_C_up->setText(QApplication::translate("MainWindow", "UP", 0, QApplication::UnicodeUTF8));
        b_C_down->setText(QApplication::translate("MainWindow", "DOWN", 0, QApplication::UnicodeUTF8));
        Mani_up->setText(QApplication::translate("MainWindow", "UP", 0, QApplication::UnicodeUTF8));
        Mani_down->setText(QApplication::translate("MainWindow", "DOWN", 0, QApplication::UnicodeUTF8));
        label_3->setText(QApplication::translate("MainWindow", "Ist", 0, QApplication::UnicodeUTF8));
        label_4->setText(QApplication::translate("MainWindow", "Soll", 0, QApplication::UnicodeUTF8));
        label_5->setText(QApplication::translate("MainWindow", "Stift", 0, QApplication::UnicodeUTF8));
        menuManipulator_Steuerung->setTitle(QApplication::translate("MainWindow", "Datei", 0, QApplication::UnicodeUTF8));
        menuAbout->setTitle(QApplication::translate("MainWindow", "About", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
