#include <Include/main_system.h>

#include <iostream>

void MainSystem::RunImmitation()
{
    double t = 0;
    double ta;
    double ts_min;
    unsigned int ts_min_index = 0;

    for (auto& dev : devices_) {
        auto* expDev = dynamic_cast<ExponentialProcessingDevice*>(dev.get());
        if (expDev) expDev->resetStats();
    }

    while( t < modeling_time )
    {

        ts_min = std::numeric_limits < double >::max();
        ta = stream_->GenerateTau();
        for( size_t i = 0; i < devices_.size(); i++ )
        {
            double ts_i = devices_[i]->getServiceTime();
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
            Requirement new_req = req_handler_->CreateRequirement();
            devices_[0]->AcceptRequirement( new_req );
            //std::cout << "Поступила заявка" << " ";
        }
        else
        {
            t += ts_min;
            devices_[ts_min_index]->FinishService();

            //std::cout << "Заявка обслужилась на " << ts_min_index << " устройстве" << " ";
            if( devices_[ts_min_index] != devices_.back() )
            {
                auto unpacked_requirements = req_handler_->UnpackRequirement();

                for( auto& req: unpacked_requirements )
                {
                    devices_[ts_min_index + 1]->AcceptRequirement( req );
                }
                //std::cout << unpacked_requirements.size() << " заявок распаковалось" << '\n';
            }
        }
        //std::cout << "Время: " << t << '\n';
    }
}

std::vector<double> MainSystem::GetProbabilityDistribution( size_t device_id ) const
{
    if (device_id >= devices_.size())
    {
        return {};
    }

    auto* exp_device = dynamic_cast<ExponentialProcessingDevice*>(devices_[device_id].get());
    if (!exp_device)
    {
        return {};
    }

    const auto& stats = exp_device->getQueueStats();
    if (stats.empty())
    {
        return {};
    }

    // 1. Считаем общее число наблюдений
    size_t total_observations = 0;
    for (const auto& [len, freq] : stats)
    {
        total_observations += freq;
    }

    if (total_observations == 0)
    {
        return {};
    }

    // 2. Находим максимальную длину очереди, чтобы задать размер вектора
    size_t max_queue_len = stats.rbegin()->first;

    // 3. Создаём вектор вероятностей, заполняем нулями
    std::vector<double> probabilities(static_cast<int>(max_queue_len) + 1, 0.0);

    // 4. Конвертируем частоты в вероятности
    for (const auto& [len, freq] : stats)
    {
        probabilities[static_cast<int>(len)] = static_cast<double>(freq) / total_observations;
    }

    /// Отладочная инфа
    // std::cout << "=== Debug: Device " << device_id << " probability vector ===\n";
    // for (size_t i = 0; i < probabilities.size(); ++i)
    // {
    //     if (probabilities[i] > 0.0)
    //     {
    //         std::cout << "  P(" << i << ") = " << probabilities[i] << "\n";
    //     }
    // }

    return probabilities;
}

std::vector<std::vector<double>> MainSystem::GetAllProbabilityDistributions() const
{
    std::vector< std::vector< double > > result;
    for( size_t i = 0; i < devices_.size(); i++ )
    {
        result.push_back( GetProbabilityDistribution(i) );
    }

    return result;
}

// Метод подсчета ср.числа заявок на фазе, дисперсию
std::pair< double, double > MainSystem::CalculateStatistics(std::vector< double >& sample) const
{
    double mean = 0.0;
    double variance = 0.0;

    for( size_t i = 0; i < sample.size(); i++ )
    {
        mean += ( i + 1 ) * sample[i];
    }


    for( size_t i = 0; i < sample.size(); i++ )
    {
        variance += sample[i] * std::pow( ( i + 1 ) - mean, 2 );
    }

    return { mean, variance };
}
