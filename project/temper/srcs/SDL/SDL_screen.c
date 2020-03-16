#include "../common.h"
#include "SDL_screen.h"

SDL_Surface *screen = NULL;
SDL_Surface *real_screen = NULL;
u32 last_scale_factor;
u8 *real_screen_pixels;

void update_screen()
{
  if (last_scale_factor != config.scale_factor)
  {
    u32 width = 320;
    u32 height = 240;
#if WIN32_BUILD|LINUX_X86_BUILD
    if (SCALE_FULLSCREEN != config.scale_factor)
    {
      //width *= config.scale_factor;
      //height *= config.scale_factor;
    }
#endif
    set_screen_resolution(width, height);
  }
  {
    SDL_Flip(screen);
  }
}

void set_screen_resolution(u32 width, u32 height)
{
  {
    u16 *old_pixels = NULL;

    if (screen != NULL)
    {
      old_pixels = malloc(320 * 240 * 2);
      copy_screen(old_pixels);
      SDL_FreeSurface(screen);
    }

    switch (config.scale_factor)
    {
    case SCALE_FULLSCREEN:
    #ifndef WIN32_BUILD
      screen = SDL_SetVideoMode(width, height, 16, SDL_FULLSCREEN
#ifdef SDL_TRIPLEBUF
                                                       | SDL_HWSURFACE | SDL_TRIPLEBUF
#endif
      );
      real_screen_pixels = screen->pixels;

      if (old_pixels != NULL)
        blit_screen(old_pixels);

      break;
      #endif

    default:
      screen = SDL_SetVideoMode(width, height, 16,
#ifdef SDL_TRIPLEBUF
                                SDL_HWSURFACE | SDL_TRIPLEBUF
#else
                                0
#endif
      );

      {
        if (old_pixels != NULL)
        {
          blit_screen(old_pixels);
        }
      }
      break;
    }

    if (old_pixels != NULL)
      free(old_pixels);

    last_scale_factor = config.scale_factor;
  }

  SDL_WM_SetCaption("Temper PC-Engine Emulator", "Temper");
}

void *get_screen_ptr()
{
  return screen->pixels;
}

u32 get_screen_pitch()
{
  if (config.use_opengl)
    return 320;

  return (screen->pitch / 2);
}
u32 get_screen_height(){
  if (config.use_opengl)
    return 240;
  return screen->h;
}


void clear_screen()
{
  u32 i;
  u32 pitch = get_screen_pitch();
  u16 *pixels = get_screen_ptr();

  for (i = 0; i < 240; i++)
  {
    memset(pixels, 0, 320 * 2);
    pixels += pitch;
  }
}

void clear_line_edges(u32 line_number, u32 color, u32 edge, u32 middle)
{
  u32 *dest = (u32 *)((u16 *)get_screen_ptr() +
                      (line_number * get_screen_pitch()));
  u32 i;

  color |= (color << 16);

  edge /= 2;
  middle /= 2;

  for (i = 0; i < edge; i++)
  {
    *dest = color;
    dest++;
  }

  dest += middle;

  for (i = 0; i < edge; i++)
  {
    *dest = color;
    dest++;
  }
}

void set_single_buffer_mode()
{
}

void set_multi_buffer_mode()
{
}

void clear_all_buffers()
{
}
