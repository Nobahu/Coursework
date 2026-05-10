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

    void on_SSettings_pushButton_clicked();

private:

    std::unique_ptr< MainSystem > SimSystem;
    Ui::MainWindow *ui;
    QComboBox* deviceComboBox;

    /// Настройки для каждой отдельной фазы
    QComboBox* phasesComboBox;
    std::vector< QLineEdit* > m_phaseLineEdits;
    std::vector< QComboBox* > m_strategyComboBoxes;
    std::vector< QStackedWidget* > m_strategyParamsStack;
    std::vector< std::vector< QLineEdit* > > m_unpackParamEdits;

    std::vector<QComboBox*> m_serviceTypeComboBoxes;
    std::vector<std::vector<QLineEdit*>> m_serviceParamEdits;

    /// Настройки входящего потока заявок
    QComboBox* m_streamTypeComboBox;
    QStackedWidget* m_streamParamStack;
    std::vector<QLineEdit*> m_streamParamEdits;
    std::unique_ptr<IStream> m_stream;

};
#endif // MAINWINDOW_H
