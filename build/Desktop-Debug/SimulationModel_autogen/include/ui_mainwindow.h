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
    QWidget *layoutWidget;
    QVBoxLayout *verticalLayout;
    QLabel *label_4;
    QLabel *label_3;
    QLabel *label_2;
    QLabel *label_5;
    QLabel *label_6;
    QLabel *label_7;
    QWidget *layoutWidget1;
    QVBoxLayout *verticalLayout_2;
    QLineEdit *lambdaLineEdit;
    QLineEdit *timeLineEdit;
    QLineEdit *deviceNumLineEdit;
    QLineEdit *rhLambdaLineEdit;
    QLineEdit *muLineEdit;
    QLineEdit *unpackProbLineEdit;
    QMenuBar *menubar;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName("MainWindow");
        MainWindow->resize(1280, 756);
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName("centralwidget");
        stackedGraphicsWidget = new QStackedWidget(centralwidget);
        stackedGraphicsWidget->setObjectName("stackedGraphicsWidget");
        stackedGraphicsWidget->setGeometry(QRect(720, 10, 551, 681));
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
        layoutWidget = new QWidget(widget);
        layoutWidget->setObjectName("layoutWidget");
        layoutWidget->setGeometry(QRect(20, 50, 118, 231));
        verticalLayout = new QVBoxLayout(layoutWidget);
        verticalLayout->setObjectName("verticalLayout");
        verticalLayout->setContentsMargins(0, 0, 0, 0);
        label_4 = new QLabel(layoutWidget);
        label_4->setObjectName("label_4");
        QFont font;
        font.setPointSize(14);
        label_4->setFont(font);

        verticalLayout->addWidget(label_4);

        label_3 = new QLabel(layoutWidget);
        label_3->setObjectName("label_3");
        label_3->setFont(font);

        verticalLayout->addWidget(label_3);

        label_2 = new QLabel(layoutWidget);
        label_2->setObjectName("label_2");
        label_2->setFont(font);

        verticalLayout->addWidget(label_2);

        label_5 = new QLabel(layoutWidget);
        label_5->setObjectName("label_5");
        label_5->setFont(font);

        verticalLayout->addWidget(label_5);

        label_6 = new QLabel(layoutWidget);
        label_6->setObjectName("label_6");
        label_6->setFont(font);

        verticalLayout->addWidget(label_6);

        label_7 = new QLabel(layoutWidget);
        label_7->setObjectName("label_7");
        label_7->setFont(font);

        verticalLayout->addWidget(label_7);

        layoutWidget1 = new QWidget(widget);
        layoutWidget1->setObjectName("layoutWidget1");
        layoutWidget1->setGeometry(QRect(140, 50, 110, 231));
        verticalLayout_2 = new QVBoxLayout(layoutWidget1);
        verticalLayout_2->setObjectName("verticalLayout_2");
        verticalLayout_2->setContentsMargins(0, 0, 0, 0);
        lambdaLineEdit = new QLineEdit(layoutWidget1);
        lambdaLineEdit->setObjectName("lambdaLineEdit");

        verticalLayout_2->addWidget(lambdaLineEdit);

        timeLineEdit = new QLineEdit(layoutWidget1);
        timeLineEdit->setObjectName("timeLineEdit");

        verticalLayout_2->addWidget(timeLineEdit);

        deviceNumLineEdit = new QLineEdit(layoutWidget1);
        deviceNumLineEdit->setObjectName("deviceNumLineEdit");

        verticalLayout_2->addWidget(deviceNumLineEdit);

        rhLambdaLineEdit = new QLineEdit(layoutWidget1);
        rhLambdaLineEdit->setObjectName("rhLambdaLineEdit");

        verticalLayout_2->addWidget(rhLambdaLineEdit);

        muLineEdit = new QLineEdit(layoutWidget1);
        muLineEdit->setObjectName("muLineEdit");

        verticalLayout_2->addWidget(muLineEdit);

        unpackProbLineEdit = new QLineEdit(layoutWidget1);
        unpackProbLineEdit->setObjectName("unpackProbLineEdit");

        verticalLayout_2->addWidget(unpackProbLineEdit);

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
