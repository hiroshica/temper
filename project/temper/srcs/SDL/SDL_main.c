#include "../common.h"
#include "SDL_screen.h"

void msleep(float milisec)
{
  struct timespec req = {0}, ret = {0};
  time_t sec = (unsigned short)(milisec / 1000);

  milisec = milisec - (sec * 1000);
  req.tv_sec = sec;
  req.tv_nsec = (long)(milisec * 1000000L);

  while (nanosleep(&req, &ret) == -1)
    continue;
}

void get_ticks_us(u64 *ticks_return)
{
  *ticks_return = (SDL_GetTicks() * 1000);
}

void delay_us(u32 delay)
{

  /*or*/
  msleep(delay / 1000);
}

config_struct config =
    {
        // u32 pad[PAD_STOCK_MAX];
        {
           0, 1,
           2, 3, 4, 5,
           6, 7, 8,
           9,10,11,
          12,13,

          -1,-1,

          -1,-1,-1,-1,
          -1,-1,-1,-1,
          -1,-1,-1,-1,
          -1,-1,-1,-1,
        },
        // u32 rapid_active[PAD_STOCK_MAX];
        {
          0,0,0,0,0,0,0,0,
          0,0,0,0,0,0,0,0,
          0,0,0,0,0,0,0,0,
          0,0,0,0,0,0,0,0,
        },
        // u32 rapid_frame[PAD_STOCK_MAX];
        {
          1,1,1,1,1,1,1,1,
          1,1,1,1,1,1,1,1,
          1,1,1,1,1,1,1,1,
          1,1,1,1,1,1,1,1,
        },
        0,               // u32 show_fps;
        1,               // u32 enable_sound;
        0,               // u32 fast_forward;
        44100,           // u32 audio_output_frequency;
        1,               // u32 patch_idle_loops;
        SS_SNAPSHOT_OFF, // u32 snapshot_format;
        0,               // u32 force_usa;

        300,               // u32 clock_speed; hurr mr pc is faster
        0,                 // u32 gp2x_ram_timings;
        100,               // u32 gp2x_gamma_percent;
        0,                 // u32 six_button_pad;
        CD_SYSTEM_TYPE_V3, // cd_system_type_enum cd_system_type;
        1,                 // u32 bz2_savestates;
        0,                 // u32 per_game_bram;
        0,                 // u32 sound_double;
        SCALE_1x,          // u32 scale_factor;
        0,                 // u32 fast_cd_access;
        0,                 // u32 fast_cd_load;
        0,                 // u32 scale_width;
        0,                 // u32 unlimit_sprites
        0,                 // u32 compatibility_mode
};

void synchronize()
{
  static u64 last_ticks = 0;

  if (last_ticks != 0)
  {
    u64 current_ticks;
    s32 delay;

    // Point B, the beginning of the new frame.
    get_ticks_us(&current_ticks);

    delay = (15000 - (current_ticks - last_ticks));

    if ((delay > 0) && (config.fast_forward == 0))
      delay_us(delay);
  }

  get_ticks_us(&last_ticks);
  platform_update();
}

SDL_Joystick *joy = NULL;

void platform_initialize()
{
  SDL_Init(SDL_INIT);
  SDL_ShowCursor(0);
#if 0
  // ジョイスティックが存在するかチェックする
  if (SDL_NumJoysticks() > 0)
    {
      // ジョイスティックを開く
      joy = SDL_JoystickOpen(0);

      if (joy)
	{
	  printf("ジョイスティック 0 を開いた\n");
	  printf("名前: %s\n", SDL_JoystickName(0));
	  printf("軸の数: %d\n", SDL_JoystickNumAxes(joy));
	  printf("ボタンの数: %d\n", SDL_JoystickNumButtons(joy));
	  printf("ボールの数: %d\n", SDL_JoystickNumBalls(joy));
	}
      else
	{
	  printf("ジョイスティック 0 を開けなかった\n");
	}
    }
#endif
}

void platform_update()
{
  //SDL_JoystickUpdate();
}

void platform_quit()
{
#ifndef PANDORA_BUILD
  show_profile_stats();
#endif
#if 0
  // 開いたなら閉じる
  if (joy != NULL)
    {
      SDL_JoystickClose(joy);
    }
#endif
  exit_screen();
  SDL_Quit();
}

void set_gamma(u32 gamma)
{
  int error;
  float gam = gamma;
  gam = gam / 100;
  //error = SDL_SetGamma(gam, gam, gam);
}
