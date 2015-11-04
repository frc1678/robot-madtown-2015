#include <fstream>
#include "gtest/gtest.h"
#include "claw_plant.h"
#include "claw_controller.h"
#include "unitscpp/unitscpp.h"

TEST(ClawTest, ModelStops) {
    ClawPlant plant;
    for (int i = 0; i < 100; i++) {
        plant.update(.005*s, 3*V);
    }
    for (int i = 0; i < 1000; i++) {
        plant.update(.005*s, 0*V);
    }
    EXPECT_NEAR(plant.angular_velocity().to(rad/s), 0, 0.01);
}

TEST(ClawTest, Calibrates) {
  ClawPlant plant(.1*rad, 0*rad/s);
  ClawController controller;

  for (int i = 0; i < 1000; i++) {
    controller.set_goal(0);
    Voltage voltage = controller.update(plant.encoder(), plant.min_hall_triggered(), plant.max_hall_triggered(), true);
    plant.update(.005*s, voltage);

    EXPECT_LE(voltage, 12.0*V);
    EXPECT_GT(voltage, -12.0*V);
  }
  EXPECT_TRUE(controller.running());
  EXPECT_NEAR(plant.angle().to(rad), 0, 0.01);
}

TEST(ClawTest, MovesToPosition) {
  ClawPlant plant(.1*rad, 0*rad/s);
  ClawController controller;

  std::ofstream log("/tmp/claw_moves_to_position.csv");

  for (int i = 0; i < 500; i++) {
    controller.set_goal(1);
    Voltage voltage = controller.update(plant.encoder(), plant.min_hall_triggered(), plant.max_hall_triggered(), true);
    plant.update(0.005*s, voltage);
    log << plant.angle() << "\t" << voltage.to(8*V) << "\n";

    EXPECT_LE(voltage, 12.0*V);
    EXPECT_GT(voltage, -12.0*V);
  }

  log.close();

  EXPECT_NEAR(1, plant.angle().to(rad), 0.01);
}

TEST(ClawTest, FullRange) {
  ClawPlant plant(.4*rad, .1*rad/s);
  ClawController controller;

  std::ofstream log("/tmp/claw_full_range.csv");

  for (int i = 0; i < 500; i++) {
    controller.set_goal(2.1*rad);
    Voltage voltage = controller.update(plant.encoder(), plant.min_hall_triggered(), plant.max_hall_triggered(), true);
    plant.update(0.005*s, voltage);
    log << plant.angle() << "\t" << voltage.to(8*V) << "\n";

    EXPECT_LE(voltage, 12.0*V);
    EXPECT_GT(voltage, -12.0*V);
  }

  log.close();

  EXPECT_TRUE(plant.max_hall_triggered());
  EXPECT_NEAR(0, plant.angular_velocity().to(rad/s), 0.01);
  EXPECT_NEAR(2.1, plant.angle().to(rad), 0.01);
}
