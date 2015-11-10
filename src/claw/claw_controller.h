#ifndef CLAW_CONTROLLER_H
#define CLAW_CONTROLLER_H

#include "unitscpp/unitscpp.h"
#include "WPILib.h"

class ClawController {
 enum State { INITIALIZING = 0, CALIBRATING = 1, RUNNING = 2, ESTOP = 3 };
public:
  ClawController();
  Voltage update(Angle encoder, bool min_hall, bool max_hall, bool enabled);
  bool running();
  void set_goal(Angle goal);
  Angle _offset;
private:
  void run_intake(Voltage speed);
  void spit_intake(Voltage speed); 
  Angle _goal;
  Angle _error_last;

  Time dt = .005*s;

  // Unit of V/rad and Vs/rad, respectively
  Units<2,-3,1,-1> k_proportional = 15*V/rad;
  Units<2,-2,1,-1> k_derivative = 0*V*s/rad;

  State _state;
};
#endif
