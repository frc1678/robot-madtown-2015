/*
 * claw_subsystem.h
 *
 *  Created on: Nov 9, 2015
 *      Author: Citrus CAD
 */

#ifndef SRC_CLAW_CLAW_SUBSYSTEM_H_
#define SRC_CLAW_CLAW_SUBSYSTEM_H_

#include "claw_controller.h"
#include <components/RobotParts.h>

class ClawSubsystem {
	ClawController _controller;
	RobotParts* parts;
	Voltage _intake_speed;
public:
	ClawSubsystem();
	ClawSubsystem(RobotParts* parts);
	virtual ~ClawSubsystem();
	void set_goal(Angle goal);
	void update();
	void open();
	void close();
	void run_intakes(Voltage speed);
	Angle angle();

	static Angle human_pickup_forward;
	static Angle ground_pickup;
	static Angle human_pickup_reverse;
};

#endif /* SRC_CLAW_CLAW_SUBSYSTEM_H_ */
