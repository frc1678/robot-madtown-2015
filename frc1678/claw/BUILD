cc_library(
  name = 'claw',
  hdrs = ['claw_plant.h', 'claw_controller.h'],
  srcs = ['claw_plant.cpp', 'claw_controller.cpp'],
  deps = [
    '@eigen//:main',
    '//unitscpp'
  ],
  visibility = ["//visibility:public"]
)

cc_test(
  name = 'claw_test',
  size = 'small',
  srcs = [
    'claw_test.cpp'
  ],
  deps = [
    ':claw',
    '@gtest//:main',
    '//unitscpp'
  ]
)
