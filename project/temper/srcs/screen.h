#ifndef __SCREEN_H__
#define __SCREEN_H__

#include "common_deftypes.h"

#define SCREEN_W (320)
#define SCREEN_H (240)
#define SCREEN_WIDTH_NARROW_CHARS ((SCREEN_W / 6) - 1)
#define SCREEN_WIDTH_WIDE_CHARS   ((SCREEN_W / 8) - 1)

void *get_screen_ptr();
void release_screen_ptr();
u32 get_screen_pitch();
void init_screen(bool textureinit);
void update_screen();
void exit_screen();
void destroy_screen();

void set_screen_resolution();

void print_string_ext(const char *str, u32 fg_color, u32 bg_color,
 u32 x, u32 y, u16 *_bg_ptr, u32 pad,
 u32 screen_limit);
void print_string(const char *str, u32 fg_color, u32 bg_color,
 u32 x, u32 y, u32 screen_limit);
void print_string_bg(const char *str, u32 fg_color, u16 *bg_ptr,
 u32 x, u32 y, u32 screen_limit);

void set_font_wide();
void set_font_narrow();

void clear_screen();
void clear_line_edges(u32 line_number, u32 color, u32 edge, u32 middle);
void copy_screen(u16 *dest);
void blit_screen(u16 *src);
void copy_screen_half_intensity(u16 *dest);
void copy_screen_quarter_intensity(u16 *dest);
void buffer_quarter_intensity(u16 *_dest);
void buffer_half_intensity(u16 *_dest, u16 *_pixels, u32 pitch);
void set_multi_buffer_mode();
void set_single_buffer_mode();
void clear_all_buffers();

#endif

