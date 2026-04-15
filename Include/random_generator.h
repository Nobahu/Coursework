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
};

#endif // RANDOM_GENERATOR_H
