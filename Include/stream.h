#ifndef STREAM_H
#define STREAM_H

#include <Include/random_generator.h>

class IStream
{


public:

    virtual ~IStream() = default;
    virtual double GenerateTau() = 0;
    virtual int RequestNumber() = 0;
};

class PoissonStream : public IStream
{


public:


    PoissonStream( double lambda ): lambda_( lambda ), distr_( lambda ) {};

    double GenerateTau() override
    {
        return distr_( RandomGenerator::get() );
    }

    // Заглушка в виде одной заявки за единицу времени
    int RequestNumber() override
    {
        return 1;
    }


private:

    double lambda_;
    std::exponential_distribution < double > distr_;
};

#endif // STREAM_H
