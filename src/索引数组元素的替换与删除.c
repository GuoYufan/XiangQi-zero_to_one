void replace_num(short *container, short old_item, short new_item)
{
	short *p=container;
	
	for (;;p++)
	{
		if (*p == old_item)
		{
			*p = new_item;
			return;
		}
	}	
}


short remove_num(short *container, short item, short *size)
{
	/*
	0~9 -> 10次
	0~5 -> 6次
	6   7 8 9
	==
	3次：i=6 i=7 i=8
	
	*/
	short *p=container;

	for (short i=0;i < *size;i++,p++)
	{
		if (*p == item)
		{
			// 记录截断点索引
			short breakPoint = i;
			while (i+1 < *size)
			{
				*p++ = *p;
				
				/*
				等价于：
				左边*p保持（已计算，不受p++影响）
				左边p++
				右边*p
				=
				所以*(p+1)赋值给*p
				*/
				
				/*
				*p=*p++;
				错误等价于：
				左边*p
				右边*p
				...（我也不懂，无法解读）
				反正结果是把本来要删除的元素不仅存在，而且无限往后覆盖为与之相同
				*/
				
				/*		
				//*(p++)=*(p+1);
				这样符合先完成赋值再自增的直觉，但会出问题。
				连续两个元素被覆盖。
				*/
				
				/*
				//*p = *(p+1);
				//p++;
				这样不会出问题。
				但需要写两行。
				*/
				
				/*
				也可以在右边+1的同时不发生连续两个元素被覆盖。
				但多跨越了一个元素。
				//*++p=*(p+1);
				*/
				
				i++;

			}
			*p = -1;
			(*size) --;
			return breakPoint;
		}
	}
	
	// 返回无索引表示未找到
	return -1;
}