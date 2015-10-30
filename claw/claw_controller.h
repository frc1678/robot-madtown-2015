#ifndef CLAW_CONTROLLER_H
#define CLAW_CONTROLLER_H

class ClawController {
public:
    double Update(double dt, double claw_position, double claw_velocity);
};

#endif