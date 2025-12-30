# XiangQi_zero-to-one
中国象棋从零开始

## 📖使用方法
**一、项目目录下的`<include>`目录下的`<config.h>`文件中设置棋盘尺寸（宽度和高度）。**

**二、项目目录下的`<src>`目录下的`<main.c>`开头全局变量结构体初始化函数内设置debug模式**

```
GYF_Debug_Mode *gyf_debug_mode = NULL;

/*《调试模式设置》
GYF_Debug_Mode->DoesMsgPrint：是否进行debug信息输出。
GYF_Debug_Mode->DoesTest：是否进行特定情况测试。（例如强制固定一个值，观察变化。）
*/

void GYF_Debug_Mode_init(GYF_Debug_Mode *self)
{	
	self->DoesMsgPrint=false;
	
	self->DoesTest=false;
	
	// 固定落棋范围：用坐标控制
	self->固定落棋范围 = 0;
}

```

**三、这个全局变量结构体的初始化会在`GYF_Debug_Mode_init`函数内进行。所以debug模式的相关设置在这个函数内。**

设置为：
> self->DoesMsgPrint=true;
> self->DoesTest=false;

**表示开启debug信息输出，关闭测试**

> 前者false,后者true

**表示关闭dedug信息输出，开启测试**

> 前者true, 后者true

**表示debug模式全开**

> 前者false, 后者false

**表示debug模式全关**

## 📖目前测试是
正常选棋，棋子索引正常。
但固定坐标为0，因为可落点计算全部都是坐标计算出来的，与索引无关。
所以让任何位置的棋子全部往第1行、第1列落子。
从而容易出现吃子。达到测试吃子的需求。

## 📖目前支持情况
### 车、马、炮的可落点计算
