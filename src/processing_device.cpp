#include <Include/processing_device.h>

void ProcessingDevice::FinishService()
{
    if( requirements_.empty() )
    {
        return;
    }
    auto min_iter = std::min_element( requirements_.begin(), requirements_.end(),
                                     []( const Requirement& a, const Requirement& b )
                                     {
                                         return a.service_time_ < b.service_time_;
                                     }
                                     );

    requirements_.erase( min_iter );
    recordVectorState();
}

void ProcessingDevice::TimeSubstraction( double time )
{
    for( auto& req: requirements_ )
    {
        req.service_time_ -= time;
        if ( req.service_time_ < 0 ) req.service_time_ = 0;
    }
}

double ProcessingDevice::GetMinimalServiceTime()
{
    if ( requirements_.empty() )
    {
        return -1.0;
    }

    auto iter = std::min_element( requirements_.begin(),requirements_.end(),
                                 []( const Requirement& first, const Requirement& second)
                                 {
                                     return first.service_time_ < second.service_time_;
                                 }
                                 );

    if ( iter != requirements_.end() )
    {
        min_service_time_ = iter->service_time_;
        if ( min_service_time_ < 0 ) min_service_time_ = 0;
        return min_service_time_ ;
    }
    else
    {
        return -1;
    }
}

void ProcessingDevice::recordVectorState()
{
    size_t current_size = requirements_.size();
    map_stats_[ current_size ]++;
}
const std::map< size_t, size_t >& ProcessingDevice::getVectorStats() const
{
    return map_stats_;
}
void ProcessingDevice::resetStats()
{
    map_stats_.clear();
}

// Один и тот же код (но пока не понятно с тактами)
void ExponentialProcessingDevice::AcceptRequirement( Requirement& requirement )
{
    requirement.service_time_ = service_distr_( RandomGenerator::get() );
    requirements_.emplace_back( requirement );
    recordVectorState();
}

void GammaProcessingDevice::AcceptRequirement( Requirement& requirement )
{
    requirement.service_time_ = service_distr_( RandomGenerator::get() );
    requirements_.emplace_back( requirement );
    recordVectorState();
}

