#include "common.h"

//#define LOG_CONTROLS

// debug用
char *config_name_table[] =
    {
        "CONFIG_BUTTON_UP",
        "CONFIG_BUTTON_DOWN",
        "CONFIG_BUTTON_LEFT",
        "CONFIG_BUTTON_RIGHT",

        "CONFIG_BUTTON_RUN",
        "CONFIG_BUTTON_SELECT",

        "CONFIG_BUTTON_I",
        "CONFIG_BUTTON_II",
        "CONFIG_BUTTON_III",
        "CONFIG_BUTTON_IV",
        "CONFIG_BUTTON_V",
        "CONFIG_BUTTON_VI",

        "CONFIG_BUTTON_LOAD_STATE",
        "CONFIG_BUTTON_SAVE_STATE",
        "CONFIG_BUTTON_FAST_FORWARD",

        "CONFIG_BUTTON_RAPID_ONOFF",
        "CONFIG_BUTTON_MENU",

        "CONFIG_HAT_CENTER",
        "CONFIG_HAT_UP",
        "CONFIG_HAT_UP_RIGHT",
        "CONFIG_HAT_RIGHT",
        "CONFIG_HAT_DOWN_RIGHT",
        "CONFIG_HAT_DOWN",
        "CONFIG_HAT_DOWN_LEFT",
        "CONFIG_HAT_LEFT",
        "CONFIG_HAT_UP_LEFT",

        "CONFIG_BUTTON_NONE",
        "CONFIG_BUTTON_MAX",
};

// Make menu.c match this.
// configからpceのbitに変換するテーブル
// cnfigと同じ並びじゃないとバグる
u32 config_to_io_map[] =
    {
        IO_BUTTON_UP,
        IO_BUTTON_DOWN,
        IO_BUTTON_LEFT,
        IO_BUTTON_RIGHT,
        IO_BUTTON_RUN,
        IO_BUTTON_SELECT,
        IO_BUTTON_I,
        IO_BUTTON_II,
        IO_BUTTON_III,
        IO_BUTTON_IV,
        IO_BUTTON_V,
        IO_BUTTON_VI,
};
#define IO_BUTTON_UDLR (IO_BUTTON_UP | IO_BUTTON_DOWN | IO_BUTTON_LEFT | IO_BUTTON_RIGHT)

typedef struct tRapidStatus
{
  u32 m_Status;
  u32 m_Active;
  s32 m_frameCount;
  u32 m_bottunStatus; // IO_BUTTON_?? work.

} RapidStatus;

u32 m_RapidSelect = 0;
static RapidStatus m_RapidStatus[PAD_STOCK_MAX];
static u32 button_status = 0xFFFFFFFF; // emulatorへ送り込むキー情報
static u32 talk_mode = 0;
static u32 talk_x = 0;
static char talk_message[128];

void create_hat_key(u32 hat_buttons_press){
  button_status |=
            (IO_BUTTON_UP | IO_BUTTON_DOWN | IO_BUTTON_LEFT | IO_BUTTON_RIGHT) &
            ~hat_buttons_press;
        button_status &= ~hat_buttons_press;
}
void init_events(void)
{
  u32 iI;
  for (iI = 0; iI < PAD_STOCK_MAX; ++iI)
  {
    m_RapidStatus[iI].m_Status = INPUT_ACTION_TYPE_RELEASE;
    m_RapidStatus[iI].m_Active = 0;
    m_RapidStatus[iI].m_frameCount = 0;
  }
  m_RapidSelect = 0;
}

void config_PceKeys(u32 key_action)
{
  switch (key_action)
  {
  case KEY_ACTION_QUIT:
    quit();
    break;

  case KEY_ACTION_BG_OFF:
    config.bg_off ^= 1;
    break;

  case KEY_ACTION_SPR_OFF:
    config.spr_off ^= 1;
    break;

  case KEY_ACTION_DEBUG_BREAK:
    set_debug_mode(DEBUG_STEP);
    break;
  }
}

static s32 actionindex;
u32 getactiondata(event_input_struct *event_input)
{
  u32 retcode;
  retcode = event_input->config_button_action[actionindex];
  if (retcode != CONFIG_BUTTON_NONE)
  {
    actionindex++;
  }
  return retcode;
}

void update_events(void)
{
  event_input_struct event_input;
  u32 config_button_action;

  init_update_input();

  while (update_input(&event_input))
  {
    actionindex = 0;
    while (1)
    {
      config_button_action = getactiondata(&event_input);
      if (config_button_action == CONFIG_BUTTON_NONE)
        break;
      // joypad 入力判定
      if (config_button_action < CONFIG_BIT_BUTTON_MAX)
      {
        // 今のこの処理だとconfig.pad内の番号がpceのキー番号になっている
        u32 io_button = config_to_io_map[config_button_action];
        u32 index = config_button_action;
        m_RapidStatus[index].m_Status = event_input.action_type;
        if (!m_RapidSelect)
        {
          // 連写モード切り替えが押されていないので連写モードではない普通のキーon/offを作成する
          if (!m_RapidStatus[index].m_Active)
          {
            if (event_input.action_type == INPUT_ACTION_TYPE_RELEASE)
            {
              button_status |= io_button;
            }
            else
            {
              button_status &= ~io_button;
            }
          }
        }
        else
        {
          // 連写モード切り替えが押されているので連射バッファを初期化して登録解除する
          if (event_input.action_type == INPUT_ACTION_TYPE_PRESS)
          {
            m_RapidStatus[index].m_Active ^= 1;
            m_RapidStatus[index].m_bottunStatus = io_button;
            m_RapidStatus[index].m_frameCount = 0;
            if (config.rapid_frame[index] == 0)
            {
              config.rapid_frame[index] = 1;
            }
          }
        }
      }
      else if (event_input.action_type == INPUT_ACTION_TYPE_PRESS)
      {
        switch (config_button_action)
        {
        case CONFIG_HAT_UP:
          create_hat_key(IO_BUTTON_UP);
          break;
        case CONFIG_HAT_UP_RIGHT:
          create_hat_key((IO_BUTTON_UP | IO_BUTTON_RIGHT));
          break;
        case CONFIG_HAT_RIGHT:
          create_hat_key(IO_BUTTON_RIGHT);
          break;
        case CONFIG_HAT_DOWN_RIGHT:
          create_hat_key((IO_BUTTON_DOWN | IO_BUTTON_RIGHT));
          break;
        case CONFIG_HAT_DOWN:
          create_hat_key(IO_BUTTON_DOWN);
          break;
        case CONFIG_HAT_DOWN_LEFT:
          create_hat_key((IO_BUTTON_DOWN | IO_BUTTON_LEFT));
          break;
        case CONFIG_HAT_LEFT:
          create_hat_key(IO_BUTTON_LEFT);
          break;
        case CONFIG_HAT_UP_LEFT:
          create_hat_key((IO_BUTTON_UP | IO_BUTTON_LEFT));
          break;
        case CONFIG_HAT_CENTER:
          create_hat_key(0);
          break;

        case CONFIG_BUTTON_MENU:
          menu(0);
          return;

        case CONFIG_BUTTON_RAPID_ONOFF:
          // 連写モード切り替えキーをトグルする
          m_RapidSelect ^= 1;
          break;

        case CONFIG_BUTTON_LOAD_STATE:
        {
          char state_name[MAX_PATH];
          sprintf(state_name, "%s_%d.svs", config.rom_filename,
                  config.savestate_number);

          load_state(state_name, NULL, 0);
        }
          return;

        case CONFIG_BUTTON_SAVE_STATE:
        {
          char state_name[MAX_PATH];
          sprintf(state_name, "%s_%d.svs", config.rom_filename,
                  config.savestate_number);

          if ((config.snapshot_format) == SS_SNAPSHOT_OFF)
          {
            save_state(state_name, NULL);
          }
          else
          {
            u16 *screen_capture = malloc(320 * 240 * sizeof(u16));
            copy_screen(screen_capture);
            save_state(state_name, screen_capture);
            free(screen_capture);
          }
        }
        break;

        case CONFIG_BUTTON_FAST_FORWARD:
          config.fast_forward ^= 1;
          break;
        }
      }
      else if (event_input.action_type == INPUT_ACTION_TYPE_RELEASE)
      {
        if (config_button_action == CONFIG_HAT_CENTER)
        {
          //button_status |= (IO_BUTTON_UDLR);
        }
      }
    }
    config_PceKeys(event_input.key_action); // emulatorの設定キーの登録
  }
  // 連射生成
  u32 iI;
  for (iI = 0; iI < CONFIG_BIT_BUTTON_MAX; ++iI)
  {
    if (m_RapidStatus[iI].m_Active && m_RapidStatus[iI].m_Status == INPUT_ACTION_TYPE_PRESS)
    {
      if (m_RapidStatus[iI].m_frameCount == config.rapid_frame[iI])
      {
        button_status &= ~m_RapidStatus[iI].m_bottunStatus;
        m_RapidStatus[iI].m_frameCount = 0;
      }
      else
      {
        button_status |= m_RapidStatus[iI].m_bottunStatus;
        m_RapidStatus[iI].m_frameCount++;
      }
    }
  }
  // 連射生成ここまで

  // 最終的にできたキー入力をセットする
  io.button_status[0] = button_status;

#ifdef LOG_CONTROLS
  static FILE *control_log = NULL;
  static u32 frame_number = 0;
  {
    if (control_log)
      fclose(control_log);
  }
#endif
}
