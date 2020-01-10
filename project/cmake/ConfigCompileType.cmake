##########################################################################################
# configure compile type
##########################################################################################
#MESSAGE("compile type = ${COMPILE}")

# runtime output
set(PROJECT_WORK_DIR ${PROJECT_BINARY_DIR})
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${PROJECT_SOURCE_DIR}/exe")

if(COMPILE STREQUAL "linux")
  # linux
  INCLUDE(LinuxSetup)
elseif(COMPILE STREQUAL "mingw")
  # mingw32
  INCLUDE(MingWSetup)
elseif(COMPILE STREQUAL "win32")
  # win32(VS2008)
  INCLUDE(Win32Setup)
elseif(COMPILE STREQUAL "rg350")
  INCLUDE(mips32-linux-gcc)
endif()

################ end of file ################
