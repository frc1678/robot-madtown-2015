/*
 * RobotParts.cpp
 *
 *  Created on: Mar 23, 2015
 *      Author: Citrus Circuits
 */

#include "components/RobotParts.h"

RobotParts::RobotParts() {
	// Compressor
	compressor = new Compressor(0);

	// Claw
	tuskA = new VictorSP(6);
	tuskB = new VictorSP(3);
	clawRollers = new VictorSP(0);
	openClaw = new Solenoid(5);
	moveClawA = new VictorSP(5);
	moveClawB = new VictorSP(4);
	minHall = new DigitalInput(0);

	// Encoders
	leftEncoder = new Encoder(12, 13);
	rightEncoder = new Encoder(10, 11);
	clawEncoder = new Encoder(14, 15);

	leftDT = new VictorSP(2);
	rightDT = new VictorSP(1);

	drivetrain = new RobotDrive(leftDT, rightDT);
	drivetrain->SetSafetyEnabled(false);

	shifting = new DoubleSolenoid(1, 2);
}

RobotParts::~RobotParts() {


	delete rightEncoder;
	delete leftEncoder;

	delete leftDT;
	delete rightDT;

	delete drivetrain;

}

