#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include <stdbool.h>
#define DEBUG printf("---debug位置---\n行号:%d\n文件名:<%s>",__LINE__,__FILE__);getchar();

#include "../include/config.h"
#include "../include/Chess_Operate.h"

/*
进 退 平左 平右
*/
/*
《退无可退》
index 10 -> (1,3)
纵坐标到底了，退无可退。
最大纵坐标 = HEIGHT - 1
可进步数 = 纵坐标
可退步数 = 最大纵坐标 - 纵坐标

最大横坐标 = WIDTH - 1
可平左步数 = 横坐标
可平右步数 = 最大横坐标 - 横坐标
*/
short 马_近端_计算最理想可移动步数(short *单个坐标数组, char *移动方向)
{
	if (strstr(移动方向, "退"))
		return HEIGHT - 1 - 单个坐标数组[1]>1?1:0;
	
	else if (strstr(移动方向, "进"))
		return 单个坐标数组[1]>1?1:0;
	
	else if (strstr(移动方向, "平左"))
		return 单个坐标数组[0]>1?1:0;
		
	else if (strstr(移动方向, "平右"))
		return WIDTH - 1 - 单个坐标数组[0]>1?1:0;
		
	return 0;
}

short 马_近端_可移动步数缩小(char *chessBoard, short *选到的棋子的坐标数组, char *移动方向, short 最理想可移动步数)
{
	short 可移动步数 = 0;
	short from_x=选到的棋子的坐标数组[0];
	short from_y=选到的棋子的坐标数组[1];
	short to_x=from_x,to_y=from_y, to_index;
	
	do
	{
		// 迈一步检查
		if (strstr(移动方向, "进"))
			to_y--;
		else if (strstr(移动方向, "退"))
			to_y++;
		else if (strstr(移动方向, "平左"))
			to_x--;
		else if (strstr(移动方向, "平右"))
			to_x++;
		to_index = 坐标转索引(to_x, to_y);
		
		if (gyf_debug_mode->DoesMsgPrint) printf("x%d,y%d,to%d", to_x, to_y, to_index);

		//printf("%d,%c\n",to_index, chessBoard[to_index]);
		if (gyf_debug_mode->DoesMsgPrint) printf("进入判断，移动方向:%s，可移动步数:%d\n",移动方向, 可移动步数);


		short 棋位内容是哪种情况= 判断该棋位内容情况(chessBoard[to_index]);

		/*
		《任何时候：超出尽头时/走到棋盘外时》
		此时可移动步数已计算完成，且量刚好足够。
		因为下一步是棋盘外，不可抵达。
		
		用于检测下个点的那一步（未更改可移动步数），
		只是加到了to_x或to_y里，
		然后转成to_index去检测。
		检测用的是to_index，未影响到可移动步数。
		只是在检测把情况判断好之后，再去决定可移动步数是否变化。
		*/
		
		/*
		《遇己：踩到己方棋子上》
		此时可移动步数已计算完成，且量刚好足够。
		因为下一步是己棋，不可吃。
		*/		
		// to_index<0：超出尽头时
		// !棋位内容是哪种情况：遇己
		if (to_index<0 || !棋位内容是哪种情况)
			break;

		/*
		《或遇敌：踩到敌棋时（吃子）》
		此时可移动步数已计算完成。
		但用于检测这一步是踩在敌棋头上的，必须影响可移动步数。
		所以要把这一步加到可移动步数里。
		因为下一步是敌棋，可吃。		
		*/
		else if ( 棋位内容是哪种情况 == true )
		{
			break;
		}
		
		可移动步数++;
	} while (可移动步数<最理想可移动步数);
	
	return 可移动步数;
}

short 马_远端_获取可落点索引之单点(char *chessBoard, short *选到的棋子的坐标数组, char *移动方向, short 哪边)
{
	short from_x=选到的棋子的坐标数组[0];
	short from_y=选到的棋子的坐标数组[1];
	short to_x=from_x,to_y=from_y, to_index;

	if (strstr(移动方向, "进"))
		to_y-=2;
	else if (strstr(移动方向, "退"))
		to_y+=2;
	else if (strstr(移动方向, "平左"))
		to_x-=2;
	else if (strstr(移动方向, "平右"))
		to_x+=2;
	
	if (strstr(移动方向, "平"))
		哪边? to_y--:to_y++;
	else
		哪边? to_x--:to_x++;
	
	to_index = 坐标转索引(to_x, to_y);
	
	if (!是否有效索引(to_index)) return -1;
	return 判断该棋位内容情况(chessBoard[to_index])?to_index:-1;
}


short 马的可活动范围缩小及准备移动到的随机落点(char *chessBoard, short *选到的棋子的坐标数组)
{
	short 可移动步数数组[4];
	char *移动方向数组[4] = {"进", "退", "平左", "平右"};
	short to_index;
	short *可落点索引数组 = malloc ( sizeof (short ) * 4 * 2 );
	short 可落点数量 = 0;
	
	// 最理想可选移动方向及可移动步数
	for (short i=0; i<4; i++)
	{
		可移动步数数组[i] = 马_近端_计算最理想可移动步数(选到的棋子的坐标数组, 移动方向数组[i]);
	}
	//putchar(10);
	
	// 排除移动方向及缩小移动步数
	for (short i=0; i<4; i++)
	{
		if (可移动步数数组[i])
		{
			可移动步数数组[i] = 马_近端_可移动步数缩小(chessBoard, 选到的棋子的坐标数组, 移动方向数组[i], 可移动步数数组[i] );
	
		}
		//printf ("可%s%d步\n", 移动方向数组[i], 可移动步数数组[i]);
	}
	//putchar(10);
	
	

	// 选取索引法
	for (short i=0, *p = 可落点索引数组; i<4; i++)
	{
		if (可移动步数数组[i])
		{					
			for ( short 哪边=0; 哪边<2; 哪边++)
			{
				to_index = 马_远端_获取可落点索引之单点(chessBoard, 选到的棋子的坐标数组, 移动方向数组[i], 哪边);
				printf("%s2步且%s1步得索引%d\n", 移动方向数组[i], 哪边?(i<2?"平左":"进"):(i<2?"平右":"退"), to_index);
				if (to_index!=-1)
				{
					*(p++)=to_index;
					可落点数量++;
				}
			}
		}
	}
	
	if (可落点数量==0)
	{
		free(可落点索引数组);
		return -1;
	}
	short 选到的落点索引 = 可落点索引数组[ rand()%可落点数量 ];

	printf("马打算落在%d\n", 选到的落点索引);
	
	free(可落点索引数组);
	return 选到的落点索引;
}