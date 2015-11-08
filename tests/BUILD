cc_test(
    name = "claw_test",
    srcs = ["claw_test.cpp"],
    copts = ["-Iexternal/gtest"],
    size = "small",
    deps = ["//third_party/googletest:googletest", "//claw:claw"],
)

cc_test(
    name = "drive_test",
    srcs = ["drive_test.cpp"],
    copts = ["-Iexternal/gtest"],
    size = "small",
    deps = ["//third_party/googletest:googletest", "//drivetrain:drive"],
)
