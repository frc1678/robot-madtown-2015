/*
 * motion_profile.cpp
 *
 *  Created on: Nov 10, 2015
 *      Author: Citrus CAD
 */

#include <drivetrain/motion_profile.h>

#include "WPILib.h"

MotionProfile::MotionProfile(Length distance) {
	_accel_time = 2*s;
	_deccel_time = _accel_time;
	_max_voltage = 12*V;
	_total_time = distance / maxHighRobotSpeed - _accel_time;
//	SmartDashboard::PutNumber("total", _total_time.to(s));
}

Voltage MotionProfile::calculate(Time t) {
	if (t < _accel_time) {
		return _max_voltage * t / _accel_time;
	}
	else if (t < _total_time - _deccel_time) {
		return _max_voltage;
	}
	else if (t < _total_time) {
		return _max_voltage * (_total_time - t) / _deccel_time;
	}
	else {
		return 0*V;
	}
}

MotionProfile::~MotionProfile() {
	// TODO Auto-generated destructor stub
}

