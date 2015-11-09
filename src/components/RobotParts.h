/*
 * RobotParts.h
 *
 *  Created on: Mar 23, 2015
 *      Author: Citrus Circuits
 */

#ifndef ROBOTPARTS_H_
#define ROBOTPARTS_H_

#include "WPILib.h"

class RobotParts {
public:
	// Compressor
	Compressor *compressor;

	VictorSP* moveClawA, *moveClawB;
	Solenoid* openClaw;
	VictorSP* tuskA, *tuskB;
	VictorSP* clawRollers;

	// Encoders
	Encoder *leftEncoder;
	Encoder *rightEncoder;
	Encoder *clawEncoder;

	// Drive train and its motors

	VictorSP *leftDT;
	VictorSP *rightDT;

	RobotDrive *drivetrain;


	RobotParts();
	~RobotParts();


};

#endif /* SRC_TELEOP_ROBOTPARTS_H_ */
