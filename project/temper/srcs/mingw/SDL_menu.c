#include "../common.h"

const char *control_config_string = "PC            PC-Engine";
const u32 control_config_start_column = 64;
//const char *control_config_exit_string = "Press escape to return to the main menu";
const char *control_config_exit_string = "Press SELECT to return to the main menu";

/*
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

RG350(gcw0)
	"D-pad Up",
	"D-pad Down",
	"D-pad Left",
	"D-pad Right",
	"Y",
	"B",
	"X",
	"A",
	"Select",
	"Start",
	"L1",
	"R1",
	"L2",
	"R2",
	"L3",
	"R3",
	"Power",
*/

const u32 platform_control_count = 16;
char *platform_control_names[MAX_CONTROLS] =
{
  #ifdef WIN32_BUILD
  "Up         ", "Down       ", "Left       ", "Right      ",
  "SQUARE     ", "CROSS      ", "CIRCLE     ", "TRIANGLE   ",
  "L1         ", "R1         ",
  "L2         ", "R2         ",
  "SHARE      ", "OPTION     ",
  "L3         ", "R3         ",
 #else
  "Up         ", "Down       ", "Left       ", "Right      ",
  "Button Y   ", "Button B   ", "Button X   ", "Button A   ",
  "Start      ", "Select     ",
  "L1Shoulder ", "R1Shoulder ",
  "L2Shoulder ", "R2Shoulder ",
  "L3Shoulder ", "R3Shoulder ",
#endif

};

