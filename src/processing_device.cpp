#include <Include/processing_device.h>

void ExponentialProcessingDevice::AcceptRequirement( Requirement& requirement )
{
    if( requirements_.empty() ) {
        this->GenerateDelta();
    }
    requirements_.push( requirement );

    recordQueueState();
}

void ExponentialProcessingDevice::FinishService()
{
    if( requirements_.empty() )
    {
        return;
    }

    if( !requirements_.empty() )
    {
        requirements_.pop();
    }

    recordQueueState();

    if( !requirements_.empty() )
    {
        GenerateDelta();
    }
    else
    {
        delta_ = -1;
    }
}

double ExponentialProcessingDevice::getServiceTime()
{
    return delta_;
}

void ExponentialProcessingDevice::GenerateDelta()
{
    delta_ = distr_( RandomGenerator::get() );
}

void ExponentialProcessingDevice::recordQueueState()
{
    size_t current_size = requirements_.size();
    queue_stats_[current_size]++;
}
const std::map<size_t, size_t>& ExponentialProcessingDevice::getQueueStats() const
{
    return queue_stats_;
}
void ExponentialProcessingDevice::resetStats()
{
    queue_stats_.clear();
}

