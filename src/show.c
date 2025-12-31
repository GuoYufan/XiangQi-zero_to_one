#include "../include/config.h"
#include <stdio.h>
#include <ctype.h>

void ColorCode_init(ColorCode* self)
{
	self->red = "\033[31;1;7m";
	self->black = "\033[37;40m";
	self->reset = "\033[0m";
}

void show_棋盘(char* chessBoard)
{
	char *ptr_chsBd = chessBoard;
	for (short y = 0; y < HEIGHT; y++)
	{
		if (y == HEIGHT / 2)
		{
			if (WIDTH == 9 && HEIGHT == 10)
				printf("%8s\t%s\n", "楚河", "汉界");
			else
				puts("楚河\t汉界");
		}
		for (short x = 0; x < WIDTH; x++, ptr_chsBd++)
		{
			char c = *ptr_chsBd;
			if (c != 'o')
			{
				printf("%s", isupper(c) ? color->black : color->red);
				putchar(c);
				printf("%s", color->reset);
			}
			else
				putchar(c);
			if (x < WIDTH - 1)
				putchar('-');
		}
		putchar(10);
	}
}