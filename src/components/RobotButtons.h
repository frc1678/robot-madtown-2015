/*
 * RobotButtons.h
 *
 *  Created on: Mar 24, 2015
 *      Author: Citrus Circuits
 */

#ifndef FINAL_ROBOT_2015_SRC_ROBOTBUTTONS_H_
#define FINAL_ROBOT_2015_SRC_ROBOTBUTTONS_H_

#include "CitrusButton.h"


class RobotButtons {
public:
	RobotButtons(Joystick *l, Joystick *r, Joystick *m);
	~RobotButtons();

	CitrusButton *clawToggle;

	void UpdateButtons();
};

#endif /* FINAL_ROBOT_2015_SRC_ROBOTBUTTONS_H_ */
