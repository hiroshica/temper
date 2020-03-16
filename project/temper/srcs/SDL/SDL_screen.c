#include "../common.h"
#include "SDL_screen.h"

static SDL_Window *sWindow;
static SDL_Renderer *sRenderer;
static SDL_Texture *sScreenTexture;

u32 last_scale_factor;
//u8 *real_screen_pixels;

void init_screen(bool textureinit)
{
  set_screen_resolution();
  if (textureinit = true)
  {
    sScreenTexture = SDL_CreateTexture(sRenderer, SDL_PIXELFORMAT_ARGB8888, SDL_TEXTUREACCESS_STREAMING, SCREEN_W, SCREEN_H);
    if (sScreenTexture == NULL)
    {
      printf("texture::not create texture!(SDL_GetErr::%s)\n", SDL_GetError());
    }
  }
}

void destroy_screen()
{
  if (sWindow != NULL || sRenderer != NULL)
  {
    SDL_DestroyRenderer(sRenderer);
    SDL_DestroyWindow(sWindow);
  }
  SDL_Delay(500); /* 0.5秒停止 */
}
void exit_screen()
{
    SDL_DestroyTexture(sScreenTexture);
    destroy_screen();
}

void update_screen()
{
  if (last_scale_factor != config.scale_factor)
  {
    destroy_screen();
    init_screen(false);
  }
  {
    SDL_RenderCopy(sRenderer, sScreenTexture, NULL,NULL);
    SDL_RenderPresent(sRenderer);
  }
}

void set_screen_resolution()
{
  u32 windowflag = 0;
  u32 width = SCREEN_W;
  u32 height = SCREEN_H;

  if (config.scale_factor == SCALE_FULLSCREEN)
  {
    windowflag = SDL_WINDOW_FULLSCREEN;
  }
  else
  {
#if WIN32_BUILD | LINUX_X86_BUILD
    if (SCALE_FULLSCREEN != config.scale_factor)
    {
      //width *= config.scale_factor;
      //height *= config.scale_factor;
    }
#endif
  }

  int32_t retcode = SDL_CreateWindowAndRenderer(
      (int32_t)width, (int32_t)height,
      SDL_RENDERER_PRESENTVSYNC,
      &sWindow,
      &sRenderer);

  if (retcode == -1 || sWindow == NULL || sRenderer == NULL)
  {
    printf("!!!! not create SDL Window abort.\n error message:%s\n", SDL_GetError());
  }
  else
  {
    SDL_Delay(500); /* 0.5秒停止 */
    SDL_SetWindowTitle(sWindow,"Temper PC-Engine Emulator");
    // ここでtextureを使って一度windowのアップデートをするべき
  }
  last_scale_factor = config.scale_factor;
}

//
// draw functions
//
void *sGetPixels;
int32_t sGetPitch;
// この関数で全てのエリアをlockする
void *get_screen_ptr()
{
  SDL_LockTexture(sScreenTexture, NULL, &sGetPixels, &sGetPitch);
  return sGetPixels;
}
void release_screen_ptr(){
  SDL_UnlockTexture(sScreenTexture);
}

u32 get_screen_pitch()
{
  return (sGetPitch / 2);
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
  release_screen_ptr();
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
  release_screen_ptr();
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
