#include <fstream>
#include <tuple>
#include "gtest/gtest.h"
#include "drivetrain/drive_plant.h"
#include "drivetrain/drive_controller.h"
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

TEST_F(DriveTest, DistDriven){
  controller.set_distance_goal(10*ft);
  simulate_for(5*s);

  EXPECT_NEAR(0, plant.velocity_right().to(m/s), 0.05);
  EXPECT_NEAR(0, plant.velocity_left().to(m/s), 0.05);
  EXPECT_NEAR(10, plant.distance().to(ft), 0.1);
}

//TODO (Jasmine): Set this in a separate file so we can run tests for all
// subsystems
int main(int argc, char **argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
