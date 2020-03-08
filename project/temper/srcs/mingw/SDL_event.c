#include "../common.h"
#include "SDL_event.h"

extern u32 nowDebugKey;

// analogしきい値-32767～32767まで
#define kLIMIT ((s16)0x4000)
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
		{eMODE_KEYSYM, SDLK_UP, CONFIG_BUTTON_UP},
		{eMODE_KEYSYM, SDLK_DOWN, CONFIG_BUTTON_DOWN},
		{eMODE_KEYSYM, SDLK_LEFT, CONFIG_BUTTON_LEFT},
		{eMODE_KEYSYM, SDLK_RIGHT, CONFIG_BUTTON_RIGHT},

		{eMODE_BUTTON, 9, 4},
		{eMODE_BUTTON, 8, 5},

		{eMODE_BUTTON, 0, 6},
		{eMODE_BUTTON, 3, 7},
		{eMODE_BUTTON, 1, 8},
		{eMODE_BUTTON, 2, 9},

		{eMODE_BUTTON, 4, 10},
		{eMODE_BUTTON, 6, 11},
		{eMODE_BUTTON, 7, 12},

		{eMODE_BUTTON, 5, 13},
		{eMODE_BUTTON, 7, 14},
		{eMODE_BUTTON, 11, 15},

		{eMODE_BUTTON, 12, 16},
		{eMODE_BUTTON, 13, 17},

		{eMODE_HAT, SDL_HAT_UP, CONFIG_BUTTON_UP},
		{eMODE_HAT, SDL_HAT_RIGHTUP, CONFIG_BUTTON_UP_RIGHT},
		{eMODE_HAT, SDL_HAT_RIGHT, CONFIG_BUTTON_RIGHT},
		{eMODE_HAT, SDL_HAT_RIGHTDOWN, CONFIG_BUTTON_DOWN_RIGHT},
		{eMODE_HAT, SDL_HAT_DOWN, CONFIG_BUTTON_DOWN},
		{eMODE_HAT, SDL_HAT_LEFTDOWN, CONFIG_BUTTON_DOWN_LEFT},
		{eMODE_HAT, SDL_HAT_LEFT, CONFIG_BUTTON_LEFT},
		{eMODE_HAT, SDL_HAT_LEFTUP, CONFIG_BUTTON_UP_LEFT},

		{eMODE_END, -1, -1},
};
#if 0
  // keyboardでのマッピング処理
	  switch (event.key.keysym.sym)
	    {
	    case SDLK_ESCAPE:
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
		  event_input->config_button_action = key_map(event.key.keysym.sym, &event_input->hard_key_index);
	      break;

	    case SDLK_RETURN:
	      event_input->key_action = KEY_ACTION_NETPLAY_TALK_CURSOR_ENTER;
		  event_input->config_button_action = key_map(event.key.keysym.sym, &event_input->hard_key_index);
	      break;

	    case SDLK_LEFT:
	      event_input->key_action = KEY_ACTION_NETPLAY_TALK_CURSOR_LEFT;
		  event_input->config_button_action = key_map(event.key.keysym.sym, &event_input->hard_key_index);
	      break;

	    case SDLK_RIGHT:
	      event_input->key_action = KEY_ACTION_NETPLAY_TALK_CURSOR_RIGHT;
		  event_input->config_button_action = key_map(event.key.keysym.sym, &event_input->hard_key_index);
	      break;
	    default:
		  event_input->config_button_action = key_map(event.key.keysym.sym, &event_input->hard_key_index);
	      break;
	    }
#endif

// return u32 : config_buttons_enumを返す
// inmode : チェックするキーのモード
// keys  : SDLが返してきているキーデータ
u32 key_search(eKeyMode inmode, u32 keys)
{
	unsigned char iI;
	tSDLtoConfigMap *sdl_to_config_map = SDLtoConfigMap;

	for (iI = 0; sdl_to_config_map[iI].mode != eMODE_END; iI++)
	{
		if (inmode == sdl_to_config_map[iI].mode && sdl_to_config_map[iI].sdl_key == keys)
		{
			if (inmode == eMODE_KEYSYM)
			{
				// keyboard 入力はwin32/linuxの場合はそのままconfig_dataを返す
#if !defined(RG350_BUILD)
				return sdl_to_config_map[iI].index;
#else
				return CONFIG_BUTTON_NONE;
#endif
			}
			else if (inmode == eMODE_BUTTON)
			{
				return ButtonMapData[config.pad[sdl_to_config_map[iI].index]].event_no;
			}
			else if (inmode == eMODE_HAT)
			{
				return sdl_to_config_map[iI].index;
			}
		}
	}
	return CONFIG_BUTTON_NONE;
}

void key_map(SDL_Event *event, event_input_struct *event_input)
{
	switch (event->type)
	{
	case SDL_KEYDOWN:
		event_input->action_type = INPUT_ACTION_TYPE_PRESS;
		event_input->key_letter = event->key.keysym.unicode;
		event_input->config_button_action = key_search(eMODE_KEYSYM, event->key.keysym.sym);
		break;

	case SDL_KEYUP:
		event_input->action_type = INPUT_ACTION_TYPE_RELEASE;
		event_input->key_letter = event->key.keysym.unicode;
		event_input->config_button_action = key_search(eMODE_KEYSYM, event->key.keysym.sym);
		break;

	case SDL_JOYBUTTONDOWN:
		event_input->action_type = INPUT_ACTION_TYPE_PRESS;
		event_input->key_letter = event->key.keysym.unicode;
		event_input->config_button_action = key_search(eMODE_BUTTON, event->jbutton.button);
		break;

	case SDL_JOYBUTTONUP:
		event_input->action_type = INPUT_ACTION_TYPE_RELEASE;
		event_input->key_letter = event->key.keysym.unicode;
		event_input->config_button_action = key_search(eMODE_BUTTON, event->jbutton.button);
		break;
	case SDL_JOYAXISMOTION:
		//status_message("now axis = %d which = %d",event->jaxis.axis,event->jaxis.which);
		if (!(event->jaxis.axis & 0x02))  // ここのbitが左右スティックの判定
		{
			u32 keydata = SDL_HAT_CENTERED;
			if ((event->jaxis.axis&0x01))
			{
				// 縦
				if (event->jaxis.value < -kLIMIT)
				{
					keydata = SDL_HAT_UP;
				}
				else if (event->jaxis.value > kLIMIT)
				{
					keydata = SDL_HAT_DOWN;
				}
			}
			else if (!(event->jaxis.axis&0x01))
			{
				// 横
				if (event->jaxis.value < -kLIMIT)
				{
					keydata = SDL_HAT_LEFT;
				}
				else if (event->jaxis.value > kLIMIT)
				{
					keydata = SDL_HAT_RIGHT;
				}
			}
			if (keydata != SDL_HAT_CENTERED)
			{
				event_input->action_type = INPUT_ACTION_TYPE_PRESS;
				event_input->config_button_action = key_search(eMODE_HAT, keydata);
			}
			else
			{
				// no input
			}
		}
		//status_message("id=%d data=%d", event.jaxis.axis, event.jaxis.value);
		break;
	case SDL_JOYHATMOTION:
		if (event->jhat.value != SDL_HAT_CENTERED)
		{
			event_input->action_type = INPUT_ACTION_TYPE_PRESS;
			event_input->key_letter = event->key.keysym.unicode;
			event_input->config_button_action = key_search(eMODE_HAT, event->jhat.value);
		}
		else
		{
			// no input
		}
		break;
	}
}

u32 update_input(event_input_struct *event_input)
{
	SDL_Event event;

	event_input->config_button_action = CONFIG_BUTTON_NONE;
	event_input->key_action = KEY_ACTION_NONE;
	event_input->key_letter = 0;

	if (SDL_PollEvent(&event))
	{
		switch (event.type)
		{
		case SDL_QUIT:
			event_input->action_type = INPUT_ACTION_TYPE_PRESS;
			event_input->key_action = KEY_ACTION_QUIT;
			// Deliberate fallthrough
		default:
			key_map(&event, event_input);
			break;
		}
	}
	else
	{
		return 0;
	}
	status_message("now input = %s",config_name_table[event_input->config_button_action]);

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

void get_gui_input(gui_input_struct *gui_input)
{
	u32 count_hat_input = 0;
	s32 udvalue = 0;
	s32 lrvalue = 0;

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
			nowDebugKey = event.jbutton.button;
			gui_action = joy_map_gui_action(event.jbutton.button);
			gui_actions[gui_action] = 1;
			break;

		case SDL_JOYBUTTONUP:
			gui_actions[joy_map_gui_action(event.jbutton.button)] = 0;
			break;

		case SDL_JOYAXISMOTION:
			//status_message("id=%d data=%d", event.jaxis.axis, event.jaxis.value);
			if (event.jaxis.axis <= 3)
			{
				//printf("a:%d v:%d\n", event.jaxis.axis, event.jaxis.value);
				if ((event.jaxis.axis & 1) || (event.jaxis.value != 0))
				{
					count_hat_input++;
					udvalue = event.jaxis.value;
				}
				else if (event.jaxis.value != 0)
				{
					count_hat_input++;
					lrvalue = event.jaxis.value;
				}
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

	if (count_hat_input != 0)
	{
		s32 len = (s32)(32767 * 32767 * 0.5);
		s32 ans = (abs(udvalue) * abs(udvalue)) + (abs(lrvalue) * abs(lrvalue));
		if (ans > len)
		{
			if (udvalue > 0)
			{
				gui_action = CURSOR_DOWN;
				gui_actions[gui_action] = 1;
			}
			else if (udvalue < 0)
			{
				gui_action = CURSOR_UP;
				gui_actions[gui_action] = 1;
			}

			if (lrvalue > 0)
			{
				gui_action = CURSOR_RIGHT;
				gui_actions[gui_action] = 1;
			}
			else if (lrvalue < 0)
			{
				gui_action = CURSOR_LEFT;
				gui_actions[gui_action] = 1;
			}
		}
		else
		{
			gui_actions[CURSOR_UP] = 0;
			gui_actions[CURSOR_DOWN] = 0;
			gui_actions[CURSOR_RIGHT] = 0;
			gui_actions[CURSOR_RIGHT] = 0;
			gui_action = CURSOR_NONE;
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

SDL_Joystick *joy[64];
void initialize_event()
{
	u32 i;
	u32 joystick_count = SDL_NumJoysticks();
	//printf("%d joysticks\n", joystick_count);

	if (joystick_count > 0)
	{
		for (i = 0; i < joystick_count; i++)
		{
			joy[i] = SDL_JoystickOpen(i);
		}
		SDL_JoystickEventState(SDL_ENABLE);
	}
}
