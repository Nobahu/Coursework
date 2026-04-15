#ifndef REQUIREMENT_HANDLER_H
#define REQUIREMENT_HANDLER_H

#include <Include/requirement.h>
#include <Include/random_generator.h>

class RequirementHandler
{


public:

    RequirementHandler( double lambda, double u_prob ) : distr_( lambda ), requirements_amount_( 0 ),
        unpack_probability_( u_prob ),
        random_prob_( 0.0, 1.0 ) {}

    std::vector < Requirement >  UnpackRequirement();

    Requirement CreateRequirement();
    std::vector < Requirement > CreateKRequirement( unsigned int k );

    int GenerateK();


private:

    int k = 0;

    unsigned int requirements_amount_;
    double unpack_probability_;

    std::uniform_real_distribution < double > random_prob_;
    std::poisson_distribution < int > distr_;

};

#endif // REQUIREMENT_HANDLER_H
