#ifndef DRIVETRAIN_PLANT_H
#define DRIVETRAIN_PLANT_H

#include "Eigen/Core"
#include "unitscpp/unitscpp.h"

class DrivetrainPlant {
public:
  DrivetrainPlant();
  ~DrivetrainPlant();
  void update(Time dt, Voltage voltage_left, Voltage voltage_right);
  void update(Time dt, Eigen::VectorXd u);
  Length distance_right();
  Velocity velocity_right();
  Length distance_left();
  Velocity velocity_left();

private:
  Eigen::Vector<double, 4> _state;
  Eigen::Matrix<double, 4, 4> _dynamics;
  Eigen::Matrix<double, 4, 2> _control;
};

#endif
