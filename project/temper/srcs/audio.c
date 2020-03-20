#include "common.h"

volatile audio_struct audio;

extern void audio_signal_callback();
extern void audio_wait_callback();

void audio_sync_start()
{
  audio_signal_callback();
  audio_lock();
  audio_wait_callback();
}

void audio_sync_end()
{
  audio_signal_callback();
  audio_unlock();
}

/*
 * エミュレーション開始時に呼び出しているバッファ初期化
*/
void audio_unstall_callback(audio_struct *callback_audio)
{
  callback_audio->buffer_index = AUDIO_BUFFER_SIZE - 1;
  callback_audio->buffer_base = 0;
  audio_signal_callback(callback_audio);
}

void audio_reset_buffer(audio_struct *callback_audio)
{
  callback_audio->buffer_index = 0;
  callback_audio->buffer_base = 0;
  audio_signal_callback(callback_audio);
}

void audio_revert_pause_state(audio_struct *callback_audio, u32 pause_state)
{
  if(pause_state == 0){
    audio_unpause(callback_audio);
  }
}

