#include "../include/config.h"
#include "../include/Chess_Operate.h"
#include <ctype.h>

void Game_更新全场棋子的索引数组(Game *game)
{
	char *ptr_chsBd = game->chessBoard;
	short *ptr_index_all = game->全场棋子的索引数组;
	short *ptr_index_black = game->黑棋索引数组;	
	short *ptr_index_red = game->红棋索引数组;
	
	for (short i = 0; *ptr_chsBd != '\0'; ptr_chsBd++, i++)
	{
		if (*ptr_chsBd != 'o')
		{
			*ptr_index_all = i;
			ptr_index_all++;
			game->全场棋子数量++;
			
			char piece = *ptr_chsBd;
			if(isupper(*ptr_chsBd))
			{
				*ptr_index_black = i;
				ptr_index_black++;
				game->黑棋数量++;
			}
			else
			{
				*ptr_index_red = i;
				ptr_index_red++;
				game->红棋数量++;

			}
		}
	}
}