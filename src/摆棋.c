#include "../include/Chess_Operate.h"
void 摆棋(char *chessBoard, short (*将要放置的多个棋子的坐标二维数组)[2], short 坐标数量, const char *将要放置的多个棋子的对应内容数组)
{
	short index;

	for (short i = 0; i < 坐标数量; i++)
	{
		index = 坐标转索引(将要放置的多个棋子的坐标二维数组[i][0], 将要放置的多个棋子的坐标二维数组[i][1]);
		//chessBoard[*ptr_index] = (char)('A' + i);
		chessBoard[index] = 将要放置的多个棋子的对应内容数组[i];
	}
}