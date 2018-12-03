#pragma once

typedef int Status;

#define OK 0					//正常
#define ERROR 1					//错误
#define QiPanGeKuan 40			//棋盘格宽
#define LightBrown 0x0088AA		//棋盘底色
#define JingDu 15				//落子判断精度，越大精度越低
#define ChessPiecesSize 15		//棋子大小
#define PlayerIsBlack 1			//黑方在下
#define PlayerIsWhite 2			//白方在下
#define KeepPlaying 0			//未决出胜负
#define BlackWin 1				//黑胜
#define WhiteWin 2				//白胜
#define DrawningGame 3			//和局
#define StepTime 60				//步时
Status menu(int Gomoku_CSBD[15][15]);
Status DrawBackground();
Status playgame(int Gomoku_CSBD[15][15], int &restartgame);
Status Finish(int index, int Gomoku_CSBD[15][15]);
//鼠标左键点击落子
Status MoveByMouse(MOUSEMSG msg, int Gomoku_CSBD[15][15], int &player, int &BushuBlack, int &BushuWhite);
Status MoveByNum(int Gomoku_CSBD[15][15], int &player, int &BushuBlack, int &BushuWhite);	//给定坐标落子

//判断是否有人获胜，黑胜返回1，白胜返回2，否则返回0
int WinOrNot(int Gomoku_CSBD[15][15], int BushuBlack, int BushuWhite);

Status ExitGame(MOUSEMSG m, int left, int right, int top, int bottom);
Status RestartGame(MOUSEMSG m, int left, int right, int top, int bottom);
Status PrintTime(int player, time_t StartTime, time_t FinishTime, bool &ChangePlayer);

bool TimeFinish(time_t StartTime, time_t FinishTime);