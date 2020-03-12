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

        {"      OPTION", k_INDEX_EFFECTIVE|9 },
        {"       SHARE", k_INDEX_EFFECTIVE|8 },

        {"      SQUARE", k_INDEX_EFFECTIVE|0 },
        {"       CROSS", k_INDEX_EFFECTIVE|1 },
        {"      CIRCLE", k_INDEX_EFFECTIVE|2 },
        {"    TRIANGLE", k_INDEX_EFFECTIVE|3 },

        {"          L1", k_INDEX_EFFECTIVE|4 },
        {"          L2", k_INDEX_EFFECTIVE|6 },
        {"          L3", k_INDEX_EFFECTIVE|10 },

        {"          R1", k_INDEX_EFFECTIVE|5 },
        {"          R2", k_INDEX_EFFECTIVE|7 },
        {"          R3", k_INDEX_EFFECTIVE|11 },

        {"          PS", k_INDEX_EFFECTIVE|12 },
        {"   TOUCH PAD", k_INDEX_EFFECTIVE|13 },

        {"        None", k_INDEX_NONE },
};

const char *control_config_string = "PC-Engine            PC";
const u32 control_config_start_column = 64;
const char *control_config_exit_string = "Press escape to return to the main menu";
#if 0
char *platform_control_names[MAX_CONTROLS] =
{
	"Up         ", "Down       ", "Left       ", "Right      ",
	"OPTION     ", "SHARE      ",
	"SQUARE     ", "TRIANGLE   ", "CROSS      ", "CIRCLE     ",
	"L1         ", "L2         ", "L3         ",
	"R1         ", "R2         ", "R3         ",
	"PS         ", "TOUCHPAD   ",
};

const u32 platform_control_count = 18;
#endif

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
		{eMODE_KEYSYM, eCASE_KEYSYM, SDLK_UP, CONFIG_BUTTON_UP},
		{eMODE_KEYSYM, eCASE_KEYSYM, SDLK_DOWN, CONFIG_BUTTON_DOWN},
		{eMODE_KEYSYM, eCASE_KEYSYM, SDLK_LEFT, CONFIG_BUTTON_LEFT},
		{eMODE_KEYSYM, eCASE_KEYSYM, SDLK_RIGHT, CONFIG_BUTTON_RIGHT},
		{eMODE_KEYSYM, eCASE_KEYSYM, SDLK_5, CONFIG_BUTTON_RUN},
		{eMODE_KEYSYM, eCASE_KEYSYM, SDLK_6, CONFIG_BUTTON_SELECT},
		{eMODE_KEYSYM, eCASE_KEYSYM, SDLK_z, CONFIG_BUTTON_I},
		{eMODE_KEYSYM, eCASE_KEYSYM, SDLK_x, CONFIG_BUTTON_II},
		{eMODE_KEYSYM, eCASE_KEYSYM, SDLK_c, CONFIG_BUTTON_III},
		{eMODE_KEYSYM, eCASE_KEYSYM, SDLK_a, CONFIG_BUTTON_IV},
		{eMODE_KEYSYM, eCASE_KEYSYM, SDLK_s, CONFIG_BUTTON_V},
		{eMODE_KEYSYM, eCASE_KEYSYM, SDLK_d, CONFIG_BUTTON_VI},

		{eMODE_KEYSYM, eCASE_KEYSYM, SDLK_ESCAPE, CONFIG_BUTTON_MENU},
		{eMODE_KEYSYM, eCASE_KEYSYM, SDLK_m, CONFIG_BUTTON_MENU},
		{eMODE_KEYSYM, eCASE_KEYSYM, SDLK_r, CONFIG_BUTTON_RAPID_ONOFF},
		{eMODE_KEYSYM, eCASE_KEYSYM, SDLK_BACKQUOTE, CONFIG_BUTTON_FAST_FORWARD},
		{eMODE_KEYSYM, eCASE_KEYSYM, SDLK_F5, CONFIG_BUTTON_SAVE_STATE},
		{eMODE_KEYSYM, eCASE_KEYSYM, SDLK_F7, CONFIG_BUTTON_LOAD_STATE},

		{eMODE_KEYSYM, eCASE_KEYACT, SDLK_1, KEY_ACTION_BG_OFF},
		{eMODE_KEYSYM, eCASE_KEYACT, SDLK_2, KEY_ACTION_SPR_OFF},
		{eMODE_KEYSYM, eCASE_KEYACT, SDLK_F1, KEY_ACTION_DEBUG_BREAK},

		{eMODE_BUTTON, eCASE_BUTTON, 9, 4},
		{eMODE_BUTTON, eCASE_BUTTON, 8, 5},

		{eMODE_BUTTON, eCASE_BUTTON, 0, 6},
		{eMODE_BUTTON, eCASE_BUTTON, 3, 7},
		{eMODE_BUTTON, eCASE_BUTTON, 1, 8},
		{eMODE_BUTTON, eCASE_BUTTON, 2, 9},

		{eMODE_BUTTON, eCASE_BUTTON, 4, 10},
		{eMODE_BUTTON, eCASE_BUTTON, 6, 11},
		{eMODE_BUTTON, eCASE_BUTTON, 7, 12},

		{eMODE_BUTTON, eCASE_BUTTON, 5, 13},
		{eMODE_BUTTON, eCASE_BUTTON, 7, 14},
		{eMODE_BUTTON, eCASE_BUTTON, 11, 15},

		{eMODE_BUTTON, eCASE_BUTTON, 12, 16},
		{eMODE_BUTTON, eCASE_BUTTON, 13, 17},

		{eMODE_HAT, eCASE_HAT, SDL_HAT_UP, CONFIG_HAT_UP},
		{eMODE_HAT, eCASE_HAT, SDL_HAT_RIGHTUP, CONFIG_HAT_UP_RIGHT},
		{eMODE_HAT, eCASE_HAT, SDL_HAT_RIGHT, CONFIG_HAT_RIGHT},
		{eMODE_HAT, eCASE_HAT, SDL_HAT_RIGHTDOWN, CONFIG_HAT_DOWN_RIGHT},
		{eMODE_HAT, eCASE_HAT, SDL_HAT_DOWN, CONFIG_HAT_DOWN},
		{eMODE_HAT, eCASE_HAT, SDL_HAT_LEFTDOWN, CONFIG_HAT_DOWN_LEFT},
		{eMODE_HAT, eCASE_HAT, SDL_HAT_LEFT, CONFIG_HAT_LEFT},
		{eMODE_HAT, eCASE_HAT, SDL_HAT_LEFTUP, CONFIG_HAT_UP_LEFT},

		{eMODE_END, eCASE_END, -1, -1},
};
