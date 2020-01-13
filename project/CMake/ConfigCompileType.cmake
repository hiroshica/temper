##########################################################################################
# configure compile type
##########################################################################################
# runtime output
set(PROJECT_WORK_DIR ${PROJECT_BINARY_DIR})
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${PROJECT_SOURCE_DIR}/exe")

if(COMPILE_TYPE STREQUAL "linux")
  # linux
  INCLUDE(LinuxSetup)
elseif(COMPILE_TYPE STREQUAL "mingw")
  # mingw32
  INCLUDE(MingWSetup)
elseif(COMPILE_TYPE STREQUAL "win32")
  # win32(VS2008)
  INCLUDE(Win32Setup)
elseif(COMPILE_TYPE STREQUAL "rg350")
  INCLUDE(mips32-linux-gcc)
endif()

################ end of file ################
