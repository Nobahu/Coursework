#include <Include/requirement_handler.h>

std::vector < Requirement > RequirementHandler::UnpackRequirement( size_t processing_device_index )
{
    int k = unpack_strategies_[ processing_device_index ]->GetDescendantsCount();
    if ( k <= 0 )
        return {};

    return CreateKRequirement( k );
}

Requirement RequirementHandler::CreateRequirement()
{
    return Requirement( requirements_amount_++, 0.0 );
}

std::vector < Requirement > RequirementHandler::CreateKRequirement( unsigned int k )
{
    std::vector < Requirement > new_requirements;
    new_requirements.reserve( k );
    for( size_t i = 0; i < k; i++ )
    {
        new_requirements.emplace_back( CreateRequirement() );
    }

    return new_requirements;
}
