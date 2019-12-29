#include "../common.h"
#include "SDL_event.h"


#define kLIMIT (0x00001000)
u32 sdl_to_config_map[][2] =
    {
        { SDLK_UP, (u32)CONFIG_BUTTON_UP},
        { SDLK_DOWN, (u32)CONFIG_BUTTON_DOWN},
        { SDLK_LEFT, (u32)CONFIG_BUTTON_LEFT},
        { SDLK_RIGHT, (u32)CONFIG_BUTTON_RIGHT},
        { SDLK_LSHIFT, (u32)CONFIG_BUTTON_IV},
        { SDLK_LALT, (u32)CONFIG_BUTTON_I},
        { SDLK_SPACE, (u32)CONFIG_BUTTON_V},
        { SDLK_LCTRL, (u32)CONFIG_BUTTON_II},
        { SDLK_ESCAPE, (u32)CONFIG_BUTTON_SELECT},
        { SDLK_RETURN, (u32)CONFIG_BUTTON_RUN},
        { SDLK_TAB, (u32)CONFIG_BUTTON_III},
        { SDLK_BACKSPACE, (u32)CONFIG_BUTTON_VI},
        { SDLK_PAGEUP, (u32)CONFIG_BUTTON_SAVE_STATE},
        { SDLK_PAGEDOWN, (u32)CONFIG_BUTTON_LOAD_STATE},
        { SDLK_KP_DIVIDE, (u32)CONFIG_BUTTON_MENU},
        { SDLK_KP_PERIOD, (u32)CONFIG_BUTTON_FAST_FORWARD},
        { SDLK_HOME, (u32)CONFIG_BUTTON_MENU},
        {(u32)-1,(u32)-1,},
    };
        

u32 key_map(u32 keys)
{
  unsigned char i;

  for (i = 0; sdl_to_config_map[i][0] != (u32)-1; i++)
  {
    if (keys == sdl_to_config_map[i][0])
    {
      return sdl_to_config_map[i][1];
    }
  }
  return CONFIG_BUTTON_NONE;
}

u32 joy_button_map(u32 button)
{
  //printf("%d\n",button);
  return config.pad[button + 4];
}

u32 joy_hat_map(u32 hat_value)
{
  switch (hat_value)
  {
  case SDL_HAT_UP:
    return HAT_STATUS_UP;

  case SDL_HAT_RIGHTUP:
    return HAT_STATUS_UP_RIGHT;

  case SDL_HAT_RIGHT:
    return HAT_STATUS_RIGHT;

  case SDL_HAT_RIGHTDOWN:
    return HAT_STATUS_DOWN_RIGHT;

  case SDL_HAT_DOWN:
    return HAT_STATUS_DOWN;

  case SDL_HAT_LEFTDOWN:
    return HAT_STATUS_DOWN_LEFT;

  case SDL_HAT_LEFT:
    return HAT_STATUS_LEFT;

  case SDL_HAT_LEFTUP:
    return HAT_STATUS_UP_LEFT;

  default:
    return HAT_STATUS_CENTER;
  }
}

u32 update_input(event_input_struct *event_input)
{
  SDL_Event event;

  event_input->config_button_action = CONFIG_BUTTON_NONE;
  event_input->key_action = KEY_ACTION_NONE;
  event_input->key_letter = 0;
  event_input->hat_status = HAT_STATUS_NONE;

  if (SDL_PollEvent(&event))
  {
    switch (event.type)
    {
    case SDL_QUIT:
      event_input->action_type = INPUT_ACTION_TYPE_PRESS;
      event_input->key_action = KEY_ACTION_QUIT;
      // Deliberate fallthrough

    case SDL_KEYDOWN:
      event_input->action_type = INPUT_ACTION_TYPE_PRESS;
      event_input->key_letter = event.key.keysym.unicode;
#ifdef RG350_BUILD
      event_input->config_button_action = key_map(event.key.keysym.sym);
#else
      switch (event.key.keysym.sym)
      {
#ifdef RS97_BUILD
      case SDLK_END:
#elif RG350_BUILD
      case SDLK_HOME:
#else
      case SDLK_ESCAPE:
#endif
        event_input->config_button_action = CONFIG_BUTTON_MENU;
        //event_input->key_action = KEY_ACTION_QUIT;
        break;

      case SDLK_1:
        event_input->key_action = KEY_ACTION_BG_OFF;
        break;

      case SDLK_2:
        event_input->key_action = KEY_ACTION_SPR_OFF;
        break;

      case SDLK_F1:
        event_input->key_action = KEY_ACTION_DEBUG_BREAK;
        break;

      case SDLK_t:
        event_input->key_action = KEY_ACTION_NETPLAY_TALK;
        break;

      case SDLK_BACKQUOTE:
        event_input->config_button_action = CONFIG_BUTTON_FAST_FORWARD;
        break;

      case SDLK_F5:
        event_input->config_button_action = CONFIG_BUTTON_SAVE_STATE;
        break;

      case SDLK_F7:
        event_input->config_button_action = CONFIG_BUTTON_LOAD_STATE;
        break;

      case SDLK_m:
        event_input->config_button_action = CONFIG_BUTTON_MENU;
        break;
      case SDLK_BACKSPACE:
        event_input->key_action = KEY_ACTION_NETPLAY_TALK_CURSOR_BACKSPACE;
        event_input->config_button_action = key_map(event.key.keysym.sym);
        break;

      case SDLK_RETURN:
        event_input->key_action = KEY_ACTION_NETPLAY_TALK_CURSOR_ENTER;
        event_input->config_button_action = key_map(event.key.keysym.sym);
        break;

      case SDLK_LEFT:
        event_input->key_action = KEY_ACTION_NETPLAY_TALK_CURSOR_LEFT;
        event_input->config_button_action = key_map(event.key.keysym.sym);
        break;

      case SDLK_RIGHT:
        event_input->key_action = KEY_ACTION_NETPLAY_TALK_CURSOR_RIGHT;
        event_input->config_button_action = key_map(event.key.keysym.sym);
        break;
      default:
        event_input->config_button_action = key_map(event.key.keysym.sym);
        break;
      }
#endif
      break;

    case SDL_KEYUP:
      event_input->action_type = INPUT_ACTION_TYPE_RELEASE;
      event_input->config_button_action = key_map(event.key.keysym.sym);
      break;

    case SDL_JOYBUTTONDOWN:
      //event_input->action_type = INPUT_ACTION_TYPE_PRESS;
      //event_input->config_button_action = joy_button_map(event.jbutton.button);
      break;

    case SDL_JOYBUTTONUP:
      //event_input->action_type = INPUT_ACTION_TYPE_RELEASE;
      //event_input->config_button_action = joy_button_map(event.jbutton.button);
      break;

    case SDL_JOYHATMOTION:
      event_input->hat_status = joy_hat_map(event.jhat.value);
      break;
    }
  }
  else
  {
    return 0;
  }

  return 1;
}

u8 gui_actions[16];

void clear_gui_actions()
{
  memset(gui_actions, 0, 16);
}

gui_action_type joy_map_gui_action(u32 button)
{
  switch (button)
  {
  case 1:
    return CURSOR_EXIT;
  case 2:
    return CURSOR_SELECT;
  case 0:
    return CURSOR_BACK;
  case 4:
    return CURSOR_PAGE_UP;
  case 5:
    return CURSOR_PAGE_DOWN;
  default:
    return CURSOR_NONE;
  }
}

gui_action_type joy_hat_map_gui_action(u32 hat_value)
{
  switch (hat_value)
  {
  case SDL_HAT_UP:
    return CURSOR_UP;

  case SDL_HAT_RIGHT:
    return CURSOR_RIGHT;

  case SDL_HAT_DOWN:
    return CURSOR_DOWN;

  case SDL_HAT_LEFT:
    return CURSOR_LEFT;

  case SDL_HAT_CENTERED:
    gui_actions[CURSOR_UP] = 0;
    gui_actions[CURSOR_DOWN] = 0;
    gui_actions[CURSOR_LEFT] = 0;
    gui_actions[CURSOR_RIGHT] = 0;
  default:
    return CURSOR_NONE;
  }
}

gui_action_type key_map_gui_action(u32 key)
{
  switch (key)
  {
  case SDLK_ESCAPE:
    return CURSOR_EXIT;

  case SDLK_DOWN:
    return CURSOR_DOWN;

  case SDLK_UP:
    return CURSOR_UP;

  case SDLK_LEFT:
    return CURSOR_LEFT;

  case SDLK_RIGHT:
    return CURSOR_RIGHT;

  case SDLK_RETURN:
  case SDLK_LCTRL:
    return CURSOR_SELECT;

  case SDLK_LALT:
    return CURSOR_BACK;

    /*case SDLK_PAGEUP:
      return CURSOR_PAGE_UP;

    case SDLK_PAGEDOWN:
      return CURSOR_PAGE_DOWN;*/
  }

  return CURSOR_NONE;
}

s32 udvalue = 0;
s32 lrvalue = 0;
u32 joy_axis_map_set_gui_action(u32 axis, s32 value)
{
  if ((axis & 1) && value != udvalue)
  {
    udvalue = value;
    if (value > kLIMIT)
    {
      gui_actions[CURSOR_UP] = 1;
      return CURSOR_UP;
    }
    else if (value < -kLIMIT)
    {
      gui_actions[CURSOR_DOWN] = 1;
      return CURSOR_DOWN;
    }
    else
    {
      gui_actions[CURSOR_UP] = 0;
      gui_actions[CURSOR_DOWN] = 0;
    }
  }
  else if (!(axis & 1) && value != lrvalue)
  {
    lrvalue = value;
    if (value > kLIMIT)
    {
      gui_actions[CURSOR_LEFT] = 1;
      return CURSOR_LEFT;
    }
    else if (value < -kLIMIT)
    {
      gui_actions[CURSOR_RIGHT] = 1;
      return CURSOR_RIGHT;
    }
    else
    {
      gui_actions[CURSOR_LEFT] = 0;
      gui_actions[CURSOR_RIGHT] = 0;
    }
  }
}

void get_gui_input(gui_input_struct *gui_input)
{
  SDL_Event event;
  gui_action_type gui_action = CURSOR_NONE;

  static u64 button_repeat_timestamp;
  static button_repeat_state_type button_repeat_state = BUTTON_NOT_HELD;
  static gui_action_type cursor_repeat = CURSOR_NONE;

  delay_us(100);

  while (SDL_PollEvent(&event))
  {
    switch (event.type)
    {
    case SDL_QUIT:
      quit();

    case SDL_KEYDOWN:
      gui_action = key_map_gui_action(event.key.keysym.sym);
      gui_actions[gui_action] = 1;

      if (gui_action == CURSOR_NONE)
      {
        gui_action = CURSOR_LETTER;
        gui_input->key_letter = event.key.keysym.unicode;
      }
      break;

    case SDL_KEYUP:
      gui_actions[key_map_gui_action(event.key.keysym.sym)] = 0;
      break;

    case SDL_JOYBUTTONDOWN:
      gui_action = joy_map_gui_action(event.jbutton.button);
      gui_actions[gui_action] = 1;
      break;

    case SDL_JOYBUTTONUP:
      gui_actions[joy_map_gui_action(event.jbutton.button)] = 0;
      break;

    case SDL_JOYAXISMOTION:
      if (event.jaxis.value != 0)
      {
        //joy_axis_map_set_gui_action(event.jaxis.axis, event.jaxis.value);
      }
      break;

    case SDL_JOYHATMOTION:
      gui_action = joy_hat_map_gui_action(event.jhat.value);
      if (gui_action != CURSOR_NONE)
      {
        gui_actions[gui_action] = 1;
      }
      break;
    }
  }

  if (gui_action != CURSOR_NONE)
  {
    get_ticks_us(&button_repeat_timestamp);
    button_repeat_state = BUTTON_HELD_INITIAL;
    cursor_repeat = gui_action;
  }
  else
  {
    if (gui_actions[cursor_repeat])
    {
      u64 new_ticks;
      get_ticks_us(&new_ticks);

      if (button_repeat_state == BUTTON_HELD_INITIAL)
      {
        if ((new_ticks - button_repeat_timestamp) >
            BUTTON_REPEAT_START)
        {
          gui_action = cursor_repeat;
          button_repeat_timestamp = new_ticks;
          button_repeat_state = BUTTON_HELD_REPEAT;
        }
      }

      if (button_repeat_state == BUTTON_HELD_REPEAT)
      {
        if ((new_ticks - button_repeat_timestamp) >
            BUTTON_REPEAT_CONTINUE)
        {
          gui_action = cursor_repeat;
          button_repeat_timestamp = new_ticks;
        }
      }
    }
  }

  gui_input->action_type = gui_action;
}

void initialize_event()
{
  u32 i;
  u32 joystick_count = SDL_NumJoysticks();
  printf("%d joysticks\n", joystick_count);

  if (joystick_count > 0)
  {
    for (i = 0; i < joystick_count; i++)
    {
      SDL_JoystickOpen(i);
    }
    SDL_JoystickEventState(SDL_ENABLE);
  }
}
