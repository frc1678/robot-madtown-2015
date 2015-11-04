#include "claw_plant.h"

#define abs(a) ((a) > 0 ? (a) : -(a))
#define min(a, b) ((a) < (b) ? (a) : (b))
#define max(a, b) ((a) > (b) ? (a) : (b))
#define rangeify(a, b, c) (max(a, min(b, c)))

Angle min = 0.0 * rad;
Angle max = 2.1 * rad;
constexpr double kF = -31.857;
constexpr double kM = 6.747;

DrivetrainPlant::DrivetrainPlant() {
  _dynamics <<  0, 0, 0, 0,
                0, 0, 0, 0,
                0, 0, 0, 0;
}

DrivetrainPlant::ClawPlant(Angle initial_position, AngularVelocity initial_velocity) : _state(2), _dynamics(2, 2), _control(2, 1) {
  _offset = -initial_position;
  _dynamics(0, 0) = 0.0;
  _dynamics(0, 1) = 1.0;
  _dynamics(1, 0) = 0.0;
  _dynamics(1, 1) = kF;

  _control(0) = 0.0;
  _control(1) = kM;

  _state(0) = initial_position.to(rad);
  _state(1) = initial_velocity.to(rad/s);
}

ClawPlant::~ClawPlant() {

}

void ClawPlant::update(Time dt, Voltage voltage) {
  _state += (_dynamics * _state + voltage.to(V) * _control) * dt.to(s);
  _state(0) = rangeify(min.to(rad), _state(0), max.to(rad));
}

bool ClawPlant::max_hall_triggered() {
  return abs((angle() - max).to(rad)) < .01;
}

bool ClawPlant::min_hall_triggered() {
  return abs((angle() - min).to(rad)) < .01;
}

Angle ClawPlant::angle() {
  return _state(0) * rad;
}

AngularVelocity ClawPlant::angular_velocity() {
  return _state(1) * rad / s;
}

Angle ClawPlant::encoder() {
  return angle() + _offset;
}
