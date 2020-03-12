#ifndef __SETUP_H__
#define __SETUP_H__

#include "common_deftypes.h"
#include "common_defines.h"
#include"main.h"
#include"event.h"

#define k_INDEX_NONE         (0xffffffff)   // data終了
#define k_INDEX_EFFECTIVE    (0x00010000)   // data有効
#define k_INDEX_MASK         (0x0000ffff)   // data取り出し用マスク
typedef struct _tButtonMapData
{
  char *mName;
  u32  mIndex;
} tButtonMapData;
extern tButtonMapData ButtonMapData[PAD_STOCK_MAX];


extern const char *control_config_exit_string;
extern const char *control_config_string;
extern const u32 control_config_start_column;
//extern const u32 platform_control_count;
//extern char *platform_control_names[MAX_CONTROLS];


#endif
