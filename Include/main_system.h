#ifndef MAIN_SYSTEM_H
#define MAIN_SYSTEM_H

#include <Include/stream.h>
#include <Include/processing_device.h>
#include <Include/requirement_handler.h>
#include <Include/requirement.h>

#include <vector>
#include <memory>

class MainSystem
{


public:

    MainSystem() = default;

    MainSystem( int device_num, double time, double lambda, std::vector<std::unique_ptr<IUnpackStrategy>> unpack_strategies, std::vector<double> mu_vector ) : modeling_time( time )
    {
        stream_ = std::make_unique < PoissonStream > ( lambda );
        for( size_t i = 0; i < device_num; i++ )
        {
            devices_.push_back( std::make_unique < ProcessingDevice > ( mu_vector[i] ) );
        }
        req_handler_ = std::make_unique < RequirementHandler > ( std::move(unpack_strategies) );
    };

    void RunImmitation();

    std::vector<double> GetProbabilityDistribution(size_t device_id) const;
    //Функция для перевода map -> vector
    std::vector<std::vector<double>> GetAllProbabilityDistributions() const;
    std::pair< double, double > CalculateStatistics(std::vector< double >& sample) const;


private:

    double modeling_time;
    std::unique_ptr < IStream > stream_;
    std::vector < std::unique_ptr < ProcessingDevice > > devices_;
    std::unique_ptr < RequirementHandler > req_handler_;
};

#endif // MAIN_SYSTEM_H
