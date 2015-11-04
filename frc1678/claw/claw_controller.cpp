#include "claw_controller.h"

#define abs(a) ((a) > 0 ? a : -a)
#define min(a, b) ((a) < (b) ? (a) : (b))
#define max(a, b) ((a) > (b) ? (a) : (b))
#define rangeify(a, b, c) (max(a, min(b, c)))

ClawController::ClawController() {
  _state = INITIALIZING;
  _goal = 0;
  _offset = 0;
  _error_last = 0;
}

Voltage ClawController::update(Angle encoder_angle, bool min_hall, bool max_hall, bool enabled) {
  Voltage voltage = 0*V;
  Angle current_angle = encoder_angle + _offset;

  Angle error_p = (_goal - current_angle);
  AngularVelocity error_d = (error_p - _error_last) / dt;
  switch (_state) {
  case CALIBRATING:
    if (min_hall) {
      voltage = 0*V;
      _offset = -encoder_angle;
      _state = RUNNING;
    }
    else {
      voltage = -4*V;
    }
    break;
  case RUNNING:
    voltage = k_proportional * error_p + k_derivative * error_d;
    _error_last = encoder_angle;
    break;
  case INITIALIZING:
    if (enabled) {
      _state = CALIBRATING;
    }
    break;
  case ESTOP:
    break;
  }
  return rangeify(-12.0*V, voltage, 12.0*V);
}

bool ClawController::running() {
  return _state == RUNNING;
}

void ClawController::set_goal(Angle goal) {
  _goal = goal;
}
