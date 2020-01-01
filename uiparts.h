#pragma once
#include <easyx.h>
#include <conio.h>
#include <cstdio>
#include <ctime>
#include <cmath>
#include <string>
#include <mutex>
#pragma comment( lib, "MSIMG32.LIB")
#include "elevator.h"
#define PURPLE RGB(107,105,214)
using namespace std;

class ui {
private:
	int from,to,sig;
	int x;
	int yNow;
	int yTar;
	void putTimage(int x, int y, IMAGE* srcimg, IMAGE* dstimg = NULL, UINT transparentcolor = 0);
	void drawFloor(int x, int y);
	void drawUnit(int x, int y);
	void drawNum();
	void drawConsole(Elevator &a);
	MOUSEMSG m;

public:
	int stat;
	ui();
	void refreshdata(int a=1);
	void inputbyhand(Elevator &m);
	void inputbyfile(Elevator &m);
	void inputbyrand(Elevator &m);

	int draw(int upordown,Elevator a);
	int mousechoose();
	~ui();
};