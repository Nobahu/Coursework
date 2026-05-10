#ifndef STREAM_H
#define STREAM_H

#include <Include/random_generator.h>

class IStream
{


public:

    virtual ~IStream() = default;
    virtual double GenerateTau() = 0;
};

class PoissonStream : public IStream
{


public:


    PoissonStream( double lambda ): lambda_( lambda ), distr_( lambda ) {};

    double GenerateTau() override
    {
        return distr_( RandomGenerator::get() );
    }


private:

    double lambda_;
    std::exponential_distribution < double > distr_;
};

class GammaStream : public IStream
{


public:
    GammaStream( double k, double theta ) : k_( k ), theta_( theta ), distr_( k, theta ) {}

    double GenerateTau() override
    {

        return distr_( RandomGenerator::get() );
    }


private:
    double k_;
    double theta_;
    std::gamma_distribution< double > distr_;

};

#endif // STREAM_H
