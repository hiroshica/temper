#include "../setup.h"

/*
SDLのpad button number (PS4)
  0 = SQUARE
  1 = CROSS
  2 = CIRCLE
  3 = TRIANGLE
  4 = L1
  5 = R1
  6 = L2
  7 = R2
  8 = SHARE
  9 = OPTION
  10 = L3
  11 = R3
  12 = PS
  13 = touchpad
*/
// このテーブルの並びをconfig.padに記録する
//
tButtonMapData ButtonMapData[PAD_STOCK_MAX] = {
        /*
        {"          UP", k_INDEX_EFFECTIVE|0x00000100 },
        {"        DOWN", k_INDEX_EFFECTIVE|0x00000101 },
        {"        LEFT", k_INDEX_EFFECTIVE|0x00000102 },
        {"       RIGHT", k_INDEX_EFFECTIVE|0x00000103 },
        */

        {"       START", k_INDEX_EFFECTIVE|9 },
        {"      SELECT", k_INDEX_EFFECTIVE|8 },

        {"    Y BUTTON", k_INDEX_EFFECTIVE|0 },
        {"    B BUTTON", k_INDEX_EFFECTIVE|1 },
        {"    A BUTTON", k_INDEX_EFFECTIVE|2 },
        {"    X BUTTON", k_INDEX_EFFECTIVE|3 },

        {"   L1 BUTTON", k_INDEX_EFFECTIVE|4 },
        {"   L2 BUTTON", k_INDEX_EFFECTIVE|6 },
        {"   L3 BUTTON", k_INDEX_EFFECTIVE|10 },

        {"   R1 BUTTON", k_INDEX_EFFECTIVE|5 },
        {"   R2 BUTTON", k_INDEX_EFFECTIVE|7 },
        {"   R3 BUTTON", k_INDEX_EFFECTIVE|11 },

        {"       POWER", k_INDEX_EFFECTIVE|12 },

        {"        None", k_INDEX_NONE },
};

const char *control_config_string = "PC-Engine            PC";
const u32 control_config_start_column = 64;
const char *control_config_exit_string = "Press escape to return to the main menu";
/*
 * eMODE_KEYSYM のデータ内訳
 * sdl_key = SDLK_???
 * index = config_buttons_enumの値
 * eMODE_BUTTON のデータ内訳
 * sdl_key = JoyPadのボタン番号
 * index = platform_control_namesのindex
 */
tSDLtoConfigMap SDLtoConfigMap[] =
	{
		{eMODE_KEYSYM, eCASE_KEYSYM, ePADMODE_NONE, SDLK_UP, CONFIG_BUTTON_UP},
		{eMODE_KEYSYM, eCASE_KEYSYM, ePADMODE_NONE, SDLK_DOWN, CONFIG_BUTTON_DOWN},
		{eMODE_KEYSYM, eCASE_KEYSYM, ePADMODE_NONE, SDLK_LEFT, CONFIG_BUTTON_LEFT},
		{eMODE_KEYSYM, eCASE_KEYSYM, ePADMODE_NONE, SDLK_RIGHT, CONFIG_BUTTON_RIGHT},

		{eMODE_KEYSYM, eCASE_KEYSYM,   ePADMODE_ON, SDLK_RETURN, 9},
		{eMODE_KEYSYM, eCASE_KEYSYM,   ePADMODE_ON, SDLK_ESCAPE, 8},

		{eMODE_KEYSYM, eCASE_KEYSYM,   ePADMODE_ON, SDLK_LSHIFT, 0},
		{eMODE_KEYSYM, eCASE_KEYSYM,   ePADMODE_ON, SDLK_LALT, 3},
		{eMODE_KEYSYM, eCASE_KEYSYM,   ePADMODE_ON, SDLK_SPACE, 1},
		{eMODE_KEYSYM, eCASE_KEYSYM,   ePADMODE_ON, SDLK_LCTRL, 2},

		{eMODE_KEYSYM, eCASE_KEYSYM,   ePADMODE_ON, SDLK_TAB, 4},
		{eMODE_KEYSYM, eCASE_KEYSYM,   ePADMODE_ON, SDLK_PAGEUP, 6},
		{eMODE_KEYSYM, eCASE_KEYSYM,   ePADMODE_ON, SDLK_KP_DIVIDE, 10},

		{eMODE_KEYSYM, eCASE_KEYSYM,   ePADMODE_ON, SDLK_BACKSPACE, 5},
		{eMODE_KEYSYM, eCASE_KEYSYM,   ePADMODE_ON, SDLK_PAGEDOWN, 7},
		{eMODE_KEYSYM, eCASE_KEYSYM,   ePADMODE_ON, SDLK_KP_PERIOD, 11},

		{eMODE_KEYSYM, eCASE_KEYSYM,   ePADMODE_ON, SDLK_HOME, 12},

		{eMODE_HAT, eCASE_HAT, ePADMODE_NONE, SDL_HAT_UP, CONFIG_HAT_UP},
		{eMODE_HAT, eCASE_HAT, ePADMODE_NONE, SDL_HAT_RIGHTUP, CONFIG_HAT_UP_RIGHT},
		{eMODE_HAT, eCASE_HAT, ePADMODE_NONE, SDL_HAT_RIGHT, CONFIG_HAT_RIGHT},
		{eMODE_HAT, eCASE_HAT, ePADMODE_NONE, SDL_HAT_RIGHTDOWN, CONFIG_HAT_DOWN_RIGHT},
		{eMODE_HAT, eCASE_HAT, ePADMODE_NONE, SDL_HAT_DOWN, CONFIG_HAT_DOWN},
		{eMODE_HAT, eCASE_HAT, ePADMODE_NONE, SDL_HAT_LEFTDOWN, CONFIG_HAT_DOWN_LEFT},
		{eMODE_HAT, eCASE_HAT, ePADMODE_NONE, SDL_HAT_LEFT, CONFIG_HAT_LEFT},
		{eMODE_HAT, eCASE_HAT, ePADMODE_NONE, SDL_HAT_LEFTUP, CONFIG_HAT_UP_LEFT},

		{eMODE_END, eCASE_END, ePADMODE_NONE, -1, -1},
};
