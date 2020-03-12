#ifndef SDL_EVENT_H
#define SDL_EVENT_H

typedef enum ekeymode{
  eMODE_END = -1,
  eMODE_KEYSYM = 0,
  eMODE_BUTTON,
  eMODE_HAT,
} eKeyMode;
typedef enum ekeycase{
  eCASE_END = -1,
  eCASE_KEYSYM = 0,
  eCASE_BUTTON,
  eCASE_HAT,
  eCASE_KEYACT,
} eKeyCase;
typedef struct _tSDLtoConfigMap
{
  eKeyMode mMode;
  eKeyCase mCase;
	u32 mSdlKey;
	u32 mIndex; // ButtonMapData
  void (*mCallback)();
} tSDLtoConfigMap;



extern SDL_Joystick *joy[64];

#endif

