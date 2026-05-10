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

    MainSystem( int device_num, double time, std::unique_ptr<IStream> stream, std::vector< std::unique_ptr< IUnpackStrategy > > unpack_strategies, std::vector<std::unique_ptr<ProcessingDevice>> devices):
            modeling_time( time ),
            devices_( std::move( devices ) ),
            stream_( std::move( stream ) ),
            req_handler_( std::make_unique<RequirementHandler>( std::move( unpack_strategies ) ) ) {}

    void RunImmitation();

    //Функция для перевода map -> vector
    std::vector< std::vector< double > > GetAllProbabilityDistributions() const;
    std::pair< double, double > CalculateStatistics( std::vector< double >& sample ) const;


private:

    std::vector< double > GetProbabilityDistribution( size_t device_id ) const;

    double modeling_time;
    std::unique_ptr< IStream > stream_;
    std::vector< std::unique_ptr < ProcessingDevice > > devices_;
    std::unique_ptr< RequirementHandler > req_handler_;
};

#endif // MAIN_SYSTEM_H
