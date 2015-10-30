#include <iostream>
#include "gtest/gtest.h"
#include "claw/claw_plant.h"
#include "claw/claw_controller.h"

TEST(ClawTest, DoesCompile) {
    ClawController control;
    ClawPlant plant;
}

TEST(ClawTest, Stops) {
    ClawPlant plant;
    for (int i = 0; i < 100; i++) {
        plant.Update(.005, 3);
    }
    for (int i = 0; i < 1000; i++) {
        plant.Update(.005, 0);
    }
    EXPECT_NEAR(plant.GetAngularVelocity(), 0, 0.01);
}

TEST(ClawTest, ReachesGoal) {
    
}