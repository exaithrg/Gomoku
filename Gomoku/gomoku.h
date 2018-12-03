#pragma once

//////////////////////////////////////////////////////////////////////////////////
//本程序只供学习使用，未经作者许可，不得用于其它任何用途
//五子棋声明头文件
//作者：H.R.Geng
//修改日期：2018.12.3
//版本：v1.0
//All rights reserved
//按F12（或Fn+F12)可以追踪函数
//
//
//////////////////////////////////////////////////////////////////////////////////

typedef int Status;

#define OK 0					//正常
#define ERROR 1					//错误

#define QiPanGeKuan 40			//棋盘格宽
#define LightBrown 0x0088AA		//棋盘底色

#define JingDu 15				//落子判断精度，越大精度越低
#define ChessPiecesSize 15		//棋子大小

#define PlayerIsBlack 1			//黑方落子
#define PlayerIsWhite 2			//白方落子

#define KeepPlaying 0			//未决出胜负
#define BlackWin 1				//黑胜判断
#define WhiteWin 2				//白胜判断
#define DrawningGame 3			//和局判断

#define StepTime 10				//步时（秒数）

//程序初始界面
Status StartMenu(int Gomoku_CSBD[15][15]);

//游戏界面绘制
Status DrawBackground();

//五子棋主程序
Status GomokuRun(int Gomoku_CSBD[15][15], int &restartgame);

//输出游戏结束信息
Status GameFinish(int index, int Gomoku_CSBD[15][15]);

//鼠标左键点击落子
Status MoveByMouse(MOUSEMSG msg, int Gomoku_CSBD[15][15], int &player, int &BushuBlack, int &BushuWhite);

//给定坐标落子（尚未实现）
//Status MoveByNum(int hang, int lie, int Gomoku_CSBD[15][15], 
//	int &player, int &BushuBlack, int &BushuWhite);	

//判断是否有人获胜
//黑胜返回BlackWin，白胜返回WhiteWin，无子可下返回DrawningGame，未决出胜负返回KeepPlaying
int WinOrNot(int Gomoku_CSBD[15][15], int BushuBlack, int BushuWhite);

//关闭程序
Status ExitGame(MOUSEMSG m, int left, int right, int top, int bottom);

//重新开始新的一局
Status RestartGame(MOUSEMSG m, int left, int right, int top, int bottom);

//打印步时倒计时
Status PrintTime(int player, time_t StartTime, time_t FinishTime, bool &ChangePlayer);

//判断步时是否超时
bool TimeFinish(time_t StartTime, time_t FinishTime);