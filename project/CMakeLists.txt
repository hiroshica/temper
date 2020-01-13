##########################################################################################
#    this file is part of the CMake build system for ProjectSS
##########################################################################################
cmake_minimum_required(VERSION 3.1)
set(CMAKE_ALLOW_LOOSE_LOOP_CONSTRUCTS TRUE)
cmake_policy(SET CMP0003 NEW)

################################################
MESSAGE("compile type = ${COMPILE_TYPE}")

project(temper)

################################################
# setup library cmake includes
################################################
if(COMPILE_TYPE STREQUAL "linux")
  # linux
elseif(COMPILE_TYPE STREQUAL "rg350")
  # rg350
  set(PKG_CONFIG_EXECUTABLE "/opt/rg350-toolchain/usr/bin/pkg-config")
elseif(COMPILE_TYPE STREQUAL "mingw")
  # mingw32
elseif(COMPILE_TYPE STREQUAL "win32")
  # win32(VS2008)
endif()

  find_package(PkgConfig REQUIRED)
pkg_check_modules(SDL sdl REQUIRED)

MESSAGE("SDL_INC = ${SDL_INCLUDE_DIRS}")
MESSAGE("SDL_LIBS = ${SDL_LDFLAGS}")

set(CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/CMake")

################################################
# platform/build config
################################################
string(TOLOWER "${COMPILE_TYPE}" COMPILE)
string(TOLOWER "${CMAKE_BUILD_TYPE}" PROJECT_BUILD_TYPE)

################################################
# build config.
################################################
if (PROJECT_BUILD_TYPE STREQUAL "finalmaster")
  add_definitions(-D__FINALMASTER__)

elseif(PROJECT_BUILD_TYPE STREQUAL "debugmaster")
  add_definitions(-D__DEBUGMASTER__)
  set(PROJECT_LIB_SUFFIX "R")
else()
  add_definitions(-D__DEBUG__ -D_DEBUG)
  add_definitions(-g)
  set(PROJECT_LIB_SUFFIX "D")
endif()

set(PROJECT_EXE_SUFFIX "${MACHINE_SUFFIX}${PROJECT_LIB_SUFFIX}")

if(COMPILE_TYPE STREQUAL "linux")
  # linux
  set(PLATFORM_CFLAGS "-DLINUX_X86_BUILD")
  set(PLATFORM_LIBS "-lz -lm -pthread")
elseif(COMPILE_TYPE STREQUAL "rg350")
  # rg350
  set(PLATFORM_CFLAGS "-DRG350_BUILD -Ofast -mips32r2 -mmxu -fdata-sections -ffunction-sections")
  set(PLATFORM_LIBS " -lz -lm -lbz2 -pthread -Wl,--as-needed -Wl,--gc-sections -flto -s")
elseif(COMPILE_TYPE STREQUAL "mingw")
  # mingw32
elseif(COMPILE_TYPE STREQUAL "win32")
  # win32(VS2008)
endif()


################################################
# setup project
################################################

INCLUDE(ConfigCompileType)

################################################
#    setup targets
################################################
#
add_subdirectory(temper)

################ end of file ################
