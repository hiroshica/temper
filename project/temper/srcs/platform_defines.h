#ifndef PLATFORM_DEFINES_H
#define PLATFORM_DEFINES_H

// Everything here must be C preprocessor material only. That way even
// assembler files can load this.

//#define DEBUGGER_ON

#ifdef WIN32_BUILD

#define SDL_INIT        (SDL_INIT_VIDEO | SDL_INIT_AUDIO | SDL_INIT_JOYSTICK)

#define COLOR_RGB_565

#define X86_ARCH
#define OGG_SUPPORT
#define BZ_SUPPORT
#define DIR_SEPARATOR_CHAR '\\'
#define DIR_SEPARATOR_CHAR_STR "\\"
#define make_directory(name) mkdir(name)

#endif

#ifdef LINUX_X86_BUILD

//#define SDL_INIT        (SDL_INIT_VIDEO | SDL_INIT_JOYSTICK)
#define SDL_INIT        (SDL_INIT_VIDEO | SDL_INIT_AUDIO | SDL_INIT_JOYSTICK)

#define COLOR_RGB_565

#define LINUX_PLATFORM
#define LETSGO_HOME
#define CRC_CHECK
/*#define OGG_SUPPORT
#define BZ_SUPPORT*/
#define KEYBOARD_SUPPORT
#define DIR_SEPARATOR_CHAR '/'
#define DIR_SEPARATOR_CHAR_STR "/"
#define make_directory(name) mkdir(name, 0755)
#define MAX_PATH 1024

#endif

#ifdef RG350_BUILD

#define SDL_INIT        (SDL_INIT_VIDEO | SDL_INIT_JOYSTICK)

#define COLOR_RGB_565
#define CRC_CHECK

#define LINUX_PLATFORM
#define LETSGO_HOME
#define KEYBOARD_SUPPORT
#define CONFIG_OPTIONS_GAMMA

#define OGG_SUPPORT
#define OGG_TREMOR
#define BZ_SUPPORT

#define DIR_SEPARATOR_CHAR '/'
#define DIR_SEPARATOR_CHAR_STR "/"
#define MAX_PATH 512
#define make_directory(name) mkdir(name, 0755)

#endif

#define COPY_MAXPATH   (MAX_PATH*2)
#define COPY_MAXPATH2   (MAX_PATH*3)

#endif

