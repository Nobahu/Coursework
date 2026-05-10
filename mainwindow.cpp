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
    barChart->setTitle(QString("Распределение числа заявок (Фаза %1)").arg(device_id));
    barChart->setAnimationOptions(QChart::SeriesAnimations);

    QBarCategoryAxis *axisX = new QBarCategoryAxis();
    axisX->append(categories);
    axisX->setTitleText("Число заявок на фазе");
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
    unsigned int seed = ui->lineEdit_5->text().toInt();
    RandomGenerator::seed(seed);

    std::unique_ptr<IStream> stream;
    int streamType = m_streamTypeComboBox->currentIndex();

    if (streamType == 0) {
        double lambda = m_streamParamEdits[0]->text().toDouble();
        stream = std::make_unique<PoissonStream>(lambda);
    } else if (streamType == 1) {
        double k = m_streamParamEdits[1]->text().toDouble();
        double theta = m_streamParamEdits[2]->text().toDouble();
        stream = std::make_unique<GammaStream>(k, theta);
    }

    std::vector<std::unique_ptr<ProcessingDevice>> devices;

    for (size_t i = 0; i < device_num; i++)
    {
        int serviceType = m_serviceTypeComboBoxes[i]->currentIndex();

        if (serviceType == 0)  // Экспоненциальное
        {
            double mu = m_serviceParamEdits[i][0]->text().toDouble();
            devices.push_back(std::make_unique<ExponentialProcessingDevice>(mu));
        }
        else if (serviceType == 1)  // Гамма
        {
            double k = m_serviceParamEdits[i][0]->text().toDouble();
            double theta = m_serviceParamEdits[i][1]->text().toDouble();
            devices.push_back(std::make_unique<GammaProcessingDevice>(k, theta));
        }
    }

    std::vector<std::unique_ptr<IUnpackStrategy>> unpack_strategies;
    for (size_t i = 0; i < device_num - 1; ++i)
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
        else if (stratType == 2)
        {
            QStackedWidget* stack = m_strategyParamsStack[i];
            QWidget* gammaPage = stack->widget(2);
            QList<QLineEdit*> edits = gammaPage->findChildren<QLineEdit*>();
            double a = edits[0]->text().toDouble();
            double b = edits[1]->text().toDouble();
            unpack_strategies.push_back(std::make_unique<DiscreteUniformUnpackStrategy>(a, b));
        }
    }

    SimSystem = std::make_unique<MainSystem>( device_num, time,
                                             std::move( stream ),
                                             std::move( unpack_strategies ),
                                             std::move( devices ) );

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

void MainWindow::on_SSettings_pushButton_clicked()
{
    QStackedWidget* streamStack = ui->StreamStackedWidget;

    // Очищаем старые страницы
    while (streamStack->count() > 0) {
        QWidget* page = streamStack->widget(0);
        streamStack->removeWidget(page);
        delete page;
    }

    // Очищаем векторы
    m_streamParamEdits.clear();

    // Создаём одну страницу
    QWidget* page = new QWidget();
    QVBoxLayout* layout = new QVBoxLayout(page);

    // Заголовок
    QLabel* titleLabel = new QLabel("Настройки входного потока", page);
    QFont font = titleLabel->font();
    font.setBold(true);
    titleLabel->setFont(font);
    layout->addWidget(titleLabel);

    // Тип потока
    QLabel* streamTypeLabel = new QLabel("Тип потока:", page);
    layout->addWidget(streamTypeLabel);

    m_streamTypeComboBox = new QComboBox(page);
    m_streamTypeComboBox->addItem("Пуассоновский (экспоненциальный)");
    m_streamTypeComboBox->addItem("Гамма-поток");
    layout->addWidget(m_streamTypeComboBox);

    // Стек для параметров
    QStackedWidget* paramStack = new QStackedWidget(page);

    // Страница 0: Пуассон
    QWidget* poissonPage = new QWidget();
    QVBoxLayout* poissonLayout = new QVBoxLayout(poissonPage);
    QLineEdit* lambdaEdit = new QLineEdit(poissonPage);
    lambdaEdit->setPlaceholderText("λ (интенсивность)");
    poissonLayout->addWidget(lambdaEdit);
    poissonLayout->addStretch();
    paramStack->addWidget(poissonPage);

    // Страница 1: Гамма
    QWidget* gammaPage = new QWidget();
    QVBoxLayout* gammaLayout = new QVBoxLayout(gammaPage);
    QLineEdit* kEdit = new QLineEdit(gammaPage);
    kEdit->setPlaceholderText("k (форма)");
    gammaLayout->addWidget(kEdit);
    QLineEdit* thetaEdit = new QLineEdit(gammaPage);
    thetaEdit->setPlaceholderText("θ (масштаб)");
    gammaLayout->addWidget(thetaEdit);
    gammaLayout->addStretch();
    paramStack->addWidget(gammaPage);

    layout->addWidget(paramStack);
    layout->addStretch();

    // Сохраняем
    m_streamParamEdits.push_back(lambdaEdit);
    m_streamParamEdits.push_back(kEdit);
    m_streamParamEdits.push_back(thetaEdit);

    streamStack->addWidget(page);

    // Связь комбобокса со стеком
    connect(m_streamTypeComboBox, QOverload<int>::of(&QComboBox::currentIndexChanged),
            paramStack, &QStackedWidget::setCurrentIndex);
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
    m_serviceTypeComboBoxes.clear();
    m_serviceParamEdits.clear();

    // Для каждой фазы создаём страницу
    for (size_t i = 0; i < device_num; ++i)
    {
        QWidget *page = new QWidget();
        QVBoxLayout *layout = new QVBoxLayout(page);

        // === 1. Заголовок фазы ===
        QLabel *phaseLabel = new QLabel(QString("Фаза %1").arg(i), page);
        QFont font = phaseLabel->font();
        font.setBold(true);
        phaseLabel->setFont(font);
        layout->addWidget(phaseLabel);

        // === 2. Выбор типа обслуживания (для ВСЕХ фаз) ===
        QLabel *serviceLabel = new QLabel("Тип обслуживания:", page);
        layout->addWidget(serviceLabel);

        QComboBox *serviceTypeCombo = new QComboBox(page);
        serviceTypeCombo->addItem("Экспоненциальное");
        serviceTypeCombo->addItem("Гамма");
        layout->addWidget(serviceTypeCombo);
        m_serviceTypeComboBoxes.push_back(serviceTypeCombo);

        // === Стек для параметров обслуживания ===
        QStackedWidget *serviceParamStack = new QStackedWidget(page);
        std::vector<QLineEdit*> serviceEdits;

        // Страница 0: Экспоненциальное (μ)
        QWidget *expPage = new QWidget();
        QVBoxLayout *expLayout = new QVBoxLayout(expPage);
        QLineEdit *muEdit = new QLineEdit(expPage);
        muEdit->setPlaceholderText("μ (интенсивность)");
        expLayout->addWidget(muEdit);
        expLayout->addStretch();
        serviceParamStack->addWidget(expPage);
        serviceEdits.push_back(muEdit);  // индекс 0

        // Страница 1: Гамма (k, θ)
        QWidget *gammaServicePage = new QWidget();
        QVBoxLayout *gammaServiceLayout = new QVBoxLayout(gammaServicePage);
        QLineEdit *kServiceEdit = new QLineEdit(gammaServicePage);
        kServiceEdit->setPlaceholderText("k (форма)");
        gammaServiceLayout->addWidget(kServiceEdit);
        serviceEdits.push_back(kServiceEdit);  // индекс 1
        QLineEdit *thetaServiceEdit = new QLineEdit(gammaServicePage);
        thetaServiceEdit->setPlaceholderText("θ (масштаб)");
        gammaServiceLayout->addWidget(thetaServiceEdit);
        serviceEdits.push_back(thetaServiceEdit);  // индекс 2
        gammaServiceLayout->addStretch();
        serviceParamStack->addWidget(gammaServicePage);

        layout->addWidget(serviceParamStack);
        m_serviceParamEdits.push_back(serviceEdits);

        // Связь комбобокса типа обслуживания со стеком параметров
        connect(serviceTypeCombo, QOverload<int>::of(&QComboBox::currentIndexChanged),
                serviceParamStack, &QStackedWidget::setCurrentIndex);

        // === 3. Для всех фаз, КРОМЕ последней — настройка распаковки ===
        if (i < device_num - 1)
        {
            // Разделитель
            QFrame *line = new QFrame(page);
            line->setFrameShape(QFrame::HLine);
            line->setFrameShadow(QFrame::Sunken);
            layout->addWidget(line);

            QLabel *unpackLabel = new QLabel("Стратегия распаковки:", page);
            layout->addWidget(unpackLabel);

            // === Комбобокс выбора стратегии ===
            QComboBox *strategyCombo = new QComboBox(page);
            strategyCombo->addItem("Пуассон");
            strategyCombo->addItem("Дискретное");
            strategyCombo->addItem("Равномерное");
            layout->addWidget(strategyCombo);
            m_strategyComboBoxes.push_back(strategyCombo);

            // === Стек для параметров стратегии ===
            QStackedWidget *paramStack = new QStackedWidget(page);
            std::vector<QLineEdit*> allEdits;

            // ---- Страница 0: Пуассон ----
            QWidget *poissonPage = new QWidget();
            QVBoxLayout *poissonLayout = new QVBoxLayout(poissonPage);
            QLineEdit *lambdaEdit = new QLineEdit(poissonPage);
            lambdaEdit->setPlaceholderText("λ (среднее число заявок)");
            poissonLayout->addWidget(lambdaEdit);
            poissonLayout->addStretch();
            paramStack->addWidget(poissonPage);
            allEdits.push_back(lambdaEdit);  // индекс 0

            // ---- Страница 1: Дискретное ----
            QWidget *discretePage = new QWidget();
            QVBoxLayout *discreteLayout = new QVBoxLayout(discretePage);
            for (int j = 0; j <= 5; ++j)
            {
                QLineEdit *edit = new QLineEdit(discretePage);
                edit->setPlaceholderText(QString("p%1").arg(j));
                discreteLayout->addWidget(edit);
                allEdits.push_back(edit);  // индексы 1..6
            }
            discreteLayout->addStretch();
            paramStack->addWidget(discretePage);

            // ---- Страница 2: Равномерное ----
            QWidget *unformUnpackPage = new QWidget();
            QVBoxLayout *unformUnpackLayout = new QVBoxLayout(unformUnpackPage);
            QLineEdit *aUnpackEdit = new QLineEdit(unformUnpackPage);
            aUnpackEdit->setPlaceholderText("Параметр a");
            unformUnpackLayout->addWidget(aUnpackEdit);
            allEdits.push_back(aUnpackEdit);  // индекс 7
            QLineEdit *bUnpackEdit = new QLineEdit(unformUnpackPage);
            bUnpackEdit->setPlaceholderText("Параметр b");
            unformUnpackLayout->addWidget(bUnpackEdit);
            allEdits.push_back(bUnpackEdit);  // индекс 8
            unformUnpackLayout->addStretch();
            paramStack->addWidget(unformUnpackPage);

            layout->addWidget(paramStack);
            m_strategyParamsStack.push_back(paramStack);
            m_unpackParamEdits.push_back(allEdits);

            // === Связь комбобокса со стеком ===
            connect(strategyCombo, QOverload<int>::of(&QComboBox::currentIndexChanged),
                    paramStack, &QStackedWidget::setCurrentIndex);
        }
        else
        {
            // Для последней фазы стратегии нет
            m_strategyComboBoxes.push_back(nullptr);
            m_strategyParamsStack.push_back(nullptr);
            m_unpackParamEdits.push_back({});
        }

        layout->addStretch();
        page->setLayout(layout);

        ui->PhaseStackedWidget->addWidget(page);
        phasesComboBox->addItem(QString("Фаза %1").arg(i));
    }

    // Установка геометрии и отображение
    ui->PhaseStackedWidget->setGeometry(260, 50, 350, 400);  // увеличил высоту до 400
    ui->PhaseStackedWidget->setVisible(true);
    phasesComboBox->setVisible(true);

    if (ui->PhaseStackedWidget->count() > 0) {
        ui->PhaseStackedWidget->setCurrentIndex(0);
    }

    connect(phasesComboBox, QOverload<int>::of(&QComboBox::currentIndexChanged),
            ui->PhaseStackedWidget, &QStackedWidget::setCurrentIndex);
}

