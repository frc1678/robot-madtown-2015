#include "drive_controller.h"
#include <iostream>

DriveController::DriveController() :
		_profile(0 * m) {
	last = 10 * km;
}

DriveController::~DriveController() {
}

std::tuple<Voltage, Voltage> DriveController::update(Length left_encoder,
		Length right_encoder) {
	if (!started) {
		_offset_left = -left_encoder;
		_offset_right = -right_encoder;
		started = true;
	}
	last = (left_encoder + _offset_left + right_encoder + _offset_right) / 2;
//  Time dT = 0.005*s;
//  auto d_error = (error-last_error)/dT;
//  last_error = error;
//  return (kP*error + kD*d_error);
//	last_error =  goal_distance - (left_encoder + right_encoder)/2;
//	return _profile.calculate(t.Get() * s);
	Voltage correction = ((left_encoder + _offset_left)
			- (right_encoder + _offset_right)) * 8 * V / m;
	return std::make_tuple(10 * V - correction, 10 * V + correction);
}

void DriveController::set_distance_goal(Length distance) {
	goal_distance = distance;
	started = false;
//  t.Reset();
//  t.Start();
//  _profile = MotionProfile(distance);
}

bool DriveController::done() {
	SmartDashboard::PutNumber("Drive dist", last.to(ft));
	return goal_distance - last < 0*ft;
}
