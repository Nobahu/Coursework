#ifndef REQUIREMENT_H
#define REQUIREMENT_H

struct Requirement
{
    int number_;
    double service_time_;

    Requirement( int number, double service_time ) : number_( number ), service_time_( service_time ) {}
};

#endif // REQUIREMENT_H
