#include <WPILib.h>
#include <thread>

class MainRobot : public IterativeRobot {
    RobotDrive* drivetrain;
    Joystick* stickL, *stickR;

  public:
    MainRobot() {
      drivetrain = new RobotDrive(2, 1);
    }
    virtual ~MainRobot() {
    }
    void RobotInit() override {
    }
    void DisabledInit() override {
    }
    void DisabledPeriodic() override {
    }
    void AutonomousInit() override {
    }
    void AutonomousPeriodic() override {
    }
    void TeleopInit() override {
    }
    void TeleopPeriodic() override {
    }
};


START_ROBOT_CLASS(MainRobot);
