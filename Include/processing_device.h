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

};

class ExponentialProcessingDevice : public IProcessingDevice
{


public:

    ExponentialProcessingDevice( double mu ) : mu_( mu ), service_distr_( mu_ ) {}

    void AcceptRequirement( Requirement& requirement ) override;

private:

    double mu_;
    std::exponential_distribution< double > service_distr_;

};

class GammaProcessingDevice : public IProcessingDevice
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
