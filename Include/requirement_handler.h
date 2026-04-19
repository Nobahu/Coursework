#ifndef REQUIREMENT_HANDLER_H
#define REQUIREMENT_HANDLER_H

#include <Include/requirement.h>
#include <Include/random_generator.h>

class RequirementHandler
{


public:

    RequirementHandler( double lambda ) : k_distr_( lambda ), requirements_amount_( 0 ) {}

    std::vector< Requirement >  UnpackRequirement();

    Requirement CreateRequirement();
    std::vector< Requirement > CreateKRequirement( unsigned int k );

    int GenerateK();


private:

    int k = 0;

    unsigned int requirements_amount_;

    std::poisson_distribution < int > k_distr_;

};

#endif // REQUIREMENT_HANDLER_H
