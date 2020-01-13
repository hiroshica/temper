#############################################################################
# linux setup
#############################################################################
set (SOURCE_FILES ${SOURCE_FILES}
srcs/rg350/SDL_main.c
srcs/rg350/SDL_screen.c
srcs/rg350/SDL_audio.c
srcs/rg350/SDL_event.c
srcs/rg350/SDL_menu.c
srcs/rg350/crc32.c

srcs/rg350/tremor/bitwise.c
srcs/rg350/tremor/block.c
srcs/rg350/tremor/codebook.c
srcs/rg350/tremor/floor0.c
srcs/rg350/tremor/floor1.c
srcs/rg350/tremor/framing.c

srcs/rg350/tremor/info.c
srcs/rg350/tremor/mapping0.c
srcs/rg350/tremor/mdct.c
srcs/rg350/tremor/registry.c
srcs/rg350/tremor/res012.c
srcs/rg350/tremor/sharedbook.c

srcs/rg350/tremor/synthesis.c
srcs/rg350/tremor/vorbisfile.c
srcs/rg350/tremor/window.c
)

include_directories(${CMAKE_CURRENT_SOURCE_DIR}/srcs/${COMPILE_TYPE}/tremor)

