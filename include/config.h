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

extern ColorCode *color;
extern short current_player;
extern short 第几回合;
extern bool GYF_Debug_Mode[2];

void ColorCode_init(ColorCode *self);