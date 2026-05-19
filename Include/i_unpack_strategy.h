#ifndef I_UNPACK_STRATEGY_H
#define I_UNPACK_STRATEGY_H

#include <Include/random_generator.h>

#include <vector>
#include <random>

class IUnpackStrategy
{


public:

    virtual ~IUnpackStrategy() = default;
    virtual int GetDescendantsCount() = 0;
};

class PoissonUnpackStrategy : public IUnpackStrategy
{


public:

    PoissonUnpackStrategy( const double lambda ) : lambda_( lambda ), distr_( lambda ) {}

    int GetDescendantsCount() override
    {
        return distr_( RandomGenerator::get() );
    }


private:

    double lambda_;
    std::poisson_distribution< int > distr_;

};

class DiscreteUnpackStrategy : public IUnpackStrategy
{


public:

    DiscreteUnpackStrategy( const std::vector< double >& probs ) : probabilities_( probs ), distr_( 0.0, 1.0 ) {}

    int GetDescendantsCount() override
    {
        double alpha = distr_( RandomGenerator::get() );
        double sum = 0.0;

        for( size_t i = 0; i < probabilities_.size(); i++ )
        {
            sum += probabilities_[ i ];
            if ( sum > alpha )
            {
                return static_cast< int >( i );
            }
        }
        return static_cast< int >( probabilities_.size() ) - 1; /// Результат затычка
    }

private:

    std::vector< double > probabilities_;
    std::uniform_real_distribution< double > distr_;
};

class DiscreteUniformUnpackStrategy : public IUnpackStrategy
{

public:

    DiscreteUniformUnpackStrategy( const double a, const double b ) : a_( a ), b_( b ), distr_( a, b ) {}

    int GetDescendantsCount() override
    {
        return distr_( RandomGenerator::get() );
    }

private:
    double a_;
    double b_;
    std::uniform_int_distribution< int > distr_;
};

class GeometricUnpackStrategy : public IUnpackStrategy
{
public:

    GeometricUnpackStrategy( const double p ) : p_( p ), distr_( p ) {}

    int GetDescendantsCount() override
    {
        return distr_( RandomGenerator::get() );
    }

private:
    double p_;
    std::geometric_distribution< int > distr_;
};

#endif // I_UNPACK_STRATEGY_H
