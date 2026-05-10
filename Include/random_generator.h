#ifndef RANDOM_GENERATOR_H
#define RANDOM_GENERATOR_H

#include <random>

class RandomGenerator
{


public:

    static std::mt19937_64& get()
    {
        static std::mt19937_64 engine( std::random_device{}() );
        return engine;
    }

    static void seed( unsigned int s )
    {
        get().seed( s );
    }

private:

    static std::mt19937_64 engine;

    RandomGenerator() = default;
    ~RandomGenerator() = default;
    RandomGenerator( const RandomGenerator& ) = delete;
    RandomGenerator& operator=( const RandomGenerator& ) = delete;
};

#endif // RANDOM_GENERATOR_H
