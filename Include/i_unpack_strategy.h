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

class GammaUnpackStrategy : public IUnpackStrategy
{

public:

    GammaUnpackStrategy( const double k, const double theta ) : k_( k ), theta_( theta ), distr_( k, theta ) {}

    int GetDescendantsCount() override
    {
        return static_cast< int >( std::round( distr_( RandomGenerator::get() ) ) );
    }

private:
    double k_;
    double theta_;
    std::gamma_distribution< double > distr_;
};

#endif // I_UNPACK_STRATEGY_H
