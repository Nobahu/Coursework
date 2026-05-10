#ifndef REQUIREMENT_HANDLER_H
#define REQUIREMENT_HANDLER_H

#include <Include/requirement.h>
#include <Include/random_generator.h>
#include <Include/i_unpack_strategy.h>

#include <memory>

class RequirementHandler
{


public:

    RequirementHandler( std::vector< std::unique_ptr< IUnpackStrategy > > unpack_strategies ) : requirements_amount_( 0 ), unpack_strategies_( std::move( unpack_strategies ) ) {}

    std::vector< Requirement >  UnpackRequirement( size_t processing_device_index );
    Requirement CreateRequirement();
    std::vector< Requirement > CreateKRequirement( unsigned int k );


private:

    unsigned int requirements_amount_;
    std::vector< std::unique_ptr< IUnpackStrategy > > unpack_strategies_;

};

#endif // REQUIREMENT_HANDLER_H
