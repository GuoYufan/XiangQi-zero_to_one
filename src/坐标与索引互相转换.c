#include <stdbool.h>
#include "../include/config.h"

bool 是否有效索引(short index)
{
	if (index<0 || index > WIDTH * HEIGHT - 1)
	{
		return false;
	}
	
	return true;
}

/* (2,1) -> 5
1行3个 +2 */
short 坐标转索引(short pos_x, short pos_y)
{
	if (! (pos_x < WIDTH) || pos_x < 0)
	{
		return -1;
	}
	else if (! (pos_y < HEIGHT) || pos_y < 0)
	{
		return -1;
	}
	return pos_y * WIDTH + pos_x;
}


/* 索引转坐标的方式是除以棋盘宽度得到商和余数。
   商是纵坐标，余数是横坐标。 */
bool 索引转坐标(short index, short *单个坐标数组)
{
	if (!是否有效索引(index))
		return false;
	
	short pos_x, pos_y;

	pos_y = index / WIDTH;
	pos_x = index % WIDTH;

	单个坐标数组[0] = pos_x;
	单个坐标数组[1] = pos_y;
	
	return true;
}