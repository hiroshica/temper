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
        {"          UP", k_INDEX_EFFECTIVE|0x00000100 },
        {"        DOWN", k_INDEX_EFFECTIVE|0x00000101 },
        {"        LEFT", k_INDEX_EFFECTIVE|0x00000102 },
        {"       RIGHT", k_INDEX_EFFECTIVE|0x00000103 },

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
