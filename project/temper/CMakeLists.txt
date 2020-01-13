##########################################################################################
#    PC-ENGINE
##########################################################################################
set(EXECNAME temper)

set (SOURCE_FILES
srcs/adpcm.c
srcs/audio.c
srcs/cd.c
srcs/debug.c
srcs/event.c
srcs/irq.c
srcs/memory.c
srcs/netplay.c
srcs/screen.c
srcs/video.c
srcs/arcade_card.c
srcs/bin_cue.c
srcs/cpu.c
srcs/disasm.c  srcs/io.c
srcs/main.c
srcs/menu.c
srcs/psg.c
srcs/timer.c
srcs/crc32.c
srcs/SDL/SDL_main.c
srcs/SDL/SDL_screen.c
srcs/SDL/SDL_audio.c
srcs/SDL/SDL_event.c
srcs/SDL/SDL_menu.c
)

set (OUT_EXEC_FILE ${EXECNAME}${PROJECT_EXE_SUFFIX})

LINK_DIRECTORIES("${CMAKE_LIBRARY_OUTPUT_DIRECTORY}")
set(BUILD_CFLAGS "-I${SDL_INCLUDE_DIRS} ${PLATFORM_CFLAGS}")
set(BUILD_LDFLAGS "${SDL_LIBRARIES} ${PLATFORM_LIBS}")
set_property(SOURCE ${SOURCE_FILES} PROPERTY COMPILE_FLAGS "${BUILD_CFLAGS}")
add_executable(${OUT_EXEC_FILE} ${SOURCE_FILES})
target_link_libraries(${OUT_EXEC_FILE} ${BUILD_LDFLAGS})

################ end of file ################
