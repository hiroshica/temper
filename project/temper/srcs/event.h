#ifndef __EVENT_H__
#define __EVENT_H__

// These actions are configurable.

/*
 * このenumはSDL入力時はbit fieldとして
 * それ以外はindexとして扱う
 */
typedef enum _config_buttons_enum
{
  CONFIG_BUTTON_UP,
  CONFIG_BUTTON_DOWN,
  CONFIG_BUTTON_LEFT,
  CONFIG_BUTTON_RIGHT,

  CONFIG_BUTTON_RUN,
  CONFIG_BUTTON_SELECT,

  CONFIG_BUTTON_I,
  CONFIG_BUTTON_II,
  CONFIG_BUTTON_III,
  CONFIG_BUTTON_IV,
  CONFIG_BUTTON_V,
  CONFIG_BUTTON_VI,

  CONFIG_BUTTON_LOAD_STATE,
  CONFIG_BUTTON_SAVE_STATE,
  CONFIG_BUTTON_FAST_FORWARD,
 
  CONFIG_BUTTON_RAPID_ONOFF,
  CONFIG_BUTTON_MENU,

  CONFIG_HAT_CENTER,
  CONFIG_HAT_UP,
  CONFIG_HAT_UP_RIGHT,
  CONFIG_HAT_RIGHT,
  CONFIG_HAT_DOWN_RIGHT,
  CONFIG_HAT_DOWN,
  CONFIG_HAT_DOWN_LEFT,
  CONFIG_HAT_LEFT,
  CONFIG_HAT_UP_LEFT,

  CONFIG_BUTTON_NONE,
  CONFIG_BUTTON_MAX,

  CONFIG_BIT_BUTTON_MAX = CONFIG_BUTTON_VI+1,

  //CONFIG_BUTTON_VOLUME_DOWN,
  //CONFIG_BUTTON_VOLUME_UP,
} config_buttons_enum;
// debugテーブル必ずenumと同じ並びにすること（追加もね） event.c
extern char *config_name_table[];

// These actions can't be configured and are triggered by
// fixed inputs.
// emulatorの動作を司るconfigをコントロールするのに使われている
typedef enum
{
  KEY_ACTION_QUIT,
  KEY_ACTION_BG_OFF,
  KEY_ACTION_SPR_OFF,
  KEY_ACTION_DEBUG_BREAK,
  KEY_ACTION_DEBUG_TILE,
  KEY_ACTION_DEBUG_MAP,
  KEY_ACTION_DEBUG_SPR,
  KEY_ACTION_NONE,
} key_action_enum;

// emulatorのmenu操作に使われている
typedef enum
{
  CURSOR_UP,
  CURSOR_DOWN,
  CURSOR_LEFT,
  CURSOR_RIGHT,
  CURSOR_SELECT,
  CURSOR_BACK,
  CURSOR_EXIT,
  CURSOR_PAGE_UP,
  CURSOR_PAGE_DOWN,
  CURSOR_LETTER,
  CURSOR_NONE
} gui_action_type;

// These define autorepeat values (in microseconds), tweak as necessary.

#define BUTTON_REPEAT_START    250000
#define BUTTON_REPEAT_CONTINUE 50000

typedef enum
{
  BUTTON_NOT_HELD,
  BUTTON_HELD_INITIAL,
  BUTTON_HELD_REPEAT
} button_repeat_state_type;

typedef enum
{
  INPUT_ACTION_TYPE_NONE = -1,
  INPUT_ACTION_TYPE_PRESS = 0,
  INPUT_ACTION_TYPE_RELEASE,
  INPUT_ACTION_TYPE_REPEAT
} input_action_type_enum;

typedef struct
{
  u32 action_type;          // input_action_type_enum
  u32 config_button_action[CONFIG_BIT_BUTTON_MAX]; // config_buttons_enum
  u32 key_action;           // key_action_enum
  u32 key_letter;           // SDL自体の入力データ
  //u32 hat_status;
  //u32 hard_key_index;
} event_input_struct;

typedef struct
{
  gui_action_type action_type;
  u32 key_letter;
} gui_input_struct;

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

typedef enum epadmode{
  ePADMODE_NONE = -1,
  ePADMODE_ON = 1,
} ePadMode;

typedef struct _tSDLtoConfigMap
{
  eKeyMode mMode;
  eKeyCase mCase;
  ePadMode mPadMode;  // mIndexの値がPadの番号に化ける
	u32 mSdlKey;
	u32 mIndex; // ButtonMapData
  void (*mCallback)();
} tSDLtoConfigMap;

// analogしきい値-32767～32767まで
#define kLOWLIMIT ((s16)0x0800)
#define kLIMIT ((s16)0x4000)

void initialize_event(void);
void get_gui_input(gui_input_struct *gui_input);
void clear_gui_actions(void);
void init_events(void);
void update_events(void);
void init_update_input();
u32 update_input(event_input_struct *event_input);

#endif