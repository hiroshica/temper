***
## 確定要素
上下左右のキーコンフィグはしない(できない）とする  

config.pad(rapid_frame)の配列の並び = PCE_control_namesの並びと一致  
(config_buttons_enumのボタン入力定義部分と一致せず、上下左右を削った分がずれる))  

config.padの中身       = ButtonMapDataの並びと一致するので必要なデータは  
ButtonMapData構造体を拡張する

***
## メモ  

-RG350表  

|入力|キーコード|入力|キーコード|入力|キーコード|入力|キーコード|  
|:--:|:--:|:--:|:--:|:--:|:--:|:--:|:--:|  
|↑|SDLK_UP|↓|SDLK_DOWN|←|SDLK_LEFT|→|SDLK_RIGHT|
|A|SDLK_LCTRL|B|SDLK_LALT|X|SDLK_SPACE|Y|SDLK_LSHIFT|
|L1|SDLK_TAB|L2|SDLK_PAGEUP|L3|SDLK_KP_DIVIDE|  
|R1|SDLK_BACKSPACE|R2|SDLK_PAGEDOWN|R3|SDLK_KP_PERIOD|  
|SELECT|SDLK_ESCAPE|START|SDLK_RETURN|POWER|SDLK_HOME|  


***
## 入力周りの変更 ToDo:

***
