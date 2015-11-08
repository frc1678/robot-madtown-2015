#include "drive_plant.h"

#define abs(a) ((a) > 0 ? (a) : -(a))
#define min(a, b) ((a) < (b) ? (a) : (b))
#define max(a, b) ((a) > (b) ? (a) : (b))
#define rangeify(a, b, c) (max(a, min(b, c)))

const double kM = 1;
const double kF = 1;
const Length drive_width = 25*in;

DrivePlant::DrivePlant() {
  _dynamics << 	0.0, 0.0, 1.0, 0.0,
		0.0, 0.0, 0.0, 1.0,
		0.0, 0.0, -kF, 0.0,
		0.0, 0.0, 0.0, -kF;

  _control <<	0.0, 0.0,
		0.0, 0.0,
		kM, 0.0,
		0.0, kM;
}

DrivePlant::~DrivePlant() {

}

void DrivePlant::update(Time dt, Voltage voltage_left, Voltage voltage_right) {
  Eigen::Vector2d u;
  u(0) = voltage_left.to(V);
  u(1) = voltage_right.to(V);
  _state += (_dynamics * _state + _control * u) * dt.to(s);
}

Angle DrivePlant::angle() {
  return 2*(distance_right() - distance_left()) / drive_width;
}

Length DrivePlant::distance_right() {
  return _state(1)*m;
}

Length DrivePlant::distance_left() {
  return _state(0)*m;
}

Velocity DrivePlant::velocity_left() {
  return _state(2)*m/s;
}

Velocity DrivePlant::velocity_right() {
  return _state(3)*m/s;
}

AngularVelocity DrivePlant::angular_velocity() {
  return 2*(velocity_right() - velocity_left()) / drive_width;
}

