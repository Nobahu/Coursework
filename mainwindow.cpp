#include "mainwindow.h"
#include "./ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->setWindowTitle("Имитационное моделирование СМО с распаковкой заявок");
    loadStylesheet();

    phasesComboBox = new QComboBox(ui->centralwidget);
    phasesComboBox->setGeometry(425, 20, 150, 25); // подстройте координаты
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

void MainWindow::loadStylesheet()
{
    QFile file(":/styles.qss");
    if (file.open(QFile::ReadOnly)) {
        QString styleSheet = QLatin1String(file.readAll());
        this->setStyleSheet(styleSheet);
        file.close();
    } else {
        qDebug() << "Ресурс styles.qss не найден!";
    }
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


    double maxProb = *std::max_element(probs.begin(), probs.end());
    QValueAxis *axisY = new QValueAxis();
    axisY->setTitleText("Вероятность");
    axisY->setRange(0.0, maxProb * 1.1);
    axisY->setLabelFormat("%.2f");
    barChart->addAxis(axisY, Qt::AlignLeft);
    series->attachAxis(axisY);

    return barChart;
}

void MainWindow::ShowResultsDialog( std::vector< std::vector< double > >& samples )
{
    QDialog* resultsDialog = new QDialog(this);
    resultsDialog->setWindowTitle("Результаты моделирования");
    resultsDialog->setMinimumSize(1280, 720);
    resultsDialog->setWindowFlags(Qt::Window);

    QSplitter* mainSplitter = new QSplitter(Qt::Horizontal, resultsDialog);

    /// Левая часть с графиками
    QWidget* leftWidget = new QWidget();
    QVBoxLayout* leftLayout = new QVBoxLayout(leftWidget);

    QLabel* deviceLabel = new QLabel("Выберите устройство:");
    leftLayout->addWidget(deviceLabel);

    QComboBox* deviceSelector = new QComboBox();
    leftLayout->addWidget(deviceSelector);

    QStackedWidget* chartsStack = new QStackedWidget();
    leftLayout->addWidget(chartsStack);

    /// Правая часть с вкладками
    QWidget* rightWidget = new QWidget();
    QVBoxLayout* rightLayout = new QVBoxLayout(rightWidget);

    // Создаём виджет с вкладками
    QTabWidget* tabWidget = new QTabWidget();

    // ===== Вкладка 1: Статистика =====
    QWidget* statsWidget = new QWidget();
    QVBoxLayout* statsLayout = new QVBoxLayout(statsWidget);

    QLabel* statsLabel = new QLabel("Статистика по устройствам:");
    statsLayout->addWidget(statsLabel);

    QTableWidget* statsTable = new QTableWidget();
    statsTable->setColumnCount(3);
    statsTable->setHorizontalHeaderLabels({"Устройство", "Среднее", "Дисперсия"});
    statsTable->setAlternatingRowColors(true);
    statsTable->setSelectionBehavior(QAbstractItemView::SelectRows);
    statsLayout->addWidget(statsTable);

    tabWidget->addTab(statsWidget, "Статистика");

    // ===== Вкладка 2: Ряды распределения =====
    QWidget* distrWidget = new QWidget();
    QVBoxLayout* distrLayout = new QVBoxLayout(distrWidget);

    QLabel* distrLabel = new QLabel("Ряды распределения вероятностей:");
    distrLayout->addWidget(distrLabel);

    QTableWidget* distrTable = new QTableWidget();
    distrTable->setAlternatingRowColors(true);
    distrLayout->addWidget(distrTable);

    tabWidget->addTab(distrWidget, "Ряды распределения");

    rightLayout->addWidget(tabWidget);

    mainSplitter->addWidget(leftWidget);
    mainSplitter->addWidget(rightWidget);
    mainSplitter->setSizes({500, 250});

    /// Заполнение данными
    distrTable->setColumnCount(2);
    distrTable->setHorizontalHeaderLabels({"Кол-во заявок", "Вероятность"});

    for (size_t i = 0; i < samples.size(); ++i) {
        if (!samples[i].empty()) {
            /// Графики
            QChart* chart = createBarChart(samples[i], static_cast<int>(i));
            QChartView* view = new QChartView(chart);
            view->setRenderHint(QPainter::Antialiasing);
            chartsStack->addWidget(view);
            deviceSelector->addItem(QString("Устройство %1").arg(i));

            /// Таблица статистики
            characteristics = SimSystem->CalculateStatistics(samples[i]);
            int row = statsTable->rowCount();
            statsTable->insertRow(row);
            statsTable->setItem(row, 0, new QTableWidgetItem(QString("Устройство %1").arg(i)));
            statsTable->setItem(row, 1, new QTableWidgetItem(QString::number(characteristics.first, 'f', 6)));
            statsTable->setItem(row, 2, new QTableWidgetItem(QString::number(characteristics.second, 'f', 6)));

            /// Таблицу распределений
            int headerRow = distrTable->rowCount();
            distrTable->insertRow(headerRow);
            QTableWidgetItem* headerItem = new QTableWidgetItem(QString("Устройство %1").arg(i));
            distrTable->setItem(headerRow, 0, headerItem);
            distrTable->setSpan(headerRow, 0, 1, 2);
            headerItem->setBackground(QBrush(Qt::lightGray));
            headerItem->setTextAlignment(Qt::AlignCenter);

            for (size_t j = 0; j < samples[i].size(); ++j) {
                int probRow = distrTable->rowCount();
                distrTable->insertRow(probRow);
                distrTable->setItem(probRow, 0, new QTableWidgetItem(QString::number(j)));
                distrTable->setItem(probRow, 1, new QTableWidgetItem(QString::number(samples[i][j], 'f', 6)));
            }

            if (i < samples.size() - 1) {
                int sepRow = distrTable->rowCount();
                distrTable->insertRow(sepRow);
                distrTable->setSpan(sepRow, 0, 1, 2);
            }
        }
    }

    statsTable->resizeColumnsToContents();
    distrTable->resizeColumnsToContents();

    connect(deviceSelector, QOverload<int>::of(&QComboBox::currentIndexChanged),
            chartsStack, &QStackedWidget::setCurrentIndex);

    QPushButton* saveToCSVBtn = new QPushButton("Сохранить csv");
    saveToCSVBtn->setFixedWidth(150);
    QPushButton* closeBtn = new QPushButton("Закрыть");
    closeBtn->setFixedWidth(100);

    QHBoxLayout* buttonLayout = new QHBoxLayout();
    buttonLayout->addStretch();
    buttonLayout->addWidget(saveToCSVBtn);
    buttonLayout->addWidget(closeBtn);

    QVBoxLayout* dialogLayout = new QVBoxLayout(resultsDialog);
    dialogLayout->addWidget(mainSplitter);
    dialogLayout->addLayout(buttonLayout);

    connect(closeBtn, &QPushButton::clicked, resultsDialog, &QDialog::accept);
    connect(saveToCSVBtn, &QPushButton::clicked, this, &MainWindow::on_Save_pushButton_clicked);

    resultsDialog->exec();
}

void MainWindow::saveToCSV()
{
    std::ofstream file("Simulation_statistic.csv");
    if (!file.is_open()) return;

    // Общая информация
    file << "Статистические характеристики\n";
    file << "Конфигурация модели\n";

    if (m_streamTypeComboBox)
    {
        file << "Тип потока: ," << m_streamTypeComboBox->currentText().toStdString() << '\n';

        // Параметры потока
        int streamType = m_streamTypeComboBox->currentIndex();
        if (streamType == 0 && m_streamParamEdits.size() > 0 && m_streamParamEdits[0])
        {
            file << "Параметр λ: ," << m_streamParamEdits[0]->text().toStdString() << '\n';
        }
        else if (streamType == 1 && m_streamParamEdits.size() > 2)
        {
            file << "Параметр k: ," << m_streamParamEdits[1]->text().toStdString() << '\n'
                 << "Параметр θ: ," << m_streamParamEdits[2]->text().toStdString() << '\n';
        }
    }
    file << "Количество фаз: ," << probabilitiesMap.size() << '\n';
    file << "Время моделирования: ," << ui->lineEdit_2->text().toDouble() << "\n\n";

    /// Данные по каждой фазе
    for (size_t phaseIdx = 0; phaseIdx < probabilitiesMap.size(); ++phaseIdx)
    {
        const auto& distribution = probabilitiesMap[phaseIdx];

        file << "[Фаза " << phaseIdx + 1 << "]\n";

        if (phaseIdx < m_serviceTypeComboBoxes.size() && m_serviceTypeComboBoxes[phaseIdx])
        {
            file << "Тип обслуживания:, " << m_serviceTypeComboBoxes[phaseIdx]->currentText().toStdString() << '\n';;
            // Параметры обслуживания
            if (phaseIdx < m_serviceParamEdits.size())
            {
                const auto& params = m_serviceParamEdits[phaseIdx];
                int serviceType = m_serviceTypeComboBoxes[phaseIdx]->currentIndex();

                if (serviceType == 0) // Экспоненциальное
                {
                    file << "Параметр μ: ," << params[0]->text().toStdString() << '\n';
                }
                else if (serviceType == 1) // Гамма
                {
                    file << "Параметр k ," << params[1]->text().toStdString() << '\n'
                         << "Параметр θ: ," << params[2]->text().toStdString() << '\n';
                }
            }
            file << '\n';
        }

        if (phaseIdx < m_unpackParamEdits.size() && phaseIdx < m_strategyComboBoxes.size())
        {
            file << "Тип распаковки: ,";
            if (m_strategyComboBoxes[phaseIdx])
            {
                file << m_strategyComboBoxes[phaseIdx]->currentText().toStdString() << '\n';

                // Параметры распаковки
                const auto& params = m_unpackParamEdits[phaseIdx];
                int unpackType = m_strategyComboBoxes[phaseIdx]->currentIndex();


                if (unpackType == 0) // Пуассон
                {
                    file << "Параметр λ:, " << params[0]->text().toStdString() << '\n';
                }
                else if (unpackType == 1) // Заданное рядом распределения
                {
                    file << "Ряд распределения: ,{";
                    for (size_t j = 0; j < params.size() && params[j]; ++j)
                    {
                        if (j > 0) file << ";";
                        file << params[j]->text().toStdString();
                    }
                    file << " }" << '\n';
                }
                else if (unpackType == 2) // Равномерное дискретное
                {
                    file << "Параметры [a;b]: ," << "[" << params[7]->text().toStdString() << ";" << params[8]->text().toStdString() << "]" << '\n';
                }
                else if (unpackType == 3) // Геометрическое
                {
                    file << "Параметр p: ," << params[9]->text().toStdString() << '\n';
                }
            }
        }
        file << '\n';

        // Ряд распределения
        file << "Кол-во заявок,Вероятность\n";

        double cumulative = 0.0;
        for (size_t i = 0; i < distribution.size(); ++i)
        {
            file << i << "," << distribution[i] << '\n';
        }

        file << "\n\n"; // Разделитель между фазами
    }

    file.close();
}

void MainWindow::on_Start_pushButton_clicked() try
{
    int device_num = ui->lineEdit_4->text().toInt();
    double time = ui->lineEdit_2->text().toDouble();
    unsigned int seed = ui->lineEdit_5->text().toInt();
    RandomGenerator::seed(seed);

    CheckInputParameters( device_num, time );

    /// Выбор стратегии входящего потока
    std::unique_ptr<IStream> stream;
    int streamType = m_streamTypeComboBox->currentIndex();

    StreamStrategyChoose( stream, streamType );

    /// Выбор стратегий обслуживания для фаз
    std::vector<std::unique_ptr<IProcessingDevice>> devices;
    for (size_t i = 0; i < device_num; i++)
    {
        int serviceType = m_serviceTypeComboBoxes[i]->currentIndex();

        ServiceStrategyChoose( devices, serviceType, i );
    }

    /// Выбор стратегий распаковки для каждой фазы
    std::vector<std::unique_ptr<IUnpackStrategy>> unpack_strategies;
    for (size_t i = 0; i < device_num - 1; ++i)
    {
        if (!m_strategyComboBoxes[i]) continue;

        int unpackType = m_strategyComboBoxes[i]->currentIndex();

        UnpackStrategyChoose( unpack_strategies, unpackType, i);
    }

    SimSystem = std::make_unique<MainSystem>( device_num, time,
                                             std::move( stream ),
                                             std::move( unpack_strategies ),
                                             std::move( devices ) );
    SimSystem->RunImmitation();

    /// Сбор данных о распределениях фаз
    probabilitiesMap = SimSystem->GetAllProbabilityDistributions();

    ShowResultsDialog( probabilitiesMap );

}
catch( std::exception& e )
{
    QMessageBox::critical(this, "Ошибка:", e.what());
    return;
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
    QLabel* titleLabel = new QLabel("Настройка входящего потока", page);
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

    /// Очистка старого содержимого
    while (ui->PhaseStackedWidget->count() > 0) {
        QWidget* w = ui->PhaseStackedWidget->widget(0);
        ui->PhaseStackedWidget->removeWidget(w);
        delete w;
    }
    phasesComboBox->clear();

    /// Очистка векторов хранения
    m_phaseLineEdits.clear();
    m_strategyComboBoxes.clear();
    m_strategyParamsStack.clear();
    m_unpackParamEdits.clear();
    m_serviceTypeComboBoxes.clear();
    m_serviceParamEdits.clear();

    /// Для каждой фазы создаём страницу
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
            strategyCombo->addItem("Геометрическое");
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

            // ---- Страница 3: Геометрическое ----
            QWidget *geometricPage = new QWidget();
            QVBoxLayout *geometricLayout = new QVBoxLayout(geometricPage);
            QLineEdit *geometricEdit = new QLineEdit(geometricPage);
            geometricEdit->setPlaceholderText("p (вероятность появления события)");
            geometricLayout->addWidget(geometricEdit);
            geometricLayout->addStretch();
            paramStack->addWidget(geometricPage);
            allEdits.push_back(geometricEdit);  // индекс 9

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
    ui->PhaseStackedWidget->setGeometry(330, 50, 350, 400);
    ui->PhaseStackedWidget->setVisible(true);
    phasesComboBox->setVisible(true);

    if (ui->PhaseStackedWidget->count() > 0) {
        ui->PhaseStackedWidget->setCurrentIndex(0);
    }

    connect(phasesComboBox, QOverload<int>::of(&QComboBox::currentIndexChanged),
            ui->PhaseStackedWidget, &QStackedWidget::setCurrentIndex);
}

void MainWindow::on_Save_pushButton_clicked()
{
    saveToCSV();
    QMessageBox::information(this, "Cохранение","Статистика сохранена в build/Desktop-debug/Simulation_statistic.csv");
}
