// config.h
   #ifndef CONFIG_H
   #define CONFIG_H

   #define WIDTH 5   // 棋盘宽度
   #define HEIGHT 6 // 棋盘高度

   #endif

#include <stdlib.h>
#include <stdbool.h>
typedef struct 颜色代码 ColorCode;
struct 颜色代码
{
	char *red, *black;
	char *reset;
};

typedef struct 调试模式 GYF_Debug_Mode;
struct 调试模式
{
	bool DoesMsgPrint;
	bool DoesTest;
	short 固定落棋范围;
	const char *固定选棋范围;
};

extern ColorCode *color;
extern short current_player;
extern short 第几回合;
extern GYF_Debug_Mode *gyf_debug_mode;

void ColorCode_init(ColorCode *self);