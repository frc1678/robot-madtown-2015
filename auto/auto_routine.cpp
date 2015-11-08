#include "auto_routine.h"

std::tuple<Voltage, Voltage, Voltage> AutoRoutine::update(bool enabled, Length distance, Angle claw_angle, bool min_hall, bool max_hall) {
  Voltage v_left, v_right, v_claw;
  switch (_state) {
  case INITIALIZING:
    if (enabled) {
      _state = CALIBRATING;
    }
    break;
  case CALIBRATING:
    if (_claw_controller.running()) {
	_state = DRIVING;
    }
    else {
      _claw_controller.update(claw_angle, min_hall, max_hall, true);
    }
    break;
  case DRIVING:
    // Drive forward a specific distance and move the claw to scoring position
    break;
  case SCORING:
    // Spit out the ball
  }
  return std::tie(v_left, v_right, v_claw);
}
