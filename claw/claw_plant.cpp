#include "claw_plant.h"

#include <iostream>

#define abs(a) ((a) > 0 ? a : -a)
#define min(a, b) ((a) < (b) ? (a) : (b))
#define max(a, b) ((a) > (b) ? (a) : (b))
#define rangeify(a, b, c) (max(a, min(b, c)))

void ClawPlant::Update(double dt, double voltage) {
    theta += omega * dt;
    theta = rangeify(min, theta, max);
    omega += kM * voltage * dt + kF * omega * dt;
}

bool ClawPlant::IsMaxHallTriggered() {
    return abs(theta - max) < .03;
}

bool ClawPlant::IsMinHallTriggered() {
    return abs(theta - min) < .03;
}


double ClawPlant::GetAngle() {
    return theta;
}

double ClawPlant::GetAngularVelocity() {
    return omega;
}