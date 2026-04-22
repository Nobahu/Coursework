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

    phasesComboBox = new QComboBox(ui->centralwidget);
    phasesComboBox->setGeometry(355, 20, 150, 20); // подстройте координаты
    phasesComboBox->setObjectName("phasesComboBox");
    phasesComboBox->setFocusPolicy(Qt::NoFocus);
    phasesComboBox->setVisible(false);

    connect(phasesComboBox, QOverload<int>::of(&QComboBox::currentIndexChanged),
            ui->PhaseStackedWidget, &QStackedWidget::setCurrentIndex);
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
    std::vector< double > mu_vector;
    for(size_t i = 0;i < m_phaseLineEdits.size();i++)
    {
        mu_vector.emplace_back(m_phaseLineEdits[i]->text().toDouble());
    }

    std::vector<std::unique_ptr<IUnpackStrategy>> unpack_strategies;
    for (size_t i = 0; i < device_num - 1; ++i)  // для всех фаз, кроме последней
    {
        if (!m_strategyComboBoxes[i]) continue;

        int stratType = m_strategyComboBoxes[i]->currentIndex();

        if (stratType == 0)  // Пуассон
        {
            QStackedWidget* stack = m_strategyParamsStack[i];
            QWidget* poissonPage = stack->widget(0);
            QLineEdit* lambdaEdit = poissonPage->findChild<QLineEdit*>();
            double lambda_unpack = lambdaEdit ? lambdaEdit->text().toDouble() : 1.0;

            unpack_strategies.push_back(std::make_unique<PoissonUnpackStrategy>(lambda_unpack));
        }
        else if (stratType == 1)  // Дискретное
        {
            std::vector<double> probs;
            for (QLineEdit* edit : m_unpackParamEdits[i])
            {
                probs.push_back(edit->text().toDouble());
            }
            unpack_strategies.push_back(std::make_unique<DiscreteUnpackStrategy>(probs));
        }
    }

    SimSystem = std::make_unique<MainSystem>(device_num, time, lambda, std::move(unpack_strategies), mu_vector );

    while (ui->stackedGraphicsWidget->count() > 0) {
        QWidget* page = ui->stackedGraphicsWidget->widget(0);
        ui->stackedGraphicsWidget->removeWidget(page);
        delete page;
    }
    deviceComboBox->clear();

    SimSystem->RunImmitation();

    std::vector<std::vector<double>> samples = SimSystem->GetAllProbabilityDistributions();

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


void MainWindow::on_PSettings_pushButton_clicked()
{
    int device_num = ui->lineEdit_4->text().toInt();

    // Очистка старого содержимого
    while (ui->PhaseStackedWidget->count() > 0) {
        QWidget* w = ui->PhaseStackedWidget->widget(0);
        ui->PhaseStackedWidget->removeWidget(w);
        delete w;
    }
    phasesComboBox->clear();

    // Очистка векторов хранения
    m_phaseLineEdits.clear();
    m_strategyComboBoxes.clear();
    m_strategyParamsStack.clear();
    m_unpackParamEdits.clear();

    // Для каждой фазы создаём страницу
    for (size_t i = 0; i < device_num; ++i)
    {
        QWidget *page = new QWidget();
        QVBoxLayout *layout = new QVBoxLayout(page);

        // === 1. Поле ввода μ (для всех фаз) ===
        QLabel *muLabel = new QLabel(QString("Фаза %1 — интенсивность обслуживания μ").arg(i + 1), page);
        layout->addWidget(muLabel);

        QLineEdit *muEdit = new QLineEdit(page);
        muEdit->setPlaceholderText("Введите μ...");
        layout->addWidget(muEdit);
        m_phaseLineEdits.push_back(muEdit);

        // === 2. Для всех фаз, КРОМЕ последней — настройка распаковки ===
        if (i < device_num - 1)
        {
            // Разделитель
            QFrame *line = new QFrame(page);
            line->setFrameShape(QFrame::HLine);
            line->setFrameShadow(QFrame::Sunken);
            layout->addWidget(line);

            QLabel *unpackLabel = new QLabel("Стратегия распаковки:", page);
            layout->addWidget(unpackLabel);

            // === Комбобокс выбора стратегии (только 2 пункта) ===
            QComboBox *strategyCombo = new QComboBox(page);
            strategyCombo->addItem("Пуассон");
            strategyCombo->addItem("Дискретное");
            layout->addWidget(strategyCombo);
            m_strategyComboBoxes.push_back(strategyCombo);

            // === Стек для параметров стратегии ===
            QStackedWidget *paramStack = new QStackedWidget(page);

            // ---- Страница 0: Пуассон ----
            QWidget *poissonPage = new QWidget();
            QVBoxLayout *poissonLayout = new QVBoxLayout(poissonPage);
            QLineEdit *lambdaEdit = new QLineEdit(poissonPage);
            lambdaEdit->setPlaceholderText("λ (среднее число заявок)");
            poissonLayout->addWidget(lambdaEdit);
            poissonLayout->addStretch();
            paramStack->addWidget(poissonPage);

            // ---- Страница 1: Дискретное ----
            QWidget *discretePage = new QWidget();
            QVBoxLayout *discreteLayout = new QVBoxLayout(discretePage);
            std::vector<QLineEdit*> probEdits;
            for (int j = 0; j <= 5; ++j)
            {
                QLineEdit *edit = new QLineEdit(discretePage);
                edit->setPlaceholderText(QString("p%1").arg(j));
                discreteLayout->addWidget(edit);
                probEdits.push_back(edit);
            }
            discreteLayout->addStretch();
            paramStack->addWidget(discretePage);

            layout->addWidget(paramStack);
            m_strategyParamsStack.push_back(paramStack);
            m_unpackParamEdits.push_back(probEdits);

            // === Связь комбобокса со стеком ===
            connect(strategyCombo, QOverload<int>::of(&QComboBox::currentIndexChanged),
                    paramStack, &QStackedWidget::setCurrentIndex);
        }
        else
        {
            // Для последней фазы стратегии нет — добавляем nullptr для сохранения индексации
            m_strategyComboBoxes.push_back(nullptr);
            m_strategyParamsStack.push_back(nullptr);
            m_unpackParamEdits.push_back({});
        }

        layout->addStretch();
        page->setLayout(layout);

        ui->PhaseStackedWidget->addWidget(page);
        phasesComboBox->addItem(QString("Фаза %1").arg(i + 1));
    }

    // Установка геометрии и отображение
    ui->PhaseStackedWidget->setGeometry(260, 50, 350, 300);
    ui->PhaseStackedWidget->setVisible(true);
    phasesComboBox->setVisible(true);

    if (ui->PhaseStackedWidget->count() > 0) {
        ui->PhaseStackedWidget->setCurrentIndex(0);
    }

    connect(phasesComboBox, QOverload<int>::of(&QComboBox::currentIndexChanged),
            ui->PhaseStackedWidget, &QStackedWidget::setCurrentIndex);
}

