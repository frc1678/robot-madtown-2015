/*
 * RobotButtons.cpp
 *
 *  Created on: Mar 24, 2015
 *      Author: Citrus Circuits
 */

#include "components/RobotButtons.h"

RobotButtons::RobotButtons(Joystick *l, Joystick *r, Joystick *m) {
	pickup = new CitrusButton(m, 6);
	hp_front = new CitrusButton(m, 5);
	hp_reverse = new CitrusButton(m, 1);
	kiss_pass = new CitrusButton(m, 2);

	open_claw = new CitrusButton(m, 3);

	shift_high = new CitrusButton(r, 3);
	shift_low = new CitrusButton(l, 3);
}

RobotButtons::~RobotButtons() {
	delete pickup;
	delete hp_front;
	delete hp_reverse;
	delete kiss_pass;

	delete open_claw;

	delete shift_high;
	delete shift_low;
}


void RobotButtons::UpdateButtons() {
	pickup->Update();
	hp_front->Update();
	hp_reverse->Update();
	kiss_pass->Update();

	open_claw->Update();

	shift_high->Update();
	shift_low->Update();
}
