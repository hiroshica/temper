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

set(PROJECT_EXE_SUFFIX "${MACHINE_SUFFIX}-${COMPILE_TYPE}${PROJECT_LIB_SUFFIX}")

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

if(COMPILE_TYPE STREQUAL "rg350")
set (NOWWORKDIR "${CMAKE_CURRENT_SOURCE_DIR}/srcs/${COMPILE_TYPE}")
set (NOWWORKOUTFILE "${EXECUTABLE_OUTPUT_PATH}${OUT_EXEC_FILE}")
set (NOWWORKOUTFILEBASE "temper-RG350")
set (NOWWORKLASTOUTFILE "${NOWWORKOUTFILEBASE}.opk")

add_custom_command(OUTPUT ${NOWWORKLASTOUTFILE}
DEPENDS ${NOWWORKOUTFILE}
WORKING_DIRECTORY ${EXECUTABLE_OUTPUT_PATH}
COMMENT "Build OPK"
POST_BUILD
COMMAND "rm -rf .opk_data"
COMMAND "cp -r ${NOWWORKDIR}/data .opk_data"
COMMAND "cp ${NOWWORKOUTFILE} .opk_data/${NOWWORKOUTFILEBASE}"
COMMAND "${CMAKE_STRIP} .opk_data/${NOWWORKOUTFILEBASE}"
COMMAND "${TOOLCHAIN_PREFIX}/bin/mksquashfs .opk_data ${NOWWORKLASTOUTFILE} -all-root -noappend -no-exports -no-xattrs")

#add_dependencies(${NOWWORKLASTOUTFILE})
endif()


################ end of file ################
