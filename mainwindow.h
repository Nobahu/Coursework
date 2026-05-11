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


    void CheckInputParameters(const int device_num, const double time)
    {
        if ( device_num <= 0 )
        {
            throw std::invalid_argument( "Number of devices can't be less than 1" );
        }
        if( time <= 0.0 )
        {
            throw std::invalid_argument( "Modelling time can't be equal 0" );
        }
    }

    void StreamStrategyChoose(std::unique_ptr< IStream >& stream, const int streamType)
    {
        switch ( streamType )
        {
        case 0:
        {
            double lambda = m_streamParamEdits[0]->text().toDouble();
            if ( lambda <= 0 )
            {
                throw std::invalid_argument("Wrong stream parameter (lambda)");
            }
            stream = std::make_unique<PoissonStream>(lambda);
            break;
        }
        case 1:
        {
            double k = m_streamParamEdits[1]->text().toDouble();
            double theta = m_streamParamEdits[2]->text().toDouble();
            if ( k <= 0 || theta <= 0 )
            {
                throw std::invalid_argument("Wrong stream parameter (k or theta)");
            }
            stream = std::make_unique<GammaStream>(k, theta);
            break;
        }
        default:
            throw std::invalid_argument("Wrong stream strategy type");
        }
    }

    void ServiceStrategyChoose(std::vector<std::unique_ptr<ProcessingDevice>>& devices, const int serviceType, const int deviceIndex )
    {
        switch ( serviceType )
        {
        case 0:
        {
            double mu = m_serviceParamEdits[deviceIndex][0]->text().toDouble();
            if ( mu <= 0 )
            {
                throw std::invalid_argument("Wrong service parameter (mu)");
            }
            devices.push_back(std::make_unique<ExponentialProcessingDevice>(mu));
            break;
        }
        case 1:
        {
            double k = m_serviceParamEdits[deviceIndex][1]->text().toDouble();
            double theta = m_serviceParamEdits[deviceIndex][2]->text().toDouble();
            if ( k <= 0 || theta <= 0 )
            {
                throw std::invalid_argument("Wrong service parameter (k or theta)");
            }
            devices.push_back(std::make_unique<GammaProcessingDevice>(k, theta));
            break;
        }
        default:
            throw std::invalid_argument("Wrong service strategy type");
        }
    }

    void UnpackStrategyChoose( std::vector<std::unique_ptr<IUnpackStrategy>>& unpack_strategies, const int unpackType, const int deviceIndex )
    {
        switch ( unpackType )
        {
        case 0:
        {
            QStackedWidget* stack = m_strategyParamsStack[deviceIndex];
            QWidget* poissonPage = stack->widget(0);
            QLineEdit* lambdaEdit = poissonPage->findChild<QLineEdit*>();
            double lambda_unpack = lambdaEdit->text().toDouble();
            if ( lambda_unpack <= 0 )
            {
                throw std::invalid_argument("Wrong unpack parameter ( lambda )");
            }
            unpack_strategies.push_back(std::make_unique<PoissonUnpackStrategy>(lambda_unpack));
            break;
        }
        case 1:
        {
            std::vector<double> probs;
            double sum = 0;
            for (QLineEdit* edit : m_unpackParamEdits[deviceIndex])
            {
                sum += edit->text().toDouble();
                probs.push_back(edit->text().toDouble());
            }
            if ( abs( sum - 1.0 ) > 1e-6 )
            {
                throw std::invalid_argument("Wrong unpack parameter ( Sum of probabilities must equal 1 )");
            }
            unpack_strategies.push_back(std::make_unique<DiscreteUnpackStrategy>(probs));
            break;
        }
        case 2:
        {
            QStackedWidget* stack = m_strategyParamsStack[deviceIndex];
            QWidget* gammaPage = stack->widget(2);
            QList<QLineEdit*> edits = gammaPage->findChildren<QLineEdit*>();
            double a = edits[0]->text().toDouble();
            double b = edits[1]->text().toDouble();
            if ( a < 0 || b < a )
            {
                throw std::invalid_argument("Wrong unpack parameter ( a < 0 or b < a )");
            }
            unpack_strategies.push_back(std::make_unique<DiscreteUniformUnpackStrategy>(a, b));
            break;
        }
        default:
            throw std::invalid_argument("Wrong unpacking strategy type");
        }
    }

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
