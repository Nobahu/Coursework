#include <Include/requirement_handler.h>

std::vector < Requirement > RequirementHandler::UnpackRequirement()
{
    if( random_prob_( RandomGenerator::get()) >= unpack_probability_ )
    {
        return {};
    }
    k = GenerateK();

    if ( k <= 0 )
    {
        return {};
    }

    return CreateKRequirement( k );
}

Requirement RequirementHandler::CreateRequirement()
{
    Requirement req = Requirement();
    req.number = requirements_amount_;
    ++requirements_amount_;
    return req;
}

std::vector < Requirement > RequirementHandler::CreateKRequirement( unsigned int k )
{
    std::vector < Requirement > new_requirements;

    for( size_t i = 0; i < k; i++ )
    {
        Requirement req = Requirement();
        req.number = requirements_amount_;
        ++requirements_amount_;
        new_requirements.push_back( req );
    }

    return new_requirements;
}

int RequirementHandler::GenerateK()
{
    return distr_( RandomGenerator::get() );
}
