##########################################################################################
#    PC-ENGINE
##########################################################################################
set(EXECNAME RG-temp)

set (SOURCE_FILES
srcs/main.c
srcs/cpu.c
srcs/memory.c
srcs/irq.c
srcs/io.c
srcs/video.c
srcs/timer.c
srcs/psg.c
srcs/disasm.c

srcs/screen.c
srcs/event.c
srcs/audio.c
srcs/menu.c
srcs/debug.c
srcs/cd.c
srcs/adpcm.c
srcs/arcade_card.c
srcs/bin_cue.c
)

#include_directories(${CMAKE_CURRENT_SOURCE_DIR}/srcs)
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/srcs/${COMPILE_TYPE})
set (OUT_EXEC_FILE ${EXECNAME}${PROJECT_EXE_SUFFIX})

INCLUDE(srcs/${COMPILE_TYPE}/CMakeLists.txt)

LINK_DIRECTORIES("${CMAKE_LIBRARY_OUTPUT_DIRECTORY}")
#set(BUILD_CFLAGS " ${PLATFORM_CFLAGS} -I${SDL_INC}")


set_property(SOURCE ${SOURCE_FILES} PROPERTY COMPILE_FLAGS "${BUILD_CFLAGS}")
add_executable(${OUT_EXEC_FILE} ${SOURCE_FILES})
target_link_libraries(${OUT_EXEC_FILE} ${BUILD_LDFLAGS})

if(COMPILE_TYPE STREQUAL "linux")
  # linux
elseif(COMPILE_TYPE STREQUAL "mingw")
  # mingw32
elseif(COMPILE_TYPE STREQUAL "rg350")
#
  set (NOWWORKDIR "${CMAKE_CURRENT_SOURCE_DIR}/srcs/${COMPILE_TYPE}")
  set (NOWWORKOUTFILE "${OUT_EXEC_FILE}")
  set (NOWWORKOUTFILEBASE "temper-RG350")
  set (NOWWORKLASTOUTFILE "${NOWWORKOUTFILEBASE}.opk")
#
  add_custom_target(${NOWWORKLASTOUTFILE} ALL
  DEPENDS ${NOWWORKOUTFILE}
  WORKING_DIRECTORY ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}
  COMMENT "Build OPK"
  COMMAND rm -rf .opk_data
  COMMAND cp -r ${NOWWORKDIR}/data .opk_data
  COMMAND echo "[Desktop Entry]" > .opk_data/default.gcw0.desktop
  COMMAND echo Type=Application >> .opk_data/default.gcw0.desktop
  COMMAND echo Name=${NOWWORKOUTFILEBASE} >> .opk_data/default.gcw0.desktop
  COMMAND echo Comment=PC-Engine emulator >> .opk_data/default.gcw0.desktop
  COMMAND echo Exec=${NOWWORKOUTFILEBASE} %f >> .opk_data/default.gcw0.desktop
  COMMAND echo Icon=icon >> .opk_data/default.gcw0.desktop
  COMMAND echo Terminal=false >> .opk_data/default.gcw0.desktop
  COMMAND echo "Categories=emulators;" >> .opk_data/default.gcw0.desktop
  COMMAND echo MimeType=.pce >> .opk_data/default.gcw0.desktop
  COMMAND cp ${NOWWORKOUTFILE} .opk_data/${NOWWORKOUTFILEBASE}
  COMMAND ${CMAKE_STRIP} .opk_data/${NOWWORKOUTFILEBASE}
  COMMAND ${TOOLCHAIN_PREFIX}/bin/mksquashfs .opk_data ${NOWWORKLASTOUTFILE} -all-root -noappend -no-exports -no-xattrs
  )
endif()

################ end of file ################
