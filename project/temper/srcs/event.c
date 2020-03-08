#include "common.h"

//#define LOG_CONTROLS

char *config_name_table[] = 
{
  "CONFIG_BUTTON_UP",
  "CONFIG_BUTTON_DOWN",
  "CONFIG_BUTTON_LEFT",
  "CONFIG_BUTTON_RIGHT",
  // option/share
  "CONFIG_BUTTON_RUN",
  "CONFIG_BUTTON_SELECT",
  // x/y/a/b
  "CONFIG_BUTTON_I",
  "CONFIG_BUTTON_II",
  "CONFIG_BUTTON_III",
  "CONFIG_BUTTON_IV",
  // L123
  "CONFIG_BUTTON_LOAD_STATE",
  "CONFIG_BUTTON_V",
  "CONFIG_BUTTON_RAPID_ONOFF",
  // R123
  "CONFIG_BUTTON_SAVE_STATE",
  "CONFIG_BUTTON_VI",
  "CONFIG_BUTTON_FAST_FORWARD",
  // PS
  "CONFIG_BUTTON_MENU",
  "CONFIG_BUTTON_NONE",

  "CONFIG_BUTTON_UP_LEFT",
  "CONFIG_BUTTON_UP_RIGHT",
  "CONFIG_BUTTON_DOWN_LEFT",
  "CONFIG_BUTTON_DOWN_RIGHT",

  "CONFIG_BUTTON_MAX",
};



// Make menu.c match this.

u32 config_to_io_map[] =
    {
        IO_BUTTON_UP,
        IO_BUTTON_DOWN,
        IO_BUTTON_LEFT,
        IO_BUTTON_RIGHT,
        IO_BUTTON_I,
        IO_BUTTON_II,
        IO_BUTTON_III,
        IO_BUTTON_IV,
        IO_BUTTON_V,
        IO_BUTTON_VI,
        IO_BUTTON_RUN,
        IO_BUTTON_SELECT};

typedef struct tRapidStatus
{
  u32 m_Status;
  u32 m_Active;
  s32 m_frameCount;
  u32 m_bottunStatus; // IO_BUTTON_?? work.

} RapidStatus;

#define MAX_HARD_KEY (24)
static u32 m_RapidSelect = 0;
static RapidStatus m_RapidStatus[MAX_HARD_KEY];
//static u32 rapid_fire_state = 0;
//static u32 rapid_fire_mask = 0;
static u32 button_status = 0xFFFFFFFF;  // emulatorへ送り込むキー情報
static u32 talk_mode = 0;
static u32 talk_x = 0;
static char talk_message[128];

void init_events(void)
{
  u32 iI;
  for (iI = 0; iI < MAX_HARD_KEY; ++iI)
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

  case KEY_ACTION_NETPLAY_TALK:
    if (netplay.active)
    {
      talk_message[0] = '_';
      talk_message[1] = 0;
      config.input_message = talk_message;
      talk_x = 0;
      talk_mode = 1;
    }
    break;
  }
}

void update_events(void)
{
  event_input_struct event_input;
  u32 config_button_action;
  u32 talk_message_limit =
      (SCREEN_WIDTH_NARROW_CHARS * 2) - (strlen(config.netplay_username) + 2);

  while (update_input(&event_input))
  {
    if (talk_mode)
    {
      if (event_input.action_type == INPUT_ACTION_TYPE_PRESS)
      {
        switch (event_input.key_action)
        {
        case KEY_ACTION_NETPLAY_TALK_CURSOR_ENTER:
        {
          char full_talk_message[128];
          talk_message[talk_x] = 0;

          if (talk_message[0])
          {
            sprintf(full_talk_message, "%s: %s", config.netplay_username,
                    talk_message);

            status_message_raw(full_talk_message);
            if (strlen(full_talk_message) > SCREEN_WIDTH_NARROW_CHARS)
            {
              status_message_raw(full_talk_message +
                                 SCREEN_WIDTH_NARROW_CHARS);
            }
            send_talk_message(full_talk_message);
          }

          config.input_message = NULL;
          talk_mode = 0;
          break;
        }

        case KEY_ACTION_QUIT:
          config.input_message = NULL;
          talk_mode = 0;
          break;

        case KEY_ACTION_NETPLAY_TALK_CURSOR_BACKSPACE:
          if (talk_x > 0)
          {
            talk_x--;
            talk_message[talk_x + 1] = 0;
            talk_message[talk_x] = '_';
          }
          break;

        default:
          if (event_input.key_letter && (talk_x < talk_message_limit))
          {
            talk_message[talk_x] = event_input.key_letter;
            talk_x++;
            talk_message[talk_x] = '_';
            talk_message[talk_x + 1] = 0;
          }
          break;
        }
      }
    }
    else
    {
      config_button_action = event_input.config_button_action;
      if (config_button_action <= CONFIG_BUTTON_SELECT)
      {
#if false
        u32 io_button = config_to_io_map[config_button_action];
        u32 index = event_input.hard_key_index; // config_button_action;
        m_RapidStatus[index].m_Status = event_input.action_type;
        if (!m_RapidSelect)
        {
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
          if (event_input.action_type == INPUT_ACTION_TYPE_PRESS)
          {

            m_RapidStatus[index].m_Active ^= 1;
            m_RapidStatus[index].m_bottunStatus = io_button;
            m_RapidStatus[index].m_frameCount = 0;
            if(config.rapid_frame[index] == 0){
              config.rapid_frame[index] = 1;
            }
          }
        }
#endif
      }
      else if (config_button_action == CONFIG_BUTTON_RAPID_ONOFF)
      {
        if (event_input.action_type == INPUT_ACTION_TYPE_PRESS)
        {
          m_RapidSelect = 1;
        }
        else
        {
          m_RapidSelect = 0;
        }
      }
      else if (event_input.action_type == INPUT_ACTION_TYPE_PRESS)
      {
        switch (config_button_action)
        {
        case CONFIG_BUTTON_MENU:
          menu(0);
          return;

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
          break;
        }

        case CONFIG_BUTTON_FAST_FORWARD:
          config.fast_forward ^= 1;
          break;
        }
      }
      config_PceKeys(event_input.key_action);
    }
  }
  u32 iI;
  for (iI = 0; iI < CONFIG_BUTTON_MAX; ++iI)
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

  if (netplay.active)
  {
    switch (config.netplay_type)
    {
    case NETPLAY_TYPE_SERVER:
      netplay_frame_update(button_status, &(io.button_status[0]),
                           &(io.button_status[1]));
      break;

    case NETPLAY_TYPE_CLIENT:
      netplay_frame_update(button_status, &(io.button_status[1]),
                           &(io.button_status[0]));
      break;
    }
  }
  else
  {
    io.button_status[0] = button_status;
  }

#ifdef LOG_CONTROLS
  static FILE *control_log = NULL;
  static u32 frame_number = 0;

  if (config.netplay_type != NETPLAY_TYPE_NONE)
  {
    if (control_log == NULL)
    {
      if (config.netplay_type == NETPLAY_TYPE_CLIENT)
        control_log = fopen("control_log_client.txt", "wb");
      else
        control_log = fopen("control_log_server.txt", "wb");
    }

    fprintf(control_log, "Frame %d (%d): %08x %08x\n", netplay.frame_number,
            vce.frames_rendered, io.button_status[0], io.button_status[1]);
  }
  else
  {
    if (control_log)
      fclose(control_log);
  }
#endif
}
