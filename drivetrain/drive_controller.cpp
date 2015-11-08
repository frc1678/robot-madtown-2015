#include "drive_controller.h"


DriveController::DriveController() {
}

DriveController::~DriveController() {
}

Voltage DriveController::update(Length left_encoder, Length right_encoder){
  Length error = goal_distance - (left_encoder + right_encoder)/2;
  Time dT = 0.005*s;
  auto d_error = (last_error-error)/dT;
  last_error = error;
  return (kP*error + kD*d_error);
}

void DriveController::set_distance_goal(Length distance) { 
goal_distance = distance;
}

