#include <Include/requirement_handler.h>

std::vector < Requirement > RequirementHandler::UnpackRequirement()
{
    k = GenerateK();

    if ( k <= 0 )
    {
        return {};
    }

    return CreateKRequirement( k );
}

Requirement RequirementHandler::CreateRequirement()
{
    Requirement req = Requirement( requirements_amount_, 0.0);
    ++requirements_amount_;
    return req;
}

std::vector < Requirement > RequirementHandler::CreateKRequirement( unsigned int k )
{
    std::vector < Requirement > new_requirements;
    new_requirements.reserve(k);
    for( size_t i = 0; i < k; i++ )
    {
        new_requirements.emplace_back(CreateRequirement());
    }

    return new_requirements;
}

int RequirementHandler::GenerateK()
{
    return k_distr_( RandomGenerator::get() );
}
