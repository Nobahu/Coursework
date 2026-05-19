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
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralwidget;
    QPushButton *Start_pushButton;
    QWidget *widget;
    QLabel *label;
    QLabel *label_3;
    QLineEdit *lineEdit_2;
    QLabel *label_2;
    QLineEdit *lineEdit_4;
    QLineEdit *lineEdit_5;
    QLabel *label_5;
    QPushButton *PSettings_pushButton;
    QStackedWidget *PhaseStackedWidget;
    QWidget *page;
    QWidget *page_2;
    QStackedWidget *StreamStackedWidget;
    QWidget *page_3;
    QWidget *page_4;
    QPushButton *SSettings_pushButton;
    QMenuBar *menubar;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName("MainWindow");
        MainWindow->resize(728, 720);
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName("centralwidget");
        Start_pushButton = new QPushButton(centralwidget);
        Start_pushButton->setObjectName("Start_pushButton");
        Start_pushButton->setGeometry(QRect(50, 480, 181, 51));
        widget = new QWidget(centralwidget);
        widget->setObjectName("widget");
        widget->setGeometry(QRect(10, 10, 271, 331));
        label = new QLabel(widget);
        label->setObjectName("label");
        label->setGeometry(QRect(5, 10, 261, 20));
        QFont font;
        font.setPointSize(14);
        label->setFont(font);
        label_3 = new QLabel(widget);
        label_3->setObjectName("label_3");
        label_3->setGeometry(QRect(0, 60, 271, 26));
        QFont font1;
        font1.setPointSize(12);
        label_3->setFont(font1);
        label_3->setLayoutDirection(Qt::LeftToRight);
        label_3->setFrameShape(QFrame::NoFrame);
        label_3->setAlignment(Qt::AlignCenter);
        lineEdit_2 = new QLineEdit(widget);
        lineEdit_2->setObjectName("lineEdit_2");
        lineEdit_2->setEnabled(true);
        lineEdit_2->setGeometry(QRect(80, 100, 111, 25));
        label_2 = new QLabel(widget);
        label_2->setObjectName("label_2");
        label_2->setGeometry(QRect(0, 140, 271, 22));
        label_2->setFont(font1);
        label_2->setAlignment(Qt::AlignCenter);
        lineEdit_4 = new QLineEdit(widget);
        lineEdit_4->setObjectName("lineEdit_4");
        lineEdit_4->setGeometry(QRect(80, 180, 111, 25));
        lineEdit_5 = new QLineEdit(widget);
        lineEdit_5->setObjectName("lineEdit_5");
        lineEdit_5->setGeometry(QRect(80, 250, 108, 25));
        label_5 = new QLabel(widget);
        label_5->setObjectName("label_5");
        label_5->setGeometry(QRect(5, 220, 261, 22));
        label_5->setFont(font1);
        label_5->setAlignment(Qt::AlignCenter);
        PSettings_pushButton = new QPushButton(centralwidget);
        PSettings_pushButton->setObjectName("PSettings_pushButton");
        PSettings_pushButton->setGeometry(QRect(30, 420, 221, 51));
        PhaseStackedWidget = new QStackedWidget(centralwidget);
        PhaseStackedWidget->setObjectName("PhaseStackedWidget");
        PhaseStackedWidget->setGeometry(QRect(330, 40, 300, 411));
        page = new QWidget();
        page->setObjectName("page");
        PhaseStackedWidget->addWidget(page);
        page_2 = new QWidget();
        page_2->setObjectName("page_2");
        PhaseStackedWidget->addWidget(page_2);
        StreamStackedWidget = new QStackedWidget(centralwidget);
        StreamStackedWidget->setObjectName("StreamStackedWidget");
        StreamStackedWidget->setGeometry(QRect(330, 460, 301, 201));
        page_3 = new QWidget();
        page_3->setObjectName("page_3");
        StreamStackedWidget->addWidget(page_3);
        page_4 = new QWidget();
        page_4->setObjectName("page_4");
        StreamStackedWidget->addWidget(page_4);
        SSettings_pushButton = new QPushButton(centralwidget);
        SSettings_pushButton->setObjectName("SSettings_pushButton");
        SSettings_pushButton->setGeometry(QRect(30, 360, 221, 51));
        MainWindow->setCentralWidget(centralwidget);
        menubar = new QMenuBar(MainWindow);
        menubar->setObjectName("menubar");
        menubar->setGeometry(QRect(0, 0, 728, 22));
        MainWindow->setMenuBar(menubar);
        statusbar = new QStatusBar(MainWindow);
        statusbar->setObjectName("statusbar");
        MainWindow->setStatusBar(statusbar);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "MainWindow", nullptr));
        Start_pushButton->setText(QCoreApplication::translate("MainWindow", "\320\235\320\260\321\207\320\260\321\202\321\214 \320\274\320\276\320\264\320\265\320\273\320\270\321\200\320\276\320\262\320\260\320\275\320\270\320\265", nullptr));
        label->setText(QCoreApplication::translate("MainWindow", "\320\237\320\260\321\200\320\260\320\274\320\265\321\202\321\200\321\213 \320\274\320\276\320\264\320\265\320\273\320\270\321\200\320\276\320\262\320\260\320\275\320\270\321\217", nullptr));
        label_3->setText(QCoreApplication::translate("MainWindow", "\320\222\321\200\320\265\320\274\321\217 \320\274\320\276\320\264\320\265\320\273\320\270\321\200\320\276\320\262\320\260\320\275\320\270\321\217", nullptr));
        label_2->setText(QCoreApplication::translate("MainWindow", "\320\232\320\276\320\273\320\270\321\207\320\265\321\201\321\202\320\262\320\276 \321\204\320\260\320\267", nullptr));
        label_5->setText(QCoreApplication::translate("MainWindow", "seed", nullptr));
        PSettings_pushButton->setText(QCoreApplication::translate("MainWindow", "\320\235\320\260\321\201\321\202\321\200\320\276\320\271\320\272\320\260 \321\204\320\260\320\267 \320\276\320\261\321\201\320\273\321\203\320\266\320\270\320\262\320\260\320\275\320\270\321\217", nullptr));
        SSettings_pushButton->setText(QCoreApplication::translate("MainWindow", "\320\235\320\260\321\201\321\202\321\200\320\276\320\271\320\272\320\260 \320\262\321\205\320\276\320\264\321\217\321\211\320\265\320\263\320\276 \320\277\320\276\321\202\320\276\320\272\320\260", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
