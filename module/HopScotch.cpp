#include "HopScotch.h"

HopScotch::HopScotch(Controller& ctrler_, MoveStraight& linear_, LineTracer& tracer_, Rotation& yaw_)
    : ctrler(ctrler_), linear(linear_), tracer(tracer_), yaw(yaw_)
{}

void HopScotch::cnvrtC8E2Motion(std::vector<std::vector<int>>& c8es_, Direction direct_)
{

}