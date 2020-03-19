#include "../common.h"

static int AudioDeviceId;

/*
 * thread A
*/

void _sound_copy(audio_struct *callback_audio, u32 source_offset, u32 length, u32 shift,s16 *stream_base)
{
  u32 i;
  u32 _length = (length) / 2;
  s32 *source = callback_audio->buffer + source_offset;
  s32 current_sample;
  for(i = 0; i < _length; i++)
  {
    current_sample = source[i] >> shift;
    if(current_sample > 32767){
      current_sample = 32767;
    }
    else if(current_sample < -32768){
      current_sample = -32768;
    }
    stream_base[i] = current_sample;
    source[i] = 0;
  }
}

void sound_copy(audio_struct *callback_audio, u32 source_offset, u32 length, s16 *stream_base)
{
  if(config.sound_double)
  {
    _sound_copy(callback_audio,source_offset, length, 4, stream_base);
  }
  else
  {
    _sound_copy(callback_audio, source_offset, length, 5, stream_base);
  }
}

void audio_callback(void *userdata, Uint8 *stream, int length)
{
  audio_struct *callback_audio = (audio_struct *)userdata;
  u32 sample_length = length / 2;
  u32 _length;
  s16 *stream_base = (s16 *)stream;

  u32 check_buffersize = (callback_audio->buffer_index - callback_audio->buffer_base)%AUDIO_BUFFER_SIZE;

  if(config.enable_sound){
     if(check_buffersize >= length){
      if ((callback_audio->buffer_base + sample_length) >= AUDIO_BUFFER_SIZE)
      {
        // 今コピーすべきサイズ分サウンドができていない
        u32 partial_length = (AUDIO_BUFFER_SIZE - callback_audio->buffer_base) * 2;
        sound_copy(callback_audio, callback_audio->buffer_base, partial_length, stream_base);  // 出来てる分コピー
        sound_copy(callback_audio, 0, length - partial_length, stream_base);         // 出来てない分０クリア
        callback_audio->buffer_base = (length - partial_length) / 2;
      }
      else
      {
        // 今コピーすべきサイズ分サウンドが出来てる
        sound_copy(callback_audio, callback_audio->buffer_base, length, stream_base);
        callback_audio->buffer_base += sample_length;
      }
    }
  }
  else
  {
    // サウンド更新しないのでバッファポインターだけ更新して再生バッファは０で埋める
    if ((callback_audio->buffer_base + sample_length) >= AUDIO_BUFFER_SIZE)
    {
      u32 partial_length = (AUDIO_BUFFER_SIZE - callback_audio->buffer_base) * 2;
      callback_audio->buffer_base = (length - partial_length) / 2;
    }
    else
    {
      callback_audio->buffer_base += sample_length;
    }
    memset(stream, 0, length);
  }
}
/*
 * thread A 
*/

void initialize_audio(audio_struct *callback_audio)
{
  printf("initializing audio with frequency %d\n",
         config.audio_output_frequency);
/*
  switch (config.audio_output_frequency)
  {
  case 8000:
  case 11025:
    callback_audio->playback_buffer_size = 512;
    break;

  case 16000:
  case 22050:
    callback_audio->playback_buffer_size = 1024;
    break;

  case 44100:
    callback_audio->playback_buffer_size = 2048;
    break;

  default:
    callback_audio->playback_buffer_size = 4096;
    break;
  }
*/

  callback_audio->pause_state = 1;
  callback_audio->playback_buffer_size = 4096;
  //callback_audio->playback_buffer_size = 2048;
  //callback_audio->playback_buffer_size = 4096;
  //callback_audio->playback_buffer_size = 16384;
  const char *getname;
  int retcode;
  int i;
  int count = SDL_GetNumAudioDevices(0);
  SDL_AudioSpec desired_spec; // = { config.audio_output_frequency, AUDIO_S16SYS, 2, 0, callback_audio->playback_buffer_size / 4, 0, 0, audio_callback, NULL};
  SDL_AudioSpec audio_settings;

  for (i = 0; i < count; ++i)
  {
    SDL_Log("オーディオデバイス %d: %s", i, SDL_GetAudioDeviceName(i, 0));
  }
  if (count > 0)
  {
    SDL_memset(&desired_spec, 0, sizeof(desired_spec)); /* または SDL_zero(want); */
    desired_spec.freq = config.audio_output_frequency;
    desired_spec.format = AUDIO_S16SYS;
    desired_spec.channels = 2;
    desired_spec.samples = callback_audio->playback_buffer_size / 4;  // /4なのは　サイズ / sizeof(s16) / stereoということかな？
    desired_spec.callback = audio_callback; /* この関数はどこか別の場所に書く. 詳細はSDL_AudioSpecを参照すること */
    desired_spec.userdata = callback_audio;         // ここで共通用のデータを受け渡すのに使うようだ

    AudioDeviceId = SDL_OpenAudioDevice(
        NULL, // ここをNULLにすると最適なデバイスを使用してくれる
        0,
        &desired_spec, &audio_settings,
        SDL_AUDIO_ALLOW_ANY_CHANGE);
    if (AudioDeviceId == 0)
    {
      printf("!!!! not create SDL Audio abort.\n error message:%s\n", SDL_GetError());
    }
    else{
      SDL_Log("Open device no = %d",AudioDeviceId);
      callback_audio->output_frequency = audio_settings.freq;
    }
  }
}

void audio_lock(){
  SDL_LockAudioDevice(AudioDeviceId);
}
void audio_unlock(){
  SDL_UnlockAudioDevice(AudioDeviceId);
}

void audio_exit(audio_struct *callback_audio)
{
  callback_audio->buffer_index = AUDIO_BUFFER_SIZE - 1;
  callback_audio->buffer_base = 0;
  SDL_CloseAudioDevice(AudioDeviceId);
}

u32 audio_pause(audio_struct *callback_audio)
{
  u32 current_audio_pause = callback_audio->pause_state;

  if (current_audio_pause == 0)
  {
    switch (SDL_GetAudioStatus())
    {
    case SDL_AUDIO_STOPPED:
      printf("停止中\n");
      break;
    case SDL_AUDIO_PLAYING:
      printf("再生中\n");
      SDL_PauseAudioDevice(AudioDeviceId,1);
      callback_audio->pause_state = 1;
      break;
    case SDL_AUDIO_PAUSED:
      printf("一時停止中\n");
      break;
    default:
      printf("???");
      break;
    }
  }
  return current_audio_pause;
}

void audio_unpause(audio_struct *callback_audio)
{
  if (callback_audio->pause_state)
  {
    callback_audio->pause_state = 0;
    switch (SDL_GetAudioStatus())
    {
    case SDL_AUDIO_STOPPED:
      printf("停止中\n");
      SDL_PauseAudioDevice(AudioDeviceId,0);
      break;
    case SDL_AUDIO_PLAYING:
      printf("再生中\n");
      callback_audio->pause_state = 1;
      break;
    case SDL_AUDIO_PAUSED:
      printf("一時停止中\n");
      break;
    default:
      printf("???");
      break;
    }
  }
}
