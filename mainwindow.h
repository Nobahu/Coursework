#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <Include/main_system.h>

#include <QMainWindow>
#include <QtCharts>
#include <QDebug>

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
    MainWindow( QWidget *parent = nullptr );

    QChart* createBarChart( const std::vector< double >& probs, const int& device_id );

    ~MainWindow();

private slots:
    void on_Start_pushButton_clicked();

    void on_PSettings_pushButton_clicked();

private:

    std::unique_ptr< MainSystem > SimSystem;
    Ui::MainWindow *ui;
    QComboBox* deviceComboBox;

    QComboBox* phasesComboBox;
    std::vector< QLineEdit* > m_phaseLineEdits;
    std::vector< QComboBox* > m_strategyComboBoxes;
    std::vector< QStackedWidget* > m_strategyParamsStack;
    std::vector< std::vector< QLineEdit* > > m_unpackParamEdits;

};
#endif // MAINWINDOW_H
