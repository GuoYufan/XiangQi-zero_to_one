# XiangQi_zero-to-one
中国象棋从零开始

## 项目目录下`<main.c>`开头设置全局变量debug模式：
> bool GYF_Debug_Mode[2]={false, false};

设置为：
> {true,false}

**表示开启debug信息输出，关闭测试**

> {false,true}

**表示关闭dedug信息输出，开启测试**

> {true, true}

**表示debug模式全开**

> {false, false}

**表示debug模式全关**

## 目前测试是
正常选棋，棋子索引正常。
但固定坐标为0，因为可落点计算全部都是坐标计算出来的，与索引无关。
所以让任何位置的棋子全部往第1行、第1列落子。
从而容易出现吃子。达到测试吃子的需求。