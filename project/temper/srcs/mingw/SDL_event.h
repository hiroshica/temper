#ifndef SDL_EVENT_H
#define SDL_EVENT_H

#if 0
typedef enum
{
  PC_BUTTON_UP,
  PC_BUTTON_DOWN,
  PC_BUTTON_LEFT,
  PC_BUTTON_RIGHT,
  PC_BUTTON_1,
  PC_BUTTON_2,
  PC_BUTTON_3,
  PC_BUTTON_4,
  PC_BUTTON_5,
  PC_BUTTON_6,
  PC_BUTTON_7,
  PC_BUTTON_8,
  PC_BUTTON_9,
  PC_BUTTON_10,
  PC_BUTTON_11,
  PC_BUTTON_12,
  PC_BUTTON_NONE
} pc_buttons_enum;
#endif

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

