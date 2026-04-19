#include <Include/processing_device.h>

void ExponentialProcessingDevice::AcceptRequirement( Requirement& requirement )
{
    requirement.service_time_ = service_distr_(RandomGenerator::get());
    requirements_.emplace_back( requirement );

    recordVectorState();
}

void ExponentialProcessingDevice::FinishService()
{
    if( requirements_.empty() )
    {
        return;
    }
    auto min_iter = std::min_element(requirements_.begin(), requirements_.end(),
                                     [](const Requirement& a, const Requirement& b)
                                     {
                                         return a.service_time_ < b.service_time_;
                                     }
                                     );

    requirements_.erase(min_iter);
    recordVectorState();
}

void ExponentialProcessingDevice::recordVectorState()
{
    size_t current_size = requirements_.size();
    vector_stats_[current_size]++;
}
const std::map<size_t, size_t>& ExponentialProcessingDevice::getVectorStats() const
{
    return vector_stats_;
}
void ExponentialProcessingDevice::resetStats()
{
    vector_stats_.clear();
}

