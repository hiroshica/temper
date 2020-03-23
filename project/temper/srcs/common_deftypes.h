#ifndef COMMON_DEFTYPES_H
#define COMMON_DEFTYPES_H

typedef unsigned char u8;
typedef signed char s8;
typedef unsigned short int u16;
typedef signed short int s16;

// For some reason, other libraries define these on PSP

#ifndef PSP_BUILD
typedef unsigned int u32;
typedef signed int s32;
#endif

typedef unsigned long long int u64;
typedef signed long long int s64;

#ifndef __cplusplus
  typedef int bool;
  #define true (1)
  #define false (0)
  #define TRUE (1)
  #define FALSE (0)
#endif

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>
#include <string.h>
#include <stdarg.h>

#include <sys/time.h>
#include <sys/stat.h>
#include <ctype.h>

#include <dirent.h>

#include <math.h>

#include "platform_defines.h"

#ifdef CRC_CHECK
#include "crc32.h"
#endif

#ifdef SDL_INIT
  #include <SDL.h>
  #include <SDL_joystick.h>
#endif

#ifdef BZ_SUPPORT
  #include <bzlib.h>
#endif

#endif

