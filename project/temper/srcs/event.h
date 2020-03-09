#ifndef EVENT_H
#define EVENT_H

// These actions are configurable.
#define DISABLE_HAT_STATUS  1

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
  CONFIG_BUTTON_NONE,

  CONFIG_HAT_CENTER,
  CONFIG_HAT_UP,
  CONFIG_HAT_UP_RIGHT,
  CONFIG_HAT_RIGHT,
  CONFIG_HAT_DOWN_RIGHT,
  CONFIG_HAT_DOWN,
  CONFIG_HAT_DOWN_LEFT,
  CONFIG_HAT_LEFT,
  CONFIG_HAT_UP_LEFT,

  CONFIG_BUTTON_MAX,

  CONFIG_BIT_BUTTON_MAX = CONFIG_BUTTON_VI,

  //CONFIG_BUTTON_VOLUME_DOWN,
  //CONFIG_BUTTON_VOLUME_UP,
} config_buttons_enum;
// debugテーブル必ずenumと同じ並びにすること（追加もね）
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
  KEY_ACTION_NETPLAY_TALK,
  KEY_ACTION_NETPLAY_TALK_CURSOR_LEFT,
  KEY_ACTION_NETPLAY_TALK_CURSOR_RIGHT,
  KEY_ACTION_NETPLAY_TALK_CURSOR_BACKSPACE,
  KEY_ACTION_NETPLAY_TALK_CURSOR_ENTER,
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

#endif

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

#if !defined(DISABLE_HAT_STATUS)
typedef enum
{
  HAT_STATUS_UP,
  HAT_STATUS_UP_RIGHT,
  HAT_STATUS_RIGHT,
  HAT_STATUS_DOWN_RIGHT,
  HAT_STATUS_DOWN,
  HAT_STATUS_DOWN_LEFT,
  HAT_STATUS_LEFT,
  HAT_STATUS_UP_LEFT,
  HAT_STATUS_CENTER,
  HAT_STATUS_NONE,
} hat_status_enum;
#endif
typedef struct
{
  u32 action_type;          // input_action_type_enum
  u32 config_button_action; // config_buttons_enum
  u32 key_action;           // key_action_enum
  u32 key_letter;           // SDL自体の入力データ
#if !defined(DISABLE_HAT_STATUS)
  u32 hat_status;
  u32 hard_key_index;
#endif
} event_input_struct;

typedef struct
{
  gui_action_type action_type;
  u32 key_letter;
} gui_input_struct;

void initialize_event(void);
void get_gui_input(gui_input_struct *gui_input);
void clear_gui_actions(void);
void init_events(void);
void update_events(void);
u32 update_input(event_input_struct *event_input);

