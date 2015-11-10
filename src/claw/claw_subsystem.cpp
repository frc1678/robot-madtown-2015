/*
 * claw_subsystem.cpp
 *
 *  Created on: Nov 9, 2015
 *      Author: Citrus CAD
 */

#include <claw/claw_subsystem.h>

Angle ClawSubsystem::human_pickup_forward = 1*rad;
Angle ClawSubsystem::ground_pickup = 0*rad;
Angle ClawSubsystem::human_pickup_reverse = 2.5*rad;

ClawSubsystem::ClawSubsystem(RobotParts* parts) : parts(parts) {
}

ClawSubsystem::ClawSubsystem() {
	parts = nullptr;
}

ClawSubsystem::~ClawSubsystem() {
	// TODO Auto-generated destructor stub
}

void ClawSubsystem::set_goal(Angle goal) {
	_controller.set_goal(goal);
}

void ClawSubsystem::update() {
	Voltage claw_voltage = _controller.update(
			parts->clawEncoder->Get() / 11.8 * deg, !parts->minHall->Get(),
			false, true);
	parts->clawRollers->Set(-_intake_speed.to(pwm));
	parts->tuskA->Set(_intake_speed.to(pwm));
	parts->tuskB->Set(-_intake_speed.to(pwm));
	parts->moveClawA->Set(-claw_voltage.to(pwm));
	parts->moveClawB->Set(-claw_voltage.to(pwm));
}

void ClawSubsystem::open() {
	parts->openClaw->Set(true);
}

void ClawSubsystem::close() {
	parts->openClaw->Set(false);
}

void ClawSubsystem::run_intakes(Voltage speed) {
	_intake_speed = speed;
}

Angle ClawSubsystem::angle() {
	return parts->clawEncoder->Get() / 11.8 * deg + _controller._offset;
}
