#ifndef SDL_EVENT_H
#define SDL_EVENT_H

typedef enum ekeymode{
  eMODE_END = -1,
  eMODE_KEYSYM = 0,
  eMODE_BUTTON,
  eMODE_HAT,
} eKeyMode;
typedef struct _tSDLtoConfigMap
{
  eKeyMode mode;
	u32 sdl_key;
	config_buttons_enum index; // ButtonMapData
} tSDLtoConfigMap;



extern SDL_Joystick *joy[64];

#endif

