#ifndef PROCESSING_DEVICE_H
#define PROCESSING_DEVICE_H

#include <Include/requirement.h>
#include <Include/random_generator.h>

#include <vector>
#include <algorithm>
#include <map>

class ProcessingDevice
{


public:

    ProcessingDevice(double mu) : mu_(mu), service_distr_(mu) {}

    void AcceptRequirement( Requirement& requirement );
    void FinishService();

    void TimeSubstraction(double time)
    {
        for(auto& req: requirements_)
        {
            req.service_time_ -= time;
            if (req.service_time_ < 0) req.service_time_ = 0;
        }
    }

    double GetMinimalServiceTime()
    {
        if (requirements_.empty())
        {
            return -1.0;
        }

        auto iter = std::min_element(requirements_.begin(),requirements_.end(),
                                     [](const Requirement& first, const Requirement& second)
                                     {
                                         return first.service_time_ < second.service_time_;
                                     }
                                     );

        if (iter != requirements_.end())
        {
            min_service_time_ = iter->service_time_;
            if (min_service_time_ < 0) min_service_time_ = 0;
            return min_service_time_ ;
        }
        else
        {
            return -1;
        }
    }

    void recordVectorState();
    const std::map<size_t, size_t>& getVectorStats() const;
    void resetStats();

private:

    double min_service_time_;
    std::vector< Requirement > requirements_;
    std::map<size_t, size_t> map_stats_;
    std::exponential_distribution<double> service_distr_;
    double mu_;

};


#endif // PROCESSING_DEVICE_H
