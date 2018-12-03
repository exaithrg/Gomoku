#include<graphics.h>
#include<cstdlib>
#include"gomoku.h"
#pragma warning(disable:4996)
using namespace std;

//////////////////////////////////////////////////////////////////////////////////
//本程序只供学习使用，未经作者许可，不得用于其它任何用途
//五子棋主程序
//作者：H.R.Geng
//修改日期：2018.12.3
//版本：v1.0
//All rights reserved
//按F12（或Fn+F12)可以追踪函数
//
//
//////////////////////////////////////////////////////////////////////////////////

int main()
{
	//gomoku chessboard
	int Gomoku_CSBD[15][15];	
	initgraph(1200, 713, SHOWCONSOLE);
	StartMenu(Gomoku_CSBD);
	closegraph();
	return 0;
}
