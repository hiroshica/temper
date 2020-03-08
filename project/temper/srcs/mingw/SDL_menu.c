#include "../common.h"

const char *control_config_string = "PC            PC-Engine";
const u32 control_config_start_column = 64;
const char *control_config_exit_string = "Press escape to return to the main menu";
//const char *control_config_exit_string = "Press SELECT to return to the main menu";

char *platform_control_names[MAX_CONTROLS] =
{
	"Up         ", "Down       ", "Left       ", "Right      ",
	"OPTION     ", "SHARE      ",
	"SQUARE     ", "TRIANGLE   ", "CROSS      ", "CIRCLE     ",
	"L1         ", "L2         ", "L3         ",
	"R1         ", "R2         ", "R3         ",
	"PS         ", "TOUCHPAD   ",
};

/*
 * SDL(windows)でのPS4 button key number
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

const u32 platform_control_count = 18;
