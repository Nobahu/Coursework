#include <Include/main_system.h>

#include <iostream>

void MainSystem::RunImmitation()
{
    double t = 0;
    double ta;
    double ts_min;
    unsigned int ts_min_index = 0;

    for (auto& device : devices_) {
        auto* expDevice = dynamic_cast<ProcessingDevice*>(device.get());
        if (expDevice) expDevice->resetStats();
    }

    ta = stream_->GenerateTau();

    while( t < modeling_time )
    {

        ts_min = std::numeric_limits < double >::max();

        for( size_t i = 0; i < devices_.size(); i++ )
        {
            double ts_i = devices_[i]->GetMinimalServiceTime();
            if( ts_i < ts_min && ts_i != -1 )
            {
                ts_min = ts_i;
                ts_min_index = i;
            }
        }

        if( ta < ts_min )
        {
            t += ta;
            // Временное решение, в идеале решить проблему через переопределение const Requirement&
            for (auto& device : devices_)
            {
                device->TimeSubstraction(ta);
            }
            Requirement new_req = req_handler_->CreateRequirement();
            devices_[0]->AcceptRequirement( new_req );

            /// Генерируем время вновь, т.к заявка уже поступила -> нужно новое время
            ta = stream_->GenerateTau();
        }
        else
        {
            t += ts_min;
            /// Уточнить добавление. По сути делаем так, чтобы время до поступления не генерировалось снова, а уменьшаем текущее
            //ta -= ts_min;
            for (auto& device : devices_)
            {
                device->TimeSubstraction(ts_min);
            }
            devices_[ts_min_index]->FinishService();

            if( devices_[ts_min_index] != devices_.back() )
            {
                auto unpacked_requirements = req_handler_->UnpackRequirement(ts_min_index);
                if(!unpacked_requirements.size())
                {
                    std::cout << "Заявка не распаковалась" << '\n';
                }
                else
                {
                    std::cout << "Произошла распаковка " << unpacked_requirements.size() << " заявок" << "\n";
                }

                for( auto& req: unpacked_requirements )
                {
                    devices_[ts_min_index + 1]->AcceptRequirement( req );
                }
            }
        }
    }
}

std::vector<double> MainSystem::GetProbabilityDistribution( size_t device_id ) const
{
    if (device_id >= devices_.size()) {
        return {};
    }

    auto* exp_device = dynamic_cast<ProcessingDevice*>(devices_[device_id].get());
    if (!exp_device) {
        return {};
    }

    const auto& stats = exp_device->getVectorStats();
    if (stats.empty()) {
        return {};
    }

    // 1. Считаем общее число наблюдений
    size_t total_observations = 0;
    for (const auto& [len, freq] : stats) {
        total_observations += freq;
    }

    if (total_observations == 0) {
        return {};
    }

    // 2. Находим максимальную длину очереди, чтобы задать размер вектора
    size_t max_queue_len = stats.rbegin()->first;

    // 3. Создаём вектор вероятностей, заполняем нулями
    std::vector<double> probabilities(static_cast<int>(max_queue_len) + 1, 0.0);

    // 4. Конвертируем частоты в вероятности
    for (const auto& [len, freq] : stats) {
        probabilities[static_cast<int>(len)] = static_cast<double>(freq) / total_observations;
    }

    /// Отладочная инфа
    // std::cout << "=== Debug: Device " << device_id << " probability vector ===\n";
    // for (size_t i = 0; i < probabilities.size(); ++i) {
    //     if (probabilities[i] > 0.0) {
    //         std::cout << "  P(" << i << ") = " << probabilities[i] << "\n";
    //     }
    // }

    return probabilities;
}

std::vector<std::vector<double>> MainSystem::GetAllProbabilityDistributions() const
{
    std::vector<std::vector<double>> result;
    for( size_t i = 0; i < devices_.size(); i++ )
    {
        result.push_back( GetProbabilityDistribution(i) );
    }

    return result;
}

// Метод подсчета ср.числа заявок на фазе, дисперсию, распределение
std::pair< double, double > MainSystem::CalculateStatistics(std::vector< double >& sample) const
{
    double mean = 0.0;
    double variance = 0.0;

    for( size_t i = 0; i < sample.size(); i++ )
    {
        mean += ( i ) * sample[ i ];
    }


    for( size_t i = 0; i < sample.size(); i++ )
    {
        variance += sample[ i ] * std::pow( i  - mean, 2 );
    }

    return { mean, variance };
}
