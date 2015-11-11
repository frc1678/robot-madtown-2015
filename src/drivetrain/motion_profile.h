/*
 * motion_profile.h
 *
 *  Created on: Nov 10, 2015
 *      Author: Citrus CAD
 */

#ifndef SRC_DRIVETRAIN_MOTION_PROFILE_H_
#define SRC_DRIVETRAIN_MOTION_PROFILE_H_

#include "unitscpp/unitscpp.h"

class MotionProfile {
	Length _distance;
	Time _accel_time, _total_time, _deccel_time;
	Voltage _max_voltage;

public:
	MotionProfile(Length distance);
	Voltage calculate(Time t);
	virtual ~MotionProfile();
};

#endif /* SRC_DRIVETRAIN_MOTION_PROFILE_H_ */
