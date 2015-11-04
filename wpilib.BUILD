_header_dirs = [
  'allwpilib/wpilibc/wpilibC++/include',
  'allwpilib/wpilibc/wpilibC++Devices/include',
  'allwpilib/hal/include',
  'allwpilib/hal/lib/Athena/FRC_FPGA_ChipObject',
  'allwpilib/hal/lib/Athena'
]

# TODO(Kyle): Build libwpi from source instead of using the pre-built binaries
cc_library(
  name = 'main',
  visibility = ['//visibility:public'],
  srcs = glob([
    "lib/libwpi.so"
  ]),
  copts = [
    '-Wno-error',
  ],
  hdrs = glob(['include/**/*.h']),
  includes = _header_dirs,
  linkopts = [
    '-Laos/externals/allwpilib/ni-libraries',
    '-lpthread',
    '-lFRC_NetworkCommunication',
    '-lRoboRIO_FRC_ChipObject',
    '-lNiFpgaLv',
    '-lNiFpga',
    '-lNiRioSrv',
    '-lspi',
    '-li2c',
  ],
)
