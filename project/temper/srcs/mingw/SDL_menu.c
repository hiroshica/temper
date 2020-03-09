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

const u32 platform_control_count = 18;
