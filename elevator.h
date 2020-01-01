#pragma once
#include "intlink.h"
#include <time.h>
//每一层楼有上楼的人和下楼的人
//分别使用两个链表存储这些数据，一个人一个节点
//一部电梯有14层楼，上楼的人按照升序排列，下楼的人按照降序排列
//电梯先上楼，后下楼，当到达一层楼之后，
//按次序访问每一层楼，得到下一次的目的地，如果人满了则不考虑上，只考虑下

class Floor
{
public:
	Link up = 0;
	Link dw = 1;
	int upnum = 0;
	int dwnum = 0;
};

class Elevator
{
public:
	int all;//电梯运行人次
	int now;
	int tar;
	int stat;//1上升 -1下降
	int people;
	int require[14];
	Floor floor[14];//存储电梯内的人的请求信息
	void request(int from, int to, int num = 1);
	Elevator();
	void nexttask();//刷新target
	void onoff();

private:
	time_t start=0, present=0;
	int searchup(int from,int to);
	int searchdw(int from,int to);//查找called
	int rsearchup(int from,int to);
	int rsearchdw(int from,int to);

};

