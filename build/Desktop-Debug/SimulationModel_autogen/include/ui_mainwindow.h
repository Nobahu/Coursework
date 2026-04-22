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
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStackedWidget>
#include <QtWidgets/QStatusBar>
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
    QHBoxLayout *horizontalLayout;
    QLabel *label_4;
    QLineEdit *lineEdit;
    QWidget *layoutWidget1;
    QHBoxLayout *horizontalLayout_2;
    QLabel *label_3;
    QLineEdit *lineEdit_2;
    QWidget *layoutWidget2;
    QHBoxLayout *horizontalLayout_3;
    QLabel *label_2;
    QLineEdit *lineEdit_4;
    QPushButton *PSettings_pushButton;
    QStackedWidget *PhaseStackedWidget;
    QWidget *page;
    QWidget *page_2;
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
        Start_pushButton->setGeometry(QRect(40, 370, 181, 51));
        widget = new QWidget(centralwidget);
        widget->setObjectName("widget");
        widget->setGeometry(QRect(10, 10, 271, 281));
        label = new QLabel(widget);
        label->setObjectName("label");
        label->setGeometry(QRect(50, 10, 171, 17));
        layoutWidget = new QWidget(widget);
        layoutWidget->setObjectName("layoutWidget");
        layoutWidget->setGeometry(QRect(21, 50, 231, 28));
        horizontalLayout = new QHBoxLayout(layoutWidget);
        horizontalLayout->setSpacing(110);
        horizontalLayout->setObjectName("horizontalLayout");
        horizontalLayout->setContentsMargins(0, 0, 0, 0);
        label_4 = new QLabel(layoutWidget);
        label_4->setObjectName("label_4");
        QFont font;
        font.setPointSize(14);
        label_4->setFont(font);

        horizontalLayout->addWidget(label_4);

        lineEdit = new QLineEdit(layoutWidget);
        lineEdit->setObjectName("lineEdit");

        horizontalLayout->addWidget(lineEdit);

        layoutWidget1 = new QWidget(widget);
        layoutWidget1->setObjectName("layoutWidget1");
        layoutWidget1->setGeometry(QRect(21, 110, 231, 28));
        horizontalLayout_2 = new QHBoxLayout(layoutWidget1);
        horizontalLayout_2->setSpacing(80);
        horizontalLayout_2->setObjectName("horizontalLayout_2");
        horizontalLayout_2->setContentsMargins(0, 0, 0, 0);
        label_3 = new QLabel(layoutWidget1);
        label_3->setObjectName("label_3");
        label_3->setFont(font);

        horizontalLayout_2->addWidget(label_3);

        lineEdit_2 = new QLineEdit(layoutWidget1);
        lineEdit_2->setObjectName("lineEdit_2");

        horizontalLayout_2->addWidget(lineEdit_2);

        layoutWidget2 = new QWidget(widget);
        layoutWidget2->setObjectName("layoutWidget2");
        layoutWidget2->setGeometry(QRect(21, 169, 231, 28));
        horizontalLayout_3 = new QHBoxLayout(layoutWidget2);
        horizontalLayout_3->setSpacing(15);
        horizontalLayout_3->setObjectName("horizontalLayout_3");
        horizontalLayout_3->setContentsMargins(0, 0, 0, 0);
        label_2 = new QLabel(layoutWidget2);
        label_2->setObjectName("label_2");
        label_2->setFont(font);

        horizontalLayout_3->addWidget(label_2);

        lineEdit_4 = new QLineEdit(layoutWidget2);
        lineEdit_4->setObjectName("lineEdit_4");

        horizontalLayout_3->addWidget(lineEdit_4);

        PSettings_pushButton = new QPushButton(centralwidget);
        PSettings_pushButton->setObjectName("PSettings_pushButton");
        PSettings_pushButton->setGeometry(QRect(40, 310, 181, 51));
        PhaseStackedWidget = new QStackedWidget(centralwidget);
        PhaseStackedWidget->setObjectName("PhaseStackedWidget");
        PhaseStackedWidget->setGeometry(QRect(280, 40, 300, 601));
        page = new QWidget();
        page->setObjectName("page");
        PhaseStackedWidget->addWidget(page);
        page_2 = new QWidget();
        page_2->setObjectName("page_2");
        PhaseStackedWidget->addWidget(page_2);
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
        PSettings_pushButton->setText(QCoreApplication::translate("MainWindow", "Phases settings", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
