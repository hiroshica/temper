#include "common.h"

volatile audio_struct audio;

/*
 * エミュレーション開始時に呼び出しているバッファ初期化
*/
void audio_unstall_callback(audio_struct *callback_audio)
{
  callback_audio->buffer_index = AUDIO_BUFFER_SIZE - 1;
  callback_audio->buffer_base = 0;
}

void audio_reset_buffer(audio_struct *callback_audio)
{
  callback_audio->buffer_index = 0;
  callback_audio->buffer_base = 0;
}

void audio_revert_pause_state(audio_struct *callback_audio, u32 pause_state)
{
  if(pause_state == 0){
    audio_unpause(callback_audio);
  }
}

