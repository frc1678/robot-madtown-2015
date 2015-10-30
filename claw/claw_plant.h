#ifndef CLAW_PLANT_H
#define CLAW_PLANT_H

class ClawPlant {
private:
    double theta = 0.0;
    double omega = 0.0;
    static constexpr double kF = -31.857;
    static constexpr double kM = 6.747;
    static constexpr double min = 0.0;
    static constexpr double max = 2.1;
public:
    void Update(double dt, double voltage);
    double GetAngle();
    bool IsMaxHallTriggered();
    bool IsMinHallTriggered();
    double GetAngularVelocity();
};

#endif