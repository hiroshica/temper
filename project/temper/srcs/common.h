#ifndef COMMON_H
#define COMMON_H

#include "common_deftypes.h"

#ifdef GP2X_BUILD
  #include "gp2x/gp2x_common.h"
#endif

#ifdef RG350_BUILD
#define TEMPER_VERSION "1.30.0 RG350"
#else
#define TEMPER_VERSION "1.24.2 GCW"
#endif
#define CD_SWAP_OPTION
#define FASTFORWARD_FRAMESKIP
#define FASTFORWARD_FRAMESKIP_RATE 4

#ifdef OGG_SUPPORT

#ifdef OGG_TREMOR
#include <tremor/ivorbisfile.h>
#else
#include <vorbis/vorbisfile.h>
#endif

#endif


#include"common_defines.h"
#include "cpu.h"
#include "debug.h"
#include "memory.h"
#include "video.h"
#include "irq.h"
#include "io.h"
#include "timer.h"
#include "psg.h"
#include "main.h"
#include "disasm.h"
#include "event.h"
#include "menu.h"
#include "cd.h"
#include "adpcm.h"
#include "arcade_card.h"
#include "netplay.h"
#include "screen.h"
#include "audio.h"

#include "bin_cue.h"


#ifdef LINUX_PLATFORM

#include <fcntl.h>
#include <strings.h>
#include <sched.h>
#include <unistd.h>

#include <sys/socket.h>
#include <netinet/in.h>
#include <netinet/tcp.h>
#include <poll.h>
#include <errno.h>

#ifndef _GNU_SOURCE
#define _GNU_SOURCE
#endif

#endif

#include <getopt.h>

#ifdef WIN32_BUILD

#include <winsock.h>

#endif

#endif

