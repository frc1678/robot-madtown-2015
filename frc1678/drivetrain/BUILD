cc_library(
  name = 'drivetrain',
  hdrs = ['drivetrain_plant.h', 'drivetrain_controller.h'],
  srcs = ['drivetrain_plant.cpp', 'drivetrain_controller.cpp'],
  deps = [
    '@eigen//:main',
    '//unitscpp'
  ],
  visibility = ["//visibility:public"]
)

cc_test(
  name = 'drivetrain_test',
  size = 'small',
  srcs = [
    'drivetrain_test.cpp'
  ],
  deps = [
    ':drivetrain',
    '@gtest//:main',
    '//unitscpp'
  ]
)
