#include "WPILib.h"
#include "components/RobotParts.h"
#include "components/RobotButtons.h"
#include "claw/claw_controller.h"
#include "drivetrain/drive_controller.h"

class Robot: public IterativeRobot
{
	Joystick* right, *left, *manipulator;
	RobotParts* parts;
	RobotButtons* buttons;
	DriveController drive_control;
	ClawController claw_control;
	bool open;

private:

	void RobotInit()
	{
		right = new Joystick(0);
		left = new Joystick(1);
		manipulator = new Joystick(2);
		buttons = new RobotButtons(left, right, manipulator);
		parts = new RobotParts();
	}

	void DisabledPeriodic() {
		SmartDashboard::PutNumber("Claw Encoder", parts->clawEncoder->Get());
		SmartDashboard::PutNumber("Claw Angle", (parts->clawEncoder->Get() - 376) / 11.8 * 3.14159 / 180.0);
	}

	void AutonomousInit()
	{

	}

	void AutonomousPeriodic()
	{

	}

	void TeleopInit()
	{

	}

	void TeleopPeriodic()
	{
		parts->openClaw->Set(buttons->clawToggle->ButtonPressed());
		parts->drivetrain->TankDrive(left->GetY(), right->GetY());
		parts->clawRollers->Set(manipulator->GetRawAxis(1));
		parts->tuskA->Set(manipulator->GetRawAxis(3) - manipulator->GetRawAxis(2));
		parts->tuskB->Set(manipulator->GetRawAxis(2) - manipulator->GetRawAxis(3));
//		claw_control.set_goal(0*rad);
//		Voltage claw_voltage = claw_control.update(parts->clawEncoder->Get() / 11.8 * deg, false, false, true);
//		if (claw_voltage > 4*V) {
//			claw_voltage = 4*V;
//		}
//		if (claw_voltage < -4*V) {
//			claw_voltage = -4*V;
//		}
//		parts->moveClawA->Set(claw_voltage.to(pwm));
//		parts->moveClawB->Set(claw_voltage.to(pwm));
	}

	void TestPeriodic()
	{

	}
};

START_ROBOT_CLASS(Robot);
