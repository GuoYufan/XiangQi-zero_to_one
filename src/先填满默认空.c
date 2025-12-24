#include "../include/config.h"
#include <stdio.h>

void 先填满默认空(char *chessBoard)
{
	char *ptr_chsBd = chessBoard;

	for (short i = 0; i < WIDTH * HEIGHT; i++, ptr_chsBd++)
	{
		*ptr_chsBd = 'o';
	}
}