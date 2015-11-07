#include "claw_plant.h"

#define abs(a) ((a) > 0 ? (a) : -(a))
#define min(a, b) ((a) < (b) ? (a) : (b))
#define max(a, b) ((a) > (b) ? (a) : (b))
#define rangeify(a, b, c) (max(a, min(b, c)))

Angle min = 0.0 * rad;
Angle max = 2.1 * rad;
constexpr double kF = -31.857;
constexpr double kM = 6.747;

ClawPlant::ClawPlant() : ClawPlant(0.0*rad, 0.0*rad/s) {}

ClawPlant::ClawPlant(Angle initial_position, AngularVelocity initial_velocity) : _state(2), _dynamics(2, 2), _control(2, 1) {
  _offset = -initial_position;
  _dynamics << 0.0, 1.0,
              0.0, kF;

  _control(0) = 0.0;
  _control(1) = kM;

  _state(0) = initial_position.to(rad);
  _state(1) = initial_velocity.to(rad/s);
}

ClawPlant::~ClawPlant() {

}

void ClawPlant::set_angle(Angle theta) {
  _state(0) = theta.to(rad);
}

void ClawPlant::set_velocity(AngularVelocity omega) {
  _state(1) = omega.to(rad/s);
}

void ClawPlant::update(Time dt, Voltage voltage) {
  // If x is the current state,
  // x_dot is the time derivative of the state,
  // A is a matrix representing the defining differential equation of the unforced system,
  // u is the input given from the controller (in this case voltage),
  // and B a matrix showing how the input affects the system
  // x_dot = A*x + B*u
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
