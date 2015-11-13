#include <fstream>
#include <tuple>
#include "gtest/gtest.h"
#include "drivetrain/drive_plant.h"
#include "drivetrain/drive_controller.h"
#include "drivetrain/trapezoidal_motion_profile.h"
#include "unitscpp/unitscpp.h"

class DriveTest : public ::testing::Test {
protected:
  void SetUp() {

  }

  void TearDown() {

  }

  // Simulate the closed-loop plant for a specific amount of time
  // TODO(Kyle): Add an option for logging
  void simulate_for(Time t) {
    for (int i = 0; i < t.to(.005*s); i++) {
      Voltage v = controller.update(plant.distance_left(), plant.distance_right());
      plant.update(.005*s, v, v);
    }
  }

  // TODO (Kelly): Figure out naming conventions. Are we using google style guide?
  // (_ after member variables)
  DrivePlant plant;
  DriveController controller;
};

TEST_F(DriveTest, Sanity) {
  // Sanity check
  simulate_for(2.5*s);
  simulate_for(10*s);

  EXPECT_NEAR(0,plant.velocity_right().to(m/s), 0.05);
  EXPECT_NEAR(0,plant.velocity_left().to(m/s), 0.05);
}

TEST_F(DriveTest, DistDriven) {
  TrapezoidalMotionProfile<Length> motion_profile(10*ft, maxHighRobotSpeed, maxHighRobotSpeed / (2*s));
  Time t;
  Velocity last_speed = motion_profile.calculate_speed(0*s);
  for (t = 0; !motion_profile.finished(t); t+=.05*s) {
    Velocity cur_speed = motion_profile.calculate_speed(t);
    EXPECT_LE(((cur_speed - last_speed) / (0.05*s)).to(ft/s/s), (maxHighRobotSpeed / (2*s)).to(ft/s/s) + .0001) << "Robot accelerating too quickly";
    EXPECT_GE(((cur_speed - last_speed) / (0.05*s)).to(ft/s/s), (-maxHighRobotSpeed / (2*s)).to(ft/s/s) - .0001) << "Robot deccelerating too quickly";
    last_speed = cur_speed;
  }
  EXPECT_NEAR(motion_profile.calculate_distance(t).to(ft), 10, 0.00001);
}

TEST_F(DriveTest, TrapezoidalMotion) {

}

//TODO (Jasmine): Set this in a separate file so we can run tests for all
// subsystems
int main(int argc, char **argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
