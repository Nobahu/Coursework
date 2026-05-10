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

class GeometricStream : public IStream
{


public:
    GeometricStream( double p ) : p_( p ), distr_( p ) {}

    double GenerateTau() override
    {

        return static_cast< double >( distr_( RandomGenerator::get() ) + 1.0);
    }


private:
    double p_;
    std::geometric_distribution< int > distr_;

};

#endif // STREAM_H
