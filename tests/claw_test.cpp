#include <fstream>
#include "gtest/gtest.h"
#include "claw/claw_plant.h"
#include "claw/claw_controller.h"
#include "unitscpp/unitscpp.h"

class ClawTest : public ::testing::Test {
protected:
  void SetUp()
  {

  }

  void TearDown() {

  }

  // Simulate the closed-loop plant for a specific amount of time
  // TODO(Kyle): Add an option for logging
  void simulate_for(Time t) {
    for (int i = 0; i < t.to(.005*s); i++) {
      Voltage voltage = controller.update(plant.encoder(), plant.min_hall_triggered(), plant.max_hall_triggered(), true);
      plant.update(.005*s, voltage);
      
      EXPECT_LE(voltage, 12.0*V);
      EXPECT_GE(voltage, -12.0*V);
    }
  }

  // TODO (Kelly): Figure out naming conventions. Are we using google style guide?
  // (_ after member variables)
  ClawPlant plant;
  ClawController controller;
};

// Sanity test on physics model.
// Run for half a second, make sure it stops.
TEST_F(ClawTest, ModelStops) {
    for (int i = 0; i < 100; i++) {
        plant.update(.005*s, 3*V);
    }
    for (int i = 0; i < 1000; i++) {
        plant.update(.005*s, 0*V);
    }
    EXPECT_NEAR(plant.angular_velocity().to(rad/s), 0, 0.01);
}

// Ensure that the controller calibrates.
// TODO (Kyle): add set_state to plant (and controller?)
// TODO (Kyle): add to test fixture
TEST_F(ClawTest, Calibrates) {
  plant.set_angle(.1*rad);

  // Runs for one second while hall effect is triggered
  // TODO (Kyle): Make sure the controller doesn't run into the hard stop  
  simulate_for(10*s);

  // Make sure it has calibrated
  EXPECT_TRUE(controller.running());
  EXPECT_NEAR(plant.angle().to(rad), 0, 0.01);
}

// Tests that the controller moves to a given position
// TODO (Kyle): and stops after
TEST_F(ClawTest, MovesToGoal) {
  plant.set_angle(0.1*rad);
  
  controller.set_goal(1*rad);
  simulate_for(5*s);

  EXPECT_NEAR(1, plant.angle().to(rad), 0.01);
}

// Moves from minimum to maximum point.
// TODO (Kyle): add get_min, get_max
TEST_F(ClawTest, FullRange) {
  plant.set_angle(.4*rad);
  plant.set_velocity(.1*rad/s);
  
  // Move to max position
  controller.set_goal(2.1*rad);
  simulate_for(10*s);

  EXPECT_TRUE(plant.max_hall_triggered());
  EXPECT_NEAR(0, plant.angular_velocity().to(rad/s), 0.01);
  EXPECT_NEAR(2.1, plant.angle().to(rad), 0.01);

  // Move to min position
  controller.set_goal(0*rad);
  simulate_for(10*s);

  EXPECT_TRUE(plant.min_hall_triggered());
  EXPECT_NEAR(0, plant.angular_velocity().to(rad/s), 0.01);
  EXPECT_NEAR(0, plant.angle().to(rad), 0.01);
}

//TODO (Jasmine): Set this in a separate file so we can run tests for all
// subsystems
int main(int argc, char **argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
