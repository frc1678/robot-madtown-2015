#ifndef DRIVE_PLANT_H
#define DRIVE_PLANT_H

#include "eigen/include/Core"
#include "unitscpp/unitscpp.h"

class DrivePlant {
public:
  DrivePlant();
  ~DrivePlant();
  void update(Time dt, Voltage left_voltage, Voltage right_voltage);
  Angle angle();
  AngularVelocity angular_velocity();
  Length distance();
  Length distance_right();
  Length distance_left();
  Velocity velocity_left();
  Velocity velocity_right();
  // void shift(bool high);
private:
  Eigen::Vector4d _state;
  Eigen::Matrix<double, 4, 4> _dynamics;
  Eigen::Matrix<double, 4, 2> _control;
};

#endif
