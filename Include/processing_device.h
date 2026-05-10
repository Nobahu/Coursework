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


    virtual void AcceptRequirement( Requirement& requirement ) = 0;
    void FinishService();

    void TimeSubstraction( double time );
    double GetMinimalServiceTime();

    const std::map< size_t, size_t >& getVectorStats() const;
    void resetStats();


protected:

    void recordVectorState();

    double min_service_time_;
    std::vector< Requirement > requirements_;
    std::map< size_t, size_t > map_stats_;
    double mu_;

};

class ExponentialProcessingDevice : public ProcessingDevice
{


public:

    ExponentialProcessingDevice( double mu ) : mu_( mu ), service_distr_( mu_ ) {}

    void AcceptRequirement( Requirement& requirement ) override;

private:

    double mu_;
    std::exponential_distribution< double > service_distr_;

};

class GammaProcessingDevice : public ProcessingDevice
{


public:

    GammaProcessingDevice( double k, double theta) : k_( k ), theta_( theta ), service_distr_( k, theta ) {}

    void AcceptRequirement( Requirement& requirement ) override;

private:

    double k_;
    double theta_;
    std::gamma_distribution< double > service_distr_;

};


#endif // PROCESSING_DEVICE_H
