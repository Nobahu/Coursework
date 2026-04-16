#ifndef PROCESSING_DEVICE_H
#define PROCESSING_DEVICE_H

#include <Include/requirement.h>
#include <Include/random_generator.h>

#include <queue>
#include <map>

class IProcessingDevice
{


public:

    virtual ~IProcessingDevice() = default;
    virtual void AcceptRequirement( Requirement& requirement ) = 0;
    virtual void FinishService() = 0;

    virtual double getServiceTime() = 0;
    virtual void recordQueueState() = 0;
    virtual void resetStats() = 0;


protected:

    virtual void GenerateDelta() = 0;
};

class ExponentialProcessingDevice : public IProcessingDevice
{


public:

    ExponentialProcessingDevice( double mu ) : mu_( mu ), distr_( mu ), delta_( -1 ) {};

    void AcceptRequirement( Requirement& requirement ) override;

    void FinishService() override;

    double getServiceTime() override;

    void GenerateDelta() override;

    //Для статистики
    void recordQueueState() override;
    const std::map<size_t, size_t>& getQueueStats() const;
    void resetStats() override;


private:

    double mu_;
    double delta_;
    std::exponential_distribution < double > distr_;
    std::queue < Requirement > requirements_;

    std::map<size_t,size_t> queue_stats_;
};

#endif // PROCESSING_DEVICE_H
