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
short 炮_近端_计算最理想可移动步数(short *单个坐标数组, const char *移动方向)
{
	if (strstr(移动方向, "进"))
		return 单个坐标数组[1];
	if (strstr(移动方向, "退"))
		return HEIGHT - 1 - 单个坐标数组[1];	
	if (strstr(移动方向, "平左"))
		return 单个坐标数组[0];
	if (strstr(移动方向, "平右"))
		return WIDTH - 1 - 单个坐标数组[0];
		
	return 0;
}

short 炮_近端_可移动步数缩小(char *chessBoard, short *选到的棋子的坐标数组, const char *移动方向, short 最理想可移动步数)
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
		《遇任何棋子：踩到任何棋子上》
		此时可移动步数已计算完成，且量刚好足够。
		因为下一步是棋，炮不可吃任何中间棋。
		*/		
		// to_index<0：超出尽头时
		// !棋位内容是哪种情况：遇己
		if (to_index<0 || 棋位内容是哪种情况 != -1)
			break;
			
		可移动步数++;
	} while (可移动步数<最理想可移动步数);
	
	return 可移动步数;
}

short 炮_近端_获取可落点索引之单点(char *chessBoard, short *选到的棋子的坐标数组, const char *移动方向, short 本次移动步数)
{
	short from_x=选到的棋子的坐标数组[0];
	short from_y=选到的棋子的坐标数组[1];
	short to_x=from_x,to_y=from_y, to_index;

	if (strstr(移动方向, "进"))
		to_y-=本次移动步数;
	else if (strstr(移动方向, "退"))
		to_y+=本次移动步数;
	else if (strstr(移动方向, "平左"))
		to_x-=本次移动步数;
	else if (strstr(移动方向, "平右"))
		to_x+=本次移动步数;
	
	to_index = 坐标转索引(to_x, to_y);
	
	return to_index;
}

/*
从近端可移动步数最大值到达的落点开始找。
远端点位必须是敌棋，才可落点。

在从远端起点出发往当前方向前进的路上，
当第一次遇到己方棋，
这时己方棋将更往前的路阻挡了，
说明远端已经无落点。

当第一次遇到敌棋，
这时说明可以踩到敌棋上，
且说明远端的的可落点已经计算完毕。
因为远端的可落点最少有0个，最多只有1个。


所以如果判断棋位内容（只判断第一个遇到的棋）：
如果chessBoard[to_index]为敌棋，
则to_index就是远端可落点，并且结束远端可落点计算


如果为己方棋，
则远端无可落点



这是判断棋位内容情况的方法。
还有一种方法，是判断索引的方法。

已知当前应对方的棋子的索引数组。
于是，不用在当前移动方向上一步步移动去检查点位是否可落。
而是，直接根据同方向的索引变化规律，计算出剩余索引。
然后，按顺序（从起始检查点的近端到远端）判断剩余索引是否在当前应对方的棋子的索引数组里。

对于横5纵6尺寸的棋盘：
进方向索引变化规律=起点索引-5（退方向+5）
平左方向=起点索引-1（平右方向+1）

但这种方法需要函数接收结构体指针Game*参数。

当然，我们可以对这种方法折中。
我们用索引变化规律计算出索引，再自行用chessBoard[索引]判断内容。
*/
// 炮的远端落点要么0个，要么是唯一的。所以不需要名称起为“...之单点"。


bool 该直线移动方向是索引减小的吗(const char *移动方向)
{
	return strstr(移动方向, "进") || strstr(移动方向, "平左");
}

bool 该直线移动方向是纵坐标变化的吗(const char *移动方向)
{
	return strstr(移动方向, "进") || strstr(移动方向, "退");
}

void assign_by_direction(short *var, short increment, const char *移动方向)
{
	if (该直线移动方向是索引减小的吗(移动方向))
	{
		*var -= increment;
	}
	else
	{
		*var += increment;
	}
}

/*
从近端终点为起点前进检查得遇到两次棋子。

第一次遇到。

第二次继续检查，必须为敌棋。

近端终点在边界或边界-1（即与边界距离0~1），则无远端可言，故而必无远端落点。


炮的近端终点的下一点只要不是棋盘外，必定是棋子。
*/

bool 判断棋位与边界距离是否在某个范围内(short pos_x, short pos_y, const char *移动方向, short farthest)
{
	short 单个坐标数组[2] = { pos_x, pos_y };
	return 炮_近端_计算最理想可移动步数(单个坐标数组, 移动方向) <= farthest;
}

short 炮_远端_获取可落点索引之唯一点(char *chessBoard, short *选到的棋子的坐标数组, const char *移动方向, short 近端可移动步数)
{
	short from_x=选到的棋子的坐标数组[0];
	short from_y=选到的棋子的坐标数组[1];
	short to_x=from_x, to_y=from_y, to_index;
	
	// 将检查起点根据当前移动方向移至近端终点
	// 以该方向上近端的最终落点作为远端检查起点
	printf("当前移动方向：%s 近端检查起点：%d %d\n", 移动方向, from_y, from_x);
	assign_by_direction(该直线移动方向是纵坐标变化的吗(移动方向)? &from_y: &from_x, 近端可移动步数, 移动方向);
	printf("当前移动方向：%s 远端检查起点：%d %d\n", 移动方向, from_y, from_x);
	
	// 近端终点与边界距离1以内则绝无远端落点
	if (判断棋位与边界距离是否在某个范围内(from_x, from_y, 移动方向, 1))
	{
		return -1;
	}
	
	// 可能存在远端落点。获取近端终点索引。
	short 近端终点索引 = 坐标转索引(from_x, from_y);		
	// 进退不变
	to_x=from_x;
	// 平左平右不变
	to_y=from_y;
	puts("⚡️第一轮检查");
	do{
		printf("未检查时to_y:%d to_x:%d\n",to_y, to_x);
		assign_by_direction(该直线移动方向是纵坐标变化的吗(移动方向)? &to_y: &to_x, 1, 移动方向);
		to_index = 坐标转索引(to_x, to_y);
		printf("检查到to_y:%d to_x:%d index:%d\n",to_y, to_x, to_index);
	// 棋盘内及检查棋位为空时才继续
	}while ( to_index != -1 && 判断该棋位内容情况(chessBoard[to_index]) == -1 );
	
	
	/*
	从检查起点走一步遇到的必定是棋盘外或有棋子
	所以下一步一定不为空，所以第一次远端检查只走了一步就结束
	现在检查到两种情况：
	一、棋盘外
	二、有棋子
	
	棋盘外：结束检查。无远端落点。
	有棋子（棋盘内索引）：继续检查。
	
	*/
	if (to_index == -1) return -1;

	/*
	第二次检查
	三种情况：
	一、空
	二、棋盘外
	三、有棋子
	
	空：继续检查，直到后两种情况为止。
	棋盘外：结束检查。无远端落点。
	有棋子：结束检查。分己敌。
	
	己：不可踩。无远端落点。返回棋盘外索引-1。
	敌：可踩。有且只有唯一远端落点。返回检查到的点位to_index。
	
	*/
	puts("✅第一轮检查结果：在棋盘内，遇到棋子");
	puts("⚡️第二轮检查");
	do{
		printf("未检查时to_y:%d to_x:%d\n",to_y, to_x);
		assign_by_direction(该直线移动方向是纵坐标变化的吗(移动方向)? &to_y: &to_x, 1, 移动方向);
		to_index = 坐标转索引(to_x, to_y);
		printf("检查到to_y:%d to_x:%d index:%d\n",to_y, to_x, to_index);
	// 棋盘内及检查棋位为空时才继续
	}while ( to_index != -1 && 判断该棋位内容情况(chessBoard[to_index]) == -1 );
		
	/*
	检查结束，已超出棋盘外：无可落点。
	检查结束，仍然在棋盘内，检查到的且棋位内容非空：己或敌。
	0己：结束远端计算。远端无落点。
	1敌：结束远端计算。远端有且只有唯一落点。就是to_index踩在敌棋上。
	可见三种情况中有两种情况无可落点。
	只有遇己的情况才需要控制return的to_index。
	避免把“踩己棋”的index作为可落点。
	*/
	if (chessBoard[to_index] == false )
		to_index == -1;	

	return to_index;
}


short 炮的可活动范围缩小及准备移动到的随机落点(char *chessBoard, short *选到的棋子的坐标数组)
{
	short 可移动步数数组[4];
	const char *移动方向数组[4] = {"进", "退", "平左", "平右"};
	short to_index;
	short *可落点索引数组 = malloc ( sizeof (short ) * (WIDTH-1+HEIGHT-1) );
	short 可落点数量 = 0;
	
	// 最理想可选移动方向及可移动步数
	for (short i=0; i<4; i++)
	{
		可移动步数数组[i] = 炮_近端_计算最理想可移动步数(选到的棋子的坐标数组, 移动方向数组[i]);
	}
	//putchar(10);
	
	// 排除移动方向及缩小移动步数
	for (short i=0; i<4; i++)
	{
		if (可移动步数数组[i])
		{
			可移动步数数组[i] = 炮_近端_可移动步数缩小(chessBoard, 选到的棋子的坐标数组, 移动方向数组[i], 可移动步数数组[i] );
	
		}
		//printf ("可%s%d步\n", 移动方向数组[i], 可移动步数数组[i]);
	}
	//putchar(10);
	
	

	// 选取索引法
	// 先选取炮的近端（与车类似，只是车能吃近端敌子）
	for (short i=0, *p = 可落点索引数组; i<4; i++)
	{
		if (可移动步数数组[i])
		{					
			for ( short 本次移动步数=1; 本次移动步数<=可移动步数数组[i]; 本次移动步数++)
			{
				to_index = 炮_近端_获取可落点索引之单点(chessBoard, 选到的棋子的坐标数组, 移动方向数组[i], 本次移动步数);
				printf("%s%d步得近端索引%d\n", 移动方向数组[i], 本次移动步数, to_index);
				*(p++)=to_index;
				可落点数量++;
			}
		}
	}
	
	// 再选取炮的远端唯一落点
	for (short i=0, *p = 可落点索引数组+可落点数量; i<4; i++)
	{
		to_index = 炮_远端_获取可落点索引之唯一点(chessBoard, 选到的棋子的坐标数组, 移动方向数组[i], 可移动步数数组[i]);
		printf("%s得远端索引%d\n", 移动方向数组[i], to_index);
		if (to_index != -1)
		{
			*(p++)=to_index;
			可落点数量++;
		}
	}
	
	if (可落点数量==0)
	{
		free(可落点索引数组);
		return -1;
	}
	short 选到的落点索引 = 可落点索引数组[ rand()%可落点数量 ];

	printf("炮打算落在%d\n", 选到的落点索引);
	
	free(可落点索引数组);
	return 选到的落点索引;
}