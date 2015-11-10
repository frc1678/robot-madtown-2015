#include "WPILib.h"
#include "components/RobotParts.h"
#include "components/RobotButtons.h"
#include "claw/claw_subsystem.h"
#include "drivetrain/drive_controller.h"

class Robot: public IterativeRobot {
	Joystick* right, *left, *manipulator;
	RobotParts* parts;
	RobotButtons* buttons;
	DriveController drive_control;
	ClawSubsystem _claw;
	int _auto_state;
	bool open;

private:

	void RobotInit() {
		right = new Joystick(0);
		left = new Joystick(1);
		manipulator = new Joystick(2);
		buttons = new RobotButtons(left, right, manipulator);
		parts = new RobotParts();
		_claw = ClawSubsystem(parts);
	}

	void DisabledPeriodic() {
		SmartDashboard::PutNumber("Claw Encoder", parts->clawEncoder->Get());
		SmartDashboard::PutNumber("Claw Angle", _claw.angle().to(rad));
	}

	void AutonomousInit() {
		_claw.set_goal(_claw.ground_pickup);
	}

	void AutonomousPeriodic() {
		_claw.update();
		Voltage u;
		switch(_auto_state) {
		case 0:
			drive_control.set_distance_goal(16*ft);
			u = drive_control.update(parts->leftEncoder->Get()*click, -parts->rightEncoder->Get()*click);
			parts->drivetrain->TankDrive(-u.to(pwm), -u.to(pwm), false);
			if (drive_control.done()) {
				_auto_state = 1;
			}
			break;
		case 1:
			parts->drivetrain->TankDrive(0.0, 0.0);
			_claw.run_intakes(-1);
			break;
		case 2:
			_claw.run_intakes(0);
			break;
		}
	}

	void TeleopInit() {
		_claw.set_goal(2.5 * rad);
	}

	void TeleopPeriodic() {
		SmartDashboard::PutNumber("Claw Angle", _claw.angle().to(rad));
		if (manipulator->GetRawButton(1)) {
			_claw.set_goal(_claw.human_pickup_forward);
		}
		if (manipulator->GetRawButton(2)) {
			_claw.set_goal(_claw.human_pickup_reverse);
		}
		if (manipulator->GetRawButton(3)) {
			_claw.set_goal(_claw.ground_pickup);
		}
		_claw.run_intakes(manipulator->GetRawAxis(2) - manipulator->GetRawAxis(3));
		_claw.update();
	}

	void TestPeriodic() {

	}
};

START_ROBOT_CLASS(Robot);
