#include<graphics.h>
#include<cstdlib>
#include"gomoku.h"
#pragma warning(disable:4996)
using namespace std;


int main()
{
	//gomoku chessboard
	int Gomoku_CSBD[15][15];	
	initgraph(1200, 713, SHOWCONSOLE);
	menu(Gomoku_CSBD);
	closegraph();
	return 0;
}
