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
#include_directories(${CMAKE_CURRENT_SOURCE_DIR}/srcs)
set_property(SOURCE ${SOURCE_FILES} PROPERTY COMPILE_FLAGS "${CXX_DEF_FLAGS}")
add_executable(${OUT_EXEC_FILE} ${SOURCE_FILES})
target_link_libraries(${OUT_EXEC_FILE} ${SDL_LIBRARIES} ${PLATFORM_LIBS})

################ end of file ################
