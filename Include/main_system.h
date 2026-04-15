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

    MainSystem( int device_num, double time, double lambda, double r_h_lambda , double mu, double unpack_probability ) : modeling_time( time )
    {
        stream_ = std::make_unique < PoissonStream > ( lambda );
        for( size_t i = 0; i < device_num; i++ )
        {
            devices_.push_back( std::make_unique < ExponentialProcessingDevice > ( mu ) );
        }
        req_handler_ = std::make_unique < RequirementHandler > ( r_h_lambda, unpack_probability );
    };

    void RunImmitation();

    std::vector<double> GetProbabilityDistribution(size_t device_id) const;

    //Функция для перевода map -> vector
    std::vector<std::vector<double>> GetAllProbabilityDistributions() const;

    void CalculateStatistics();


private:

    double modeling_time;

    std::unique_ptr < IStream > stream_;
    std::vector < std::unique_ptr < IProcessingDevice > > devices_;
    std::unique_ptr < RequirementHandler > req_handler_;
};

#endif // MAIN_SYSTEM_H
