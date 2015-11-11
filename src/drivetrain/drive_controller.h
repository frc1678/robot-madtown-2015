#ifndef DRIVE_CONTROLLER_H
#define DRIVE_CONTROLLER_H
#include <tuple>
#include "unitscpp/unitscpp.h"
#include "motion_profile.h"
#include "WPILib.h"

class DriveController {
  Length goal_distance;
  Units<1,-3,1,-1> kP = 3*V/m;
  Units<1,-2,1,-1> kD = 1*V*s/m;
  Length last;

  Length _offset_right, _offset_left;

  bool started = false;

  MotionProfile _profile;
  Timer t;
public:
  DriveController();
  ~DriveController();
  std::tuple<Voltage, Voltage> update(Length left_encoder, Length right_encoder);
  bool done();
  void set_distance_goal(Length distance);
};
#endif
