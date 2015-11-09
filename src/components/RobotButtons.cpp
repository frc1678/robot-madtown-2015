/*
 * RobotButtons.cpp
 *
 *  Created on: Mar 24, 2015
 *      Author: Citrus Circuits
 */

#include "components/RobotButtons.h"

RobotButtons::RobotButtons(Joystick *l, Joystick *r, Joystick *m) {

	clawToggle = new CitrusButton(m, 1);

}

RobotButtons::~RobotButtons() {

	delete clawToggle;

}


void RobotButtons::UpdateButtons() {

	clawToggle->Update();

}
