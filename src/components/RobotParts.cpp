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

	// Encoders
	leftEncoder = new Encoder(12, 13);
	rightEncoder = new Encoder(10, 11);

	leftDT = new VictorSP(2);
	rightDT = new VictorSP(1);

	drivetrain = new RobotDrive(leftDT, rightDT);
	drivetrain->SetSafetyEnabled(false);


}

RobotParts::~RobotParts() {


	delete rightEncoder;
	delete leftEncoder;

	delete leftDT;
	delete rightDT;

	delete drivetrain;

}

