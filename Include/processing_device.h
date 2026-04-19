#ifndef PROCESSING_DEVICE_H
#define PROCESSING_DEVICE_H

#include <Include/requirement.h>
#include <Include/random_generator.h>

#include <vector>
#include <algorithm>
#include <map>

class IProcessingDevice
{


public:

    virtual ~IProcessingDevice() = default;
    virtual void AcceptRequirement( Requirement& requirement ) = 0;
    virtual void FinishService() = 0;

    void TimeSubstraction(double time)
    {
        for(auto& req: requirements_)
        {
            req.service_time_ -= time;
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
            return min_service_time_ ;
        }
        else
        {
            return -1;
        }
    }

protected:

    double min_service_time_;
    std::vector< Requirement > requirements_;
    double mu_;

};

class ExponentialProcessingDevice : public IProcessingDevice
{


public:

    ExponentialProcessingDevice( double mu ) : service_distr_( mu )
    {
        mu_ = mu;
    };

    void AcceptRequirement( Requirement& requirement ) override;

    void FinishService() override;

    //Для статистики
    void recordVectorState();
    const std::map<size_t, size_t>& getVectorStats() const;
    void resetStats();


private:

    std::exponential_distribution<double> service_distr_;
    std::map<size_t,size_t> vector_stats_;
};

#endif // PROCESSING_DEVICE_H
