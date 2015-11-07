#ifndef CLAW_PLANT_H
#define CLAW_PLANT_H

#include "eigen/include/Core"
#include "unitscpp/unitscpp.h"

class ClawPlant {
public:
  ClawPlant();
  ClawPlant(Angle initial_position, AngularVelocity initial_velocity);
  ~ClawPlant();
  void update(Time dt, Voltage voltage);
  Angle angle();
  AngularVelocity angular_velocity();
  Angle encoder();
  bool max_hall_triggered();
  bool min_hall_triggered();

private:
  Angle _offset;
  Eigen::Vector2d _state;
  Eigen::Matrix<double, 2, 2> _dynamics;
  Eigen::Matrix<double, 2, 1> _control;
};

#endif
