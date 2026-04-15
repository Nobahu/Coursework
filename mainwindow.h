#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <Include/main_system.h>

#include <QMainWindow>
#include <QtCharts>

#include <iostream>
#include <memory>

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);

    QChart* createBarChart(const std::vector<double>& probs, const int& device_id);

    ~MainWindow();

private slots:
    void on_Start_pushButton_clicked();

    void on_stackedGraphicsWidget_currentChanged(int index);

private:

    MainSystem SimSystem;
    Ui::MainWindow *ui;
    QComboBox* deviceComboBox;
};
#endif // MAINWINDOW_H
