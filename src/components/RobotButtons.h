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

	CitrusButton* pickup;
	CitrusButton* hp_front;
	CitrusButton* hp_reverse;
	CitrusButton* kiss_pass;

	CitrusButton* open_claw;

	CitrusButton* shift_high;
	CitrusButton* shift_low;

	void UpdateButtons();
};

#endif /* FINAL_ROBOT_2015_SRC_ROBOTBUTTONS_H_ */
