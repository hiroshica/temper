# サウンド関連

## メモ 解析結果  

audio_struct         = エミュレータとサウンド再生側との通信用構造体。内訳は以下  
buffer               = wave dataっが書き込まれるバッファ sint32ステレオデータが書き込まれる。サイズはAUDIO_BUFFER_SIZEだけある。  
buffer_index         = PSGがアップデートされるたびに進む書き込みカウンタ。 AUDIO_BUFFER_SIZEでラップされる。  
buffer_base          = SDL_Audioのコールバックで更新されたときに更新される  
output_frequency     = 出力周波数。  
playback_buffer_size = 再生ハード側(sdl)の出力バッファサイズ  
pause_state          = メニューに行ったりする際のポーズステート 1:pauseらしい

***

## サウンド周りのToDo  

***
