#include<iostream>
#include<graphics.h>
#include<conio.h>
#include<windows.h>
#include<ctime>
#include"gomoku.h"
using namespace std;

Status menu(int Gomoku_CSBD[15][15])	//主菜单
{
	int left, right, top, bottom;
	int restartgame = OK;
	IMAGE bkgrd, playbk;
	setaspectratio(1, 1);	//设置当前缩放因子
	loadimage(&bkgrd, "start1.jpg", 1200, 713, true);// 从资源文件获取图像(bmp/jpg/gif/emf/wmf)
	putimage(0, 0, &bkgrd, SRCPAINT);// 绘制图像到屏幕
	left = 740;
	right = 945;
	top = 280;
	bottom = 385;
	MOUSEMSG m;
	m = GetMouseMsg();
	while (true)
	{
		if (MouseHit()) {
			m = GetMouseMsg();
		}
		if (m.uMsg == WM_MOUSEMOVE && m.x >= left && m.x <= right && m.y >= top && m.y <= bottom)
		{
			setlinecolor(BLACK);
			setlinestyle(PS_SOLID, 3, NULL, 0);
			ellipse(left, top, right, bottom);
		}
		if (m.uMsg == WM_LBUTTONDOWN && m.x >= left && m.x <= right && m.y >= top && m.y <= bottom)
		{
			cleardevice();
			loadimage(&playbk, "playbk.jpg", 1200, 713, false);// 从资源文件获取图像(bmp/jpg/gif/emf/wmf)
			putimage(0, 0, &playbk, SRCPAINT);// 绘制图像到屏幕
			while (restartgame==OK)
			{
				DrawBackground();
				playgame(Gomoku_CSBD, restartgame);
			}
			return OK;	//退出开始菜单
		}
		if (!(m.x >= left && m.x <= right && m.y >= top && m.y <= bottom))
		{
			setlinecolor(WHITE);
			setlinestyle(PS_SOLID, 3, NULL, 0);
			ellipse(left, top, right, bottom);
		}
	}
	return OK;
}

Status DrawBackground()	//画背景
{
	int Kuan;
	IMAGE playbk;
	char YuanLaiDe[5];
	Kuan = QiPanGeKuan * 15;
	graphdefaults();	//重置默认
	setbkcolor(WHITE);
	settextstyle(50, 20, "汉仪赵楷繁");
	settextcolor(LIGHTRED);
	outtextxy(QiPanGeKuan * 16, 80, "落子方 ");
	settextstyle(50, 25, "隶书");
	settextcolor(BLACK);
	outtextxy(830, 80, "黑");
	settextstyle(50, 20, "华文行楷");
	outtextxy(QiPanGeKuan * 16, 130, "黑方步时");
	outtextxy(QiPanGeKuan * 16, 230, "白方步时");
	settextstyle(50, 20, "Times New Roman");
	if (StepTime < 10) {
		YuanLaiDe[0] = '0';
		YuanLaiDe[1] = '0' + StepTime;
		YuanLaiDe[2] = YuanLaiDe[3] = YuanLaiDe[4] = '\0';
	}
	else {
		_itoa_s(StepTime, YuanLaiDe, 10);
	}
	outtextxy(QiPanGeKuan * 18, 180, YuanLaiDe);		//黑方步时
	outtextxy(QiPanGeKuan * 18, 280, YuanLaiDe);		//白方步时
	settextstyle(50, 15, "华文行楷");
	outtextxy(QiPanGeKuan * 20, 180, "秒");
	outtextxy(QiPanGeKuan * 20, 280, "秒");
	setfillcolor(LightBrown);
	fillrectangle(QiPanGeKuan - ChessPiecesSize, QiPanGeKuan - ChessPiecesSize,
		QiPanGeKuan * 15 + ChessPiecesSize, QiPanGeKuan * 15 + ChessPiecesSize);
	setlinecolor(BROWN);
	setlinestyle(PS_SOLID, 3, NULL, 0);
	for (int i = QiPanGeKuan; i <= Kuan; i += QiPanGeKuan)
	{
		line(i, QiPanGeKuan, i, Kuan);
		line(QiPanGeKuan, i, Kuan, i);
	}
	setfillcolor(BROWN);
	fillcircle(QiPanGeKuan * 8, QiPanGeKuan * 8, 6);
	fillcircle(QiPanGeKuan * 4, QiPanGeKuan * 4, 6);
	fillcircle(QiPanGeKuan * 4, QiPanGeKuan * 12, 6);
	fillcircle(QiPanGeKuan * 12, QiPanGeKuan * 4, 6);
	fillcircle(QiPanGeKuan * 12, QiPanGeKuan * 12, 6);
	return OK;
}

Status playgame(int Gomoku_CSBD[15][15], int &restartgame)	//打游戏
{
	restartgame = ERROR;
	char YuanLaiDe[5];
	MOUSEMSG msg;
	msg = GetMouseMsg();
	time_t StartTime, FinishTime;
	time_t LastTime;
	bool ChangePlayer;
	int StartTiming = 0;
	int tuichuyouxi = ERROR;
	int left_exit = 750;
	int right_exit = 1018;
	int top_exit = 520;
	int bottom_exit = 590;
	int left_restart = 750;
	int right_restart = 1018;
	int top_restart = 420;
	int bottom_restart = 490;
	settextstyle(70, 21, "华文行楷");
	setbkcolor(WHITE);
	settextcolor(RED);
	outtextxy(750, 520, "点击退出");
	settextcolor(BLUE);
	outtextxy(750, 420, "重新开始");
	int player=PlayerIsBlack;
	int BushuBlack = 0, BushuWhite = 0;	//初值为0
	int i, j;
	int LuoZi = ERROR;
	for (i = 0; i < 15; i++) {
		for (j = 0; j < 15; j++) {
			Gomoku_CSBD[i][j] = 0;
		}
	}
	int win = KeepPlaying;
	while (win == KeepPlaying)
	{
		if (StartTiming == 1) {
			FinishTime = time(NULL);
			if (LastTime != FinishTime) {
				PrintTime(player, StartTime, FinishTime, ChangePlayer);
				if (ChangePlayer) {	//如果时间到底了
					if (StepTime < 10) {
						YuanLaiDe[0] = '0';
						YuanLaiDe[1] = '0' + StepTime;
						YuanLaiDe[2] = YuanLaiDe[3] = YuanLaiDe[4] = '\0';
					}
					else {
						_itoa_s(StepTime, YuanLaiDe, 10);
					}
					StartTime = time(NULL);		//忘清零会导致黑白每秒反复循环
					if (player == PlayerIsBlack) {
						player = PlayerIsWhite;
						//outtextxy(QiPanGeKuan * 16, 280, YuanLaiDe);
						settextstyle(50, 25, "隶书");
						settextcolor(BLACK);
						outtextxy(830, 80, "白");
					}
					else {
						player = PlayerIsBlack;
						//outtextxy(QiPanGeKuan * 16, 180, YuanLaiDe);
						settextstyle(50, 25, "隶书");
						settextcolor(BLACK);
						outtextxy(830, 80, "黑");
					}
				}
			}
			LastTime = FinishTime;
		}
		LuoZi = ERROR;
		if (MouseHit()) {
			msg = GetMouseMsg();
		}
		tuichuyouxi = ExitGame(msg, left_exit, right_exit, top_exit, bottom_exit);
		if (tuichuyouxi == OK) {
			return OK;
		}
		restartgame = RestartGame(msg, left_restart, right_restart, top_restart, bottom_restart);
		if (restartgame == OK) {
			return OK;
		}
		LuoZi = MoveByMouse(msg, Gomoku_CSBD, player, BushuBlack, BushuWhite);
		//判断是否赢
		if (LuoZi == OK) {	//如果落子，那么步时给对方，重新算数
			StartTime = time(NULL);
			if (StartTiming == 0) {
				LastTime = FinishTime = time(NULL);
				//FinishTime = time(NULL);
			}
			StartTiming = 1;	//第一次落子开始计时
			win = WinOrNot(Gomoku_CSBD, BushuBlack, BushuWhite);
		}
	}
	Finish(win, Gomoku_CSBD);
	while (true)
	{
		if (MouseHit()) {
			msg = GetMouseMsg();
		}
		tuichuyouxi = ExitGame(msg, left_exit, right_exit, top_exit, bottom_exit);
		if (tuichuyouxi == OK) {
			return OK;
		}
		restartgame = RestartGame(msg, left_restart, right_restart, top_restart, bottom_restart);
		if (restartgame == OK) {
			return OK;
		}
	}
	return OK;
}

Status ExitGame(MOUSEMSG m, int left, int right, int top, int bottom) {
	if (m.uMsg == WM_MOUSEMOVE && m.x >= left && m.x <= right && m.y >= top && m.y <= bottom)
	{
		setlinecolor(BLACK);
		setlinestyle(PS_SOLID, 3, NULL, 0);
		rectangle(left, top, right, bottom);
	}
	if (m.uMsg == WM_LBUTTONDOWN && m.x >= left && m.x <= right && m.y >= top && m.y <= bottom)
	{
		return OK;	//退出
	}
	if (!(m.x >= left && m.x <= right && m.y >= top && m.y <= bottom))
	{
		setlinecolor(WHITE);
		setlinestyle(PS_SOLID, 3, NULL, 0);
		rectangle(left, top, right, bottom);
	}
	return ERROR;
}

Status RestartGame(MOUSEMSG m, int left, int right, int top, int bottom) {
	if (m.uMsg == WM_MOUSEMOVE && m.x >= left && m.x <= right && m.y >= top && m.y <= bottom)
	{
		setlinecolor(BLACK);
		setlinestyle(PS_SOLID, 3, NULL, 0);
		rectangle(left, top, right, bottom);
	}
	if (m.uMsg == WM_LBUTTONDOWN && m.x >= left && m.x <= right && m.y >= top && m.y <= bottom)
	{
		DrawBackground();
		return OK;
	}
	if (!(m.x >= left && m.x <= right && m.y >= top && m.y <= bottom))
	{
		setlinecolor(WHITE);
		setlinestyle(PS_SOLID, 3, NULL, 0);
		rectangle(left, top, right, bottom);
	}
	return ERROR;
}

//Status Finish(int index, int Gomoku_CSBD[15][15], int &restartgame)
Status Finish(int index, int Gomoku_CSBD[15][15])
{
	int tuichuyouxi = ERROR;
	//int left_exit = 750;
	//int right_exit = 1018;
	//int top_exit = 500;
	//int bottom_exit = 570;
	//int left_restart = 750;
	//int right_restart = 1018;
	//int top_restart = 100;
	//int bottom_restart = 200;
	settextstyle(100, 30, "华文行楷");
	if (index == BlackWin)
	{
		setbkcolor(WHITE);
		settextstyle(50, 20, "汉仪赵楷繁");
		settextcolor(RED);
		outtextxy(QiPanGeKuan * 16, 80, "  胜方 ");
		settextstyle(50, 25, "隶书");
		settextcolor(BLACK);
		outtextxy(830, 80, "黑");
	}
	else if(index==WhiteWin)
	{
		setbkcolor(WHITE);
		settextstyle(50, 20, "汉仪赵楷繁");
		settextcolor(RED);
		outtextxy(QiPanGeKuan * 16, 80, "  胜方 ");
		settextstyle(50, 25, "隶书");
		settextcolor(BLACK);
		outtextxy(830, 80, "白");
	}
	else if (index == DrawningGame) {
		setbkcolor(WHITE);
		settextcolor(BLACK);
		outtextxy(QiPanGeKuan * 16, 80, "     和局     ");
	}
	//settextstyle(70, 21, "华文行楷");
	//setbkcolor(WHITE);
	//settextcolor(RED);
	//outtextxy(750, 500, "点击退出");
	//while (true)
	//{
	//	m = GetMouseMsg();
	//	tuichuyouxi = ExitGame(m, left_exit, right_exit, top_exit, bottom_exit);
	//	if (tuichuyouxi == OK) {
	//		return OK;
	//	}
	//	restartgame = RestartGame(m, left_restart, right_restart, top_restart, bottom_restart);
	//	if (restartgame == OK) {
	//		return OK;
	//	}
	//}
	return OK;
}

int WinOrNot(int Gomoku_CSBD[15][15], int BushuBlack, int BushuWhite) {
	int i, j;
	int a, b;
	int ZongBuShu;
	ZongBuShu = BushuBlack + BushuWhite;
	if (ZongBuShu == 225) return DrawningGame;
	for (j = 0; j < 15; j++)
	{
		for (i = 0; i < 15; i++)
		{
			if (i + 4 >= 15 || j + 4 >= 15) {
				continue;
			}
			if ((Gomoku_CSBD[j][i] == 1 && Gomoku_CSBD[j][i + 1] == 1 && Gomoku_CSBD[j][i + 2] == 1 
				&& Gomoku_CSBD[j][i + 3] == 1 && Gomoku_CSBD[j][i + 4] == 1))
				//判断黑棋横向
			{
				setlinestyle(PS_SOLID, 5, NULL, 0);
				setlinecolor(RED);
				line(QiPanGeKuan*(i + 1), QiPanGeKuan*(j + 1), QiPanGeKuan*(i + 5), QiPanGeKuan*(j + 1));
				//line( QiPanGeKuan*(j + 1), QiPanGeKuan*(i + 1), QiPanGeKuan*(j + 1), QiPanGeKuan*(i + 5));
				return BlackWin;
			}
			if (Gomoku_CSBD[i][j] == 1 && Gomoku_CSBD[i + 1][j] == 1 && Gomoku_CSBD[i + 2][j] == 1
				&& Gomoku_CSBD[i + 3][j] == 1 && Gomoku_CSBD[i + 4][j] == 1) {
				//判断黑棋纵向
				setlinestyle(PS_SOLID, 5, NULL, 0);
				setlinecolor(RED);
				line(QiPanGeKuan*(j + 1), QiPanGeKuan*(i + 1), QiPanGeKuan*(j + 1), QiPanGeKuan*(i + 5));
				//line(QiPanGeKuan*(i + 1), QiPanGeKuan*(j + 1), QiPanGeKuan*(i + 5), QiPanGeKuan*(j + 1));
				return BlackWin;
			}
			if ((Gomoku_CSBD[j][i] == 2 && Gomoku_CSBD[j][i + 1] == 2 && Gomoku_CSBD[j][i + 2] == 2 
				&& Gomoku_CSBD[j][i + 3] == 2 && Gomoku_CSBD[j][i + 4] == 2))
				//判断白棋横向
			{
				setlinestyle(PS_SOLID, 5, NULL, 0);
				setlinecolor(RED);
				line(QiPanGeKuan*(i + 1), QiPanGeKuan*(j + 1), QiPanGeKuan*(i + 5), QiPanGeKuan*(j + 1));
				//line(QiPanGeKuan*(i + 1), QiPanGeKuan*(j + 1),  QiPanGeKuan*(j + 1), QiPanGeKuan*(i + 5));
				//line(QiPanGeKuan*(j + 1), QiPanGeKuan*(i + 1), QiPanGeKuan*(j + 1), QiPanGeKuan*(i + 5));
				return WhiteWin;
			}
			if (Gomoku_CSBD[i][j] == 2 && Gomoku_CSBD[i + 1][j] == 2 && Gomoku_CSBD[i + 2][j] == 2
				&& Gomoku_CSBD[i + 3][j] == 2 && Gomoku_CSBD[i + 4][j] == 2) {
				//判断白棋纵向
				setlinestyle(PS_SOLID, 5, NULL, 0);
				setlinecolor(RED);
				line( QiPanGeKuan*(j + 1), QiPanGeKuan*(i + 1),  QiPanGeKuan*(j + 1), QiPanGeKuan*(i + 5));
				return WhiteWin;
			}
		}
	}
	for (j = 0; j<15; j++)
	{
		for (i = 0; i<15; i++)
		{
			if (i + 4 >= 15 || j + 4 >= 15 ) {
				continue;
			}
			if (Gomoku_CSBD[j][i] == 1 && Gomoku_CSBD[j + 1][i + 1] == 1 
				&& Gomoku_CSBD[j + 2][i + 2] == 1 && Gomoku_CSBD[j + 3][i + 3] == 1 
				&& Gomoku_CSBD[j + 4][i + 4] == 1)
				//判断黑棋右斜
			{
				setlinestyle(PS_SOLID, 5, NULL, 0);
				setlinecolor(RED);
				line(QiPanGeKuan*(i + 1), QiPanGeKuan*(j + 1), QiPanGeKuan*(i + 5), QiPanGeKuan*(j + 5));
				return BlackWin;
			}
			if (Gomoku_CSBD[j][i] == 2 && Gomoku_CSBD[j + 1][i + 1] == 2 
				&& Gomoku_CSBD[j + 2][i + 2] == 2 && Gomoku_CSBD[j + 3][i + 3] == 2 
				&& Gomoku_CSBD[j + 4][i + 4] == 2)
				//判断白棋右斜
			{
				setlinestyle(PS_SOLID, 5, NULL, 0);
				setlinecolor(RED);
				line( QiPanGeKuan*(i + 1), QiPanGeKuan*(j + 1), QiPanGeKuan*(i + 5), QiPanGeKuan*(j + 5));
				//setlinestyle(PS_SOLID, 5, NULL, 0);
				//setlinecolor(RED);
				//line(QiPanGeKuan*(j + 1), QiPanGeKuan*(i + 1), QiPanGeKuan*(j + 5), QiPanGeKuan*(i + 5));
				//cout << "j=" << j << "i=" << i << endl;
				//for (a = 0; a < 15; a++) {
				//	for (b = 0; b < 15; b++) {
				//		cout << Gomoku_CSBD[a][b] << " ";
				//	}
				//	cout << endl;
				//}
				//cout << "  以下是判定" << endl;
				//cout << "Gomoku_CSBD[i][j]" << endl;
				//for (a = 0; a < 15; a++) {
				//	cout << Gomoku_CSBD[j][a] << " ";
				//}
				//cout << endl << "条件内容见下" << endl;
				//for (a = 0; a < 5; a++) {
				//	cout << Gomoku_CSBD[j + a][i + a] << " ";
				//}
				////有bug;
				return WhiteWin;
			}
		}
		if (i - 4 <= 0) {
			continue;
		}
		for (i = 4; i<15; i++)
		{
			if (Gomoku_CSBD[j][i] == 1 && Gomoku_CSBD[j + 1][i - 1] == 1 
				&& Gomoku_CSBD[j + 2][i - 2] == 1 && Gomoku_CSBD[j + 3][i - 3] == 1 
				&& Gomoku_CSBD[j + 4][i - 4] == 1)
				//判断黑棋左斜
			{
				setlinestyle(PS_SOLID, 5, NULL, 0);
				setlinecolor(RED);
				line(QiPanGeKuan*(i + 1), QiPanGeKuan*(j + 1), QiPanGeKuan*(i - 3), QiPanGeKuan*(j + 5));
				return BlackWin;
			}
			if (Gomoku_CSBD[j][i] == 2 && Gomoku_CSBD[j + 1][i - 1] == 2 
				&& Gomoku_CSBD[j + 2][i - 2] == 2 && Gomoku_CSBD[j + 3][i - 3] == 2 
				&& Gomoku_CSBD[j + 4][i - 4] == 2)
				//判断白棋左斜
			{
				setlinestyle(PS_SOLID, 5, NULL, 0);
				setlinecolor(RED);
				line(QiPanGeKuan*(i + 1), QiPanGeKuan*(j + 1), QiPanGeKuan*(i - 3), QiPanGeKuan*(j + 5));
				return WhiteWin;
			}
		}
	}
	return KeepPlaying;
}

//实现目标：
//更改Gomoku数组更新落子信息
//在屏幕上打印落子
Status MoveByMouse(MOUSEMSG msg, int Gomoku_CSBD[15][15], int &player, int &BushuBlack, int &BushuWhite) {
	int lie, hang;
	if (msg.uMsg == WM_LBUTTONDOWN)
	{
		for (lie = QiPanGeKuan; lie <= QiPanGeKuan * 15; lie += QiPanGeKuan)
		{
			if (msg.x <= lie + JingDu && msg.x >= lie - JingDu)
			{
				for (hang = QiPanGeKuan; hang <= QiPanGeKuan * 15; hang += QiPanGeKuan)
				{
					if (msg.y <= hang + JingDu && msg.y >= hang - JingDu)
					{
						if (player == PlayerIsBlack && Gomoku_CSBD[hang / QiPanGeKuan - 1][lie / QiPanGeKuan - 1] == 0)
						{
							setfillcolor(BLACK);	//黑方
							solidcircle(lie, hang, ChessPiecesSize);
							Gomoku_CSBD[hang / QiPanGeKuan - 1][lie / QiPanGeKuan - 1] = 1;
							player = PlayerIsWhite;
							settextstyle(50, 25, "隶书");
							settextcolor(BLACK);
							outtextxy(830, 80, "白");
							BushuBlack++;
							return OK;
						}
						if (player == PlayerIsWhite && Gomoku_CSBD[hang / QiPanGeKuan - 1][lie / QiPanGeKuan - 1] == 0)
						{
							setfillcolor(WHITE);
							solidcircle(lie, hang, ChessPiecesSize);
							Gomoku_CSBD[hang / QiPanGeKuan - 1][lie / QiPanGeKuan - 1] = 2;
							player = PlayerIsBlack;
							settextstyle(50, 25, "隶书");
							settextcolor(BLACK);
							outtextxy(830, 80, "黑");
							BushuWhite++;
							return OK;
						}
					}
				}
			}
		}
	}
	return ERROR;
}

bool TimeFinish(time_t StartTime, time_t FinishTime) {
	if (FinishTime - StartTime >= StepTime) return true;
	return false;
}

Status PrintTime(int player, time_t StartTime, time_t FinishTime, bool &ChangePlayer) {
	ChangePlayer = false;
	char RemainTime[5];
	char YuanLaiDe[5];
	int i;
	time_t TimeDifference;
	time_t TimeRemain;
	//RemainTime_Black[2] = RemainTime_White[2] = ':';
	//暂时将步时写死为1分钟，需要改动再改
	//int hour_steptime, minute_steptime, second_steptime;
	//hour_steptime = StepTime / 3600;
	//minute_steptime = StepTime % 3600;
	//minute_steptime = minute_steptime / 60;
	//second_steptime = minute_steptime % 60;
	//
	//
	TimeDifference = FinishTime - StartTime;
	TimeRemain = StepTime - TimeDifference;
	_itoa_s(TimeRemain, RemainTime, 10);
	if (TimeRemain < 10) {
		RemainTime[0] = '0';
		RemainTime[1] = '0' + TimeRemain;
		RemainTime[2] = RemainTime[3] = RemainTime[4] = '\0';
	}
	if (StepTime < 10) {
		YuanLaiDe[0] = '0';
		YuanLaiDe[1] = '0' + StepTime;
		YuanLaiDe[2] = YuanLaiDe[3] = YuanLaiDe[4] = '\0';
	}
	else {
		_itoa_s(StepTime, YuanLaiDe, 10);
	}
	if (!TimeFinish(StartTime, FinishTime)) {
		if (player == PlayerIsBlack) {
			setbkcolor(WHITE);
			settextstyle(50, 20, "Times New Roman");
			//setfillcolor(WHITE);
			//fillrectangle(QiPanGeKuan * 16, 180, QiPanGeKuan * 16 + 100, 230);
			outtextxy(QiPanGeKuan * 18, 180, RemainTime);	//黑方步时
			//fillrectangle(QiPanGeKuan * 16, 280, QiPanGeKuan * 16 + 100, 330);
			outtextxy(QiPanGeKuan * 18, 280, YuanLaiDe);		//白方步时
		}
		else if (player == PlayerIsWhite) {
			setbkcolor(WHITE);
			settextstyle(50, 20, "Times New Roman");
			outtextxy(QiPanGeKuan * 18, 180, YuanLaiDe);		//黑方步时
			outtextxy(QiPanGeKuan * 18, 280, RemainTime);	//白方步时
		}
		else {
			return ERROR;
		}
	}
	else {
		if (player == PlayerIsBlack) {
			setbkcolor(WHITE);
			settextstyle(50, 20, "Times New Roman");
			//setfillcolor(WHITE);
			//fillrectangle(QiPanGeKuan * 16, 180, QiPanGeKuan * 16 + 100, 230);
			outtextxy(QiPanGeKuan * 18, 180, YuanLaiDe);	//黑方步时
															//fillrectangle(QiPanGeKuan * 16, 280, QiPanGeKuan * 16 + 100, 330);
			outtextxy(QiPanGeKuan * 18, 280, YuanLaiDe);		//白方步时
		}
		else if (player == PlayerIsWhite) {
			setbkcolor(WHITE);
			settextstyle(50, 20, "Times New Roman");
			outtextxy(QiPanGeKuan * 18, 180, YuanLaiDe);		//黑方步时
			outtextxy(QiPanGeKuan * 18, 280, YuanLaiDe);	//白方步时
		}
		else {
			return ERROR;
		}
		ChangePlayer = true;
	}
	return OK;
}

//Status MoveByNum(int Gomoku_CSBD[15][15], int &player, int &BushuBlack, int &BushuWhite) {
//
//}