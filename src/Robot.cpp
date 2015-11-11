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
		_auto_state = 0;
		_claw.set_goal(_claw.ground_pickup);
		drive_control.set_distance_goal(13*ft);
	}

	void AutonomousPeriodic() {
		_claw.update();
		Voltage u;
		SmartDashboard::PutNumber("state", _auto_state);
		parts->shifting->Set(DoubleSolenoid::Value::kForward);
		Voltage u_left, u_right;
		switch(_auto_state) {
		case 0:
			std::tie(u_left, u_right) = drive_control.update(parts->leftEncoder->Get()*click, -parts->rightEncoder->Get()*click);
			parts->drivetrain->TankDrive(-u_left.to(pwm), -u_right.to(pwm), false);
			if (drive_control.done()) {
				_auto_state = 1;
			}
			break;
		case 1:
			parts->drivetrain->TankDrive(0.0, 0.0);
			_claw.run_intakes(1*pwm);
			break;
		case 2:
			_claw.run_intakes(0);
			break;
		}
	}

	void TeleopInit() {
		_claw.set_goal(0 * rad);
	}

	void TeleopPeriodic() {
		buttons->UpdateButtons();
		SmartDashboard::PutNumber("Claw Angle", _claw.angle().to(rad));
		if (buttons->hp_front->ButtonPressed()) {
			_claw.set_goal(_claw.human_pickup_forward);
		}
		if (buttons->hp_reverse->ButtonPressed()) {
			_claw.set_goal(_claw.human_pickup_reverse);
		}
		if (buttons->pickup->ButtonPressed()) {
			_claw.set_goal(_claw.ground_pickup);
		}
		if (buttons->kiss_pass->ButtonPressed()) {
			_claw.set_goal(.3*rad);
		}
		if (buttons->open_claw->ButtonPressed()) {
			_claw.open();
		}
		else {
			_claw.close();
		}

		if (buttons->shift_low->ButtonPressed()) {
			parts->shifting->Set(DoubleSolenoid::Value::kForward);
		}
		else if (buttons->shift_high->ButtonPressed()) {
			parts->shifting->Set(DoubleSolenoid::Value::kReverse);
		}
		_claw.run_intakes((manipulator->GetRawAxis(2) - manipulator->GetRawAxis(3)) * pwm);
		_claw.update();

		parts->drivetrain->TankDrive(left->GetY(), right->GetY());
	}

	void TestPeriodic() {

	}
};

START_ROBOT_CLASS(Robot);
