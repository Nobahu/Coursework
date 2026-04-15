/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 6.4.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStackedWidget>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralwidget;
    QStackedWidget *stackedGraphicsWidget;
    QWidget *page_0;
    QWidget *page_1;
    QPushButton *Start_pushButton;
    QWidget *widget;
    QLabel *label;
    QWidget *widget1;
    QVBoxLayout *verticalLayout;
    QLabel *label_4;
    QLabel *label_3;
    QLabel *label_2;
    QLabel *label_5;
    QLabel *label_6;
    QLabel *label_7;
    QWidget *widget2;
    QVBoxLayout *verticalLayout_2;
    QLineEdit *lineEdit;
    QLineEdit *lineEdit_2;
    QLineEdit *lineEdit_4;
    QLineEdit *lineEdit_3;
    QLineEdit *lineEdit_5;
    QLineEdit *lineEdit_6;
    QMenuBar *menubar;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName("MainWindow");
        MainWindow->resize(1280, 720);
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName("centralwidget");
        stackedGraphicsWidget = new QStackedWidget(centralwidget);
        stackedGraphicsWidget->setObjectName("stackedGraphicsWidget");
        stackedGraphicsWidget->setGeometry(QRect(720, 10, 551, 661));
        page_0 = new QWidget();
        page_0->setObjectName("page_0");
        stackedGraphicsWidget->addWidget(page_0);
        page_1 = new QWidget();
        page_1->setObjectName("page_1");
        stackedGraphicsWidget->addWidget(page_1);
        Start_pushButton = new QPushButton(centralwidget);
        Start_pushButton->setObjectName("Start_pushButton");
        Start_pushButton->setGeometry(QRect(40, 540, 181, 51));
        widget = new QWidget(centralwidget);
        widget->setObjectName("widget");
        widget->setGeometry(QRect(10, 10, 271, 291));
        label = new QLabel(widget);
        label->setObjectName("label");
        label->setGeometry(QRect(50, 10, 171, 17));
        widget1 = new QWidget(widget);
        widget1->setObjectName("widget1");
        widget1->setGeometry(QRect(20, 50, 118, 231));
        verticalLayout = new QVBoxLayout(widget1);
        verticalLayout->setObjectName("verticalLayout");
        verticalLayout->setContentsMargins(0, 0, 0, 0);
        label_4 = new QLabel(widget1);
        label_4->setObjectName("label_4");
        QFont font;
        font.setPointSize(14);
        label_4->setFont(font);

        verticalLayout->addWidget(label_4);

        label_3 = new QLabel(widget1);
        label_3->setObjectName("label_3");
        label_3->setFont(font);

        verticalLayout->addWidget(label_3);

        label_2 = new QLabel(widget1);
        label_2->setObjectName("label_2");
        label_2->setFont(font);

        verticalLayout->addWidget(label_2);

        label_5 = new QLabel(widget1);
        label_5->setObjectName("label_5");
        label_5->setFont(font);

        verticalLayout->addWidget(label_5);

        label_6 = new QLabel(widget1);
        label_6->setObjectName("label_6");
        label_6->setFont(font);

        verticalLayout->addWidget(label_6);

        label_7 = new QLabel(widget1);
        label_7->setObjectName("label_7");
        label_7->setFont(font);

        verticalLayout->addWidget(label_7);

        widget2 = new QWidget(widget);
        widget2->setObjectName("widget2");
        widget2->setGeometry(QRect(140, 50, 110, 231));
        verticalLayout_2 = new QVBoxLayout(widget2);
        verticalLayout_2->setObjectName("verticalLayout_2");
        verticalLayout_2->setContentsMargins(0, 0, 0, 0);
        lineEdit = new QLineEdit(widget2);
        lineEdit->setObjectName("lineEdit");

        verticalLayout_2->addWidget(lineEdit);

        lineEdit_2 = new QLineEdit(widget2);
        lineEdit_2->setObjectName("lineEdit_2");

        verticalLayout_2->addWidget(lineEdit_2);

        lineEdit_4 = new QLineEdit(widget2);
        lineEdit_4->setObjectName("lineEdit_4");

        verticalLayout_2->addWidget(lineEdit_4);

        lineEdit_3 = new QLineEdit(widget2);
        lineEdit_3->setObjectName("lineEdit_3");

        verticalLayout_2->addWidget(lineEdit_3);

        lineEdit_5 = new QLineEdit(widget2);
        lineEdit_5->setObjectName("lineEdit_5");

        verticalLayout_2->addWidget(lineEdit_5);

        lineEdit_6 = new QLineEdit(widget2);
        lineEdit_6->setObjectName("lineEdit_6");

        verticalLayout_2->addWidget(lineEdit_6);

        MainWindow->setCentralWidget(centralwidget);
        menubar = new QMenuBar(MainWindow);
        menubar->setObjectName("menubar");
        menubar->setGeometry(QRect(0, 0, 1280, 22));
        MainWindow->setMenuBar(menubar);
        statusbar = new QStatusBar(MainWindow);
        statusbar->setObjectName("statusbar");
        MainWindow->setStatusBar(statusbar);

        retranslateUi(MainWindow);

        stackedGraphicsWidget->setCurrentIndex(0);


        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "MainWindow", nullptr));
        Start_pushButton->setText(QCoreApplication::translate("MainWindow", "Start Simulation", nullptr));
        label->setText(QCoreApplication::translate("MainWindow", "\320\237\320\260\321\200\320\260\320\274\320\265\321\202\321\200\321\213 \320\274\320\276\320\264\320\265\320\273\320\270\321\200\320\276\320\262\320\260\320\275\320\270\321\217", nullptr));
        label_4->setText(QCoreApplication::translate("MainWindow", "\316\273", nullptr));
        label_3->setText(QCoreApplication::translate("MainWindow", "time", nullptr));
        label_2->setText(QCoreApplication::translate("MainWindow", "device_num", nullptr));
        label_5->setText(QCoreApplication::translate("MainWindow", "r_h_\316\273", nullptr));
        label_6->setText(QCoreApplication::translate("MainWindow", "\316\274", nullptr));
        label_7->setText(QCoreApplication::translate("MainWindow", "unpack_prob", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
