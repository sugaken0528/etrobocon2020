#ifndef HOPSCOTCH_H
#define HOPSCOTCH_H

#include "Controller.h"
#include "MoveStraight.h"
#include "LineTracer.h"
#include "Rotation.h"

enum Direction { North, NEast, East, SEast, South, SWest, West, NWest };

class HopScotch {
 public:
  hopscotch(Controller& ctrler_, MoveStraight& linear_, LineTracer& tracer_, Rotation& yaw_);
  void cnvrtC8E2Motion(std::vector<std::vector<int>>& c8e_, Direction direct_);

 private:
};

#endif  // HOPSCOTCH_H