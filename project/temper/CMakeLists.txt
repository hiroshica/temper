##########################################################################################
#    PC-ENGINE
##########################################################################################
set(EXECNAME temper)

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
srcs/netplay.c
srcs/arcade_card.c
srcs/bin_cue.c
)

include_directories(${CMAKE_CURRENT_SOURCE_DIR}/srcs)
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/srcs/${COMPILE_TYPE})
INCLUDE(srcs/${COMPILE_TYPE}/CMakeLists.txt)

set (OUT_EXEC_FILE ${EXECNAME}${PROJECT_EXE_SUFFIX})


LINK_DIRECTORIES("${CMAKE_LIBRARY_OUTPUT_DIRECTORY}")
set(BUILD_CFLAGS "-I${SDL_INCLUDE_DIRS} ${PLATFORM_CFLAGS}")
set(BUILD_LDFLAGS "${SDL_LIBRARIES} ${PLATFORM_LIBS}")
set_property(SOURCE ${SOURCE_FILES} PROPERTY COMPILE_FLAGS "${BUILD_CFLAGS}")
add_executable(${OUT_EXEC_FILE} ${SOURCE_FILES})
target_link_libraries(${OUT_EXEC_FILE} ${BUILD_LDFLAGS})

################ end of file ################
