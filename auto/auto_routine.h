#ifndef AUTO_ROUTINE_H
#define AUTO_ROUTINE_H

#include <tuple>
#include "claw/claw_controller.h"

class AutoRoutine {
private:
  ClawController _claw_controller;
public:
  enum State {
    INITIALIZING,
    CALIBRATING,
    DRIVING,
    SCORING,
    ESTOP
  };
  std::tuple<Voltage, Voltage, Voltage> update(bool enabled, Length distance, Angle claw_angle, bool min_hall, bool max_hall);
};

#endif 
