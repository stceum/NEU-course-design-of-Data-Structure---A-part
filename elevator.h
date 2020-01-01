#pragma once
#include "intlink.h"
#include <time.h>
//ÿһ��¥����¥���˺���¥����
//�ֱ�ʹ����������洢��Щ���ݣ�һ����һ���ڵ�
//һ��������14��¥����¥���˰����������У���¥���˰��ս�������
//��������¥������¥��������һ��¥֮��
//���������ÿһ��¥���õ���һ�ε�Ŀ�ĵأ�����������򲻿����ϣ�ֻ������

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
	int all;//���������˴�
	int now;
	int tar;
	int stat;//1���� -1�½�
	int people;
	int require[14];
	Floor floor[14];//�洢�����ڵ��˵�������Ϣ
	void request(int from, int to, int num = 1);
	Elevator();
	void nexttask();//ˢ��target
	void onoff();

private:
	time_t start=0, present=0;
	int searchup(int from,int to);
	int searchdw(int from,int to);//����called
	int rsearchup(int from,int to);
	int rsearchdw(int from,int to);

};

