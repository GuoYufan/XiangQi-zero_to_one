void 倒转(char *chessBoard, short 棋子数量, short *棋子索引数组, short *倒转后的棋子索引数组)
{
	char *ptr_chsBd = chessBoard;
	short *ptr_index_source = 棋子索引数组;
	short *ptr_index_target = 倒转后的棋子索引数组;

	char temp;
	
	for (short i = 0; i < 棋子数量;
		 i++, ptr_index_source++, ptr_index_target++)
	{
		// printf("(%d -> %d)\n", *ptr_index_source, *ptr_index_target);
		temp = ptr_chsBd[*ptr_index_target];

		ptr_chsBd[*ptr_index_target] = ptr_chsBd[*ptr_index_source];
		ptr_chsBd[*ptr_index_source] = temp;
	}
}