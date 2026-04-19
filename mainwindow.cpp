#include "mainwindow.h"
#include "./ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    deviceComboBox = new QComboBox(ui->centralwidget);
    deviceComboBox->setGeometry(720, 671, 551, 30); // x, y, width, height
    deviceComboBox->setObjectName("deviceComboBox");
    deviceComboBox->setFocusPolicy(Qt::NoFocus);    // чтобы не мешал кнопкам

    connect(deviceComboBox, QOverload<int>::of(&QComboBox::currentIndexChanged),
            ui->stackedGraphicsWidget, &QStackedWidget::setCurrentIndex);
}

MainWindow::~MainWindow()
{
    delete ui;
}

QChart* MainWindow::createBarChart(const std::vector<double>& probs, const int& device_id)
{
    if (probs.empty()) return nullptr;

    QBarSeries* series = new QBarSeries();
    QBarSet* barSet = new QBarSet(QString("device %1").arg(device_id));
    QStringList categories;

    for (int i = 0; i < probs.size(); ++i) {
        barSet->append(probs[i]);  // вероятность как высота столбца
        categories << QString::number(i);   // подпись оси X
    }

    series->append(barSet);

    QChart* barChart = new QChart();
    barChart->addSeries(series);
    barChart->setTitle(QString("Распределение числа заявок (Device %1)").arg(device_id));
    barChart->setAnimationOptions(QChart::SeriesAnimations);

    QBarCategoryAxis *axisX = new QBarCategoryAxis();
    axisX->append(categories);
    axisX->setTitleText("Число заявок в устройстве");
    barChart->addAxis(axisX, Qt::AlignBottom);
    series->attachAxis(axisX);

    QValueAxis *axisY = new QValueAxis();
    axisY->setTitleText("Вероятность");
    axisY->setRange(0.0, 1.0);
    axisY->setLabelFormat("%.2f");
    barChart->addAxis(axisY, Qt::AlignLeft);
    series->attachAxis(axisY);

    return barChart;
}

void MainWindow::on_Start_pushButton_clicked()
{
    int device_num = ui->lineEdit_4->text().toInt();
    double time = ui->lineEdit_2->text().toDouble();
    double lambda = ui->lineEdit->text().toDouble();
    double r_h_lambda = ui->lineEdit_3->text().toDouble();
    double mu = ui->lineEdit_5->text().toDouble();

    SimSystem = std::make_unique<MainSystem>(device_num, time, lambda, r_h_lambda, mu);

    while (ui->stackedGraphicsWidget->count() > 0) {
        QWidget* page = ui->stackedGraphicsWidget->widget(0);
        ui->stackedGraphicsWidget->removeWidget(page);
        delete page;
    }
    deviceComboBox->clear();

    SimSystem->RunImmitation();

    std::vector<std::vector<double>> samples = SimSystem->GetAllProbabilityDistributions();

    ///Отладочная инфа
    // for(size_t i = 0; i < samples.size();i++)
    // {
    //     std::cout << "Инфа по девайсу " << i <<  '\n';
    //     for(size_t j = 0; j < samples[i].size();j++)
    //     {
    //         std::cout << samples[i][j] << " ";
    //     }
    //     std::cout << '\n';
    // }

    std::vector<QChart*> charts;

    for (size_t i = 0; i < samples.size(); ++i) {
        if (!samples[i].empty()) {
            QChart* chart = createBarChart(samples[i], static_cast<int>(i));
            auto* view = new QChartView(chart);
            view->setRenderHint(QPainter::Antialiasing);
            view->setMinimumHeight(300);

            ui->stackedGraphicsWidget->addWidget(view);               // Добавляем страницу
            deviceComboBox->addItem(QString("Устройство %1").arg(i)); // Добавляем пункт
            std::pair<double,double> sampleStats = SimSystem->CalculateStatistics(samples[i]);
            qDebug() << "Устройство №" << i << '\n';
            qDebug() << "Среднее: " << sampleStats.first << "\n" << "Дисперсия: " << sampleStats.second << '\n';
        }
    }

    // 4. Показываем первый график
    if (ui->stackedGraphicsWidget->count() > 0) {
        ui->stackedGraphicsWidget->setCurrentIndex(0);
    }
}

void MainWindow::on_stackedGraphicsWidget_currentChanged(int index)
{

}

