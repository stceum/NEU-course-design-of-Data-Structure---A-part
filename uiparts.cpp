#include <iostream>
#include "uiparts.h"
#include<string>
#include<fstream>
#include<windows.h>

void ui::putTimage(int x, int y, IMAGE* srcimg, IMAGE* dstimg, UINT transparentcolor)
{
	HDC dstDC = GetImageHDC(dstimg);
	HDC srcDC = GetImageHDC(srcimg);
	int w = srcimg->getwidth();
	int h = srcimg->getheight();

	// 使用 Windows GDI 函数实现透明位图
	TransparentBlt(dstDC, x, y, w, h, srcDC, 0, 0, w, h, transparentcolor);
}

void ui::drawFloor(int x, int y)
{
	IMAGE floor(100, 50);
	SetWorkingImage(&floor);
	cleardevice();
	setlinecolor(RED);
	setlinestyle(PS_DASH);
	rectangle(14, 3, 86, 47);
	SetWorkingImage();
	clearrectangle(x + 13, y, x + 86, y + 50);
	putTimage(x, y, &floor);
}

void ui::drawUnit(int x, int y)
{
	setlinestyle(PS_SOLID, 2);
	setlinecolor(BLACK);
	rectangle(x, y, x + 100, y + 900);
	//单层电梯
	int i;
	for (i = 0; i < 14; i++) {
		drawFloor(x, i * 50);
	}
	settextcolor(PURPLE);
	settextstyle(22, 0, _T("黑体"));
	RECT r = { x, i * 50,100 + x, (i + 1) * 50 };
	LPCTSTR list[14] = { _T("电梯1"),_T("电梯2"), _T("电梯3"), _T("电梯4")};
	int which = (x - 50) / 100;
	drawtext(list[which], &r, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
}

void ui::drawNum()
{
	setlinestyle(PS_SOLID, 2);
	setlinecolor(BLACK);
	rectangle(0, 0, 50, 750);
	rectangle(150, 0, 250, 750);
	rectangle(250, 0, 600, 750);
	setlinestyle(PS_DASH);
	setlinecolor(RED);
	line(200, 0, 200, 750);
	rectangle(275, 25, 575, 725);

	setlinecolor(BLACK);
	setlinestyle(PS_SOLID, 3);
	int i;
	for (i = 0; i < 14; i++) {
		circle(25, (2 * i + 1) * 25, 18);
		settextcolor(PURPLE);
		settextstyle(22, 0, _T("黑体"));
		RECT r = { 0, i * 50,50, (i + 1) * 50 };
		LPCTSTR list[14] = { _T("14"),_T("13"), _T("12"), _T("11"), _T("10"), _T("9"),_T("8"), _T("7"),_T("6"), _T("5"),_T("4"),_T("3"), _T("2"), _T("1") };
		drawtext(list[i], &r, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
	}
	RECT r = { 0, i * 50,50, (i + 1) * 50 };
	drawtext(_T("序号"), &r, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
	LPCTSTR list[2] = { _T("↑"),_T("↓") };
	r = { 150,700,200,750 };
	drawtext(list[0], &r, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
	r = { 200,700,250,750 };
	drawtext(list[1], &r, DT_CENTER | DT_VCENTER | DT_SINGLELINE);

}


LPCTSTR inttolpctstr(int a)
{
	string str = std::to_string(a);
	int lengthW = MultiByteToWideChar(CP_ACP,0,str.c_str(),-1,NULL,NULL);	
	wchar_t* pUnicode = new wchar_t [lengthW*sizeof(wchar_t)];	
	memset(pUnicode,0,lengthW*sizeof(pUnicode));	
	MultiByteToWideChar(CP_ACP,0,str.c_str(),-1,pUnicode,lengthW);	
	return (LPCTSTR)pUnicode;
}

int inputbox(std::string a)
{
	wchar_t* tips = new wchar_t[strlen((a.c_str()))];
	int lengthW = MultiByteToWideChar(CP_ACP, 0, a.c_str(), -1, NULL, NULL);
	MultiByteToWideChar(CP_ACP, 0, a.c_str(), -1, tips, lengthW);
	LPTSTR s = new wchar_t[100];
	InputBox(s, 10, tips);
	int r;
	wchar_t* widestr = s;
	int num = WideCharToMultiByte(CP_OEMCP, NULL, widestr, -1, NULL, 0, NULL, FALSE);
	char* pchar = new char[num];
	WideCharToMultiByte(CP_OEMCP, NULL, widestr, -1, pchar, num, NULL, FALSE);
	sscanf(pchar, "%d", &r);
	delete[]tips;
	delete[]widestr;
	delete[]pchar;
	return r;
}

std::string inputbox()
{
	LPTSTR s = new wchar_t[100];
	InputBox(s, 100, _T("请输入文件名"));
	string r;
	wchar_t* widestr = s;
	int num = WideCharToMultiByte(CP_OEMCP, NULL, widestr, -1, NULL, 0, NULL, FALSE);
	char* pchar = new char[num];
	WideCharToMultiByte(CP_OEMCP, NULL, widestr, -1, pchar, num, NULL, FALSE);
	r = pchar;
	delete[]widestr;
	delete[]pchar;
	return r;
}

void ui::drawConsole(Elevator &a)
{
	settextcolor(RGB(255,0,0));
	clearrectangle(160, 0, 190, 700);
	clearrectangle(210, 0, 240, 700);
	for (int i = 0; i < 14; i++)
	{
		LPCTSTR tmp;
		RECT r = { 150,50 * i,200,50 + 50 * i };
		drawtext(tmp = inttolpctstr(a.floor[13-i].upnum), &r, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
		delete[]tmp;
		r = { 200,50 * i,250,50 + 50 * i };
		drawtext(tmp = inttolpctstr(a.floor[13-i].dwnum), &r, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
		delete[]tmp;

	}

	clearrectangle(425, 125, 570, 225);
	clearrectangle(425, 275, 570, 670);
	LPCTSTR list[] = { _T("14"),_T("13"), _T("12"), _T("11"), _T("10"), _T("9"),_T("8"), _T("7"),_T("6"), _T("5"),_T("4"),_T("3"), _T("2"), _T("1"),_T("DOWN"),_T("STOP"),_T("UP") };
	LPCTSTR tmp;
	RECT r = { 425,125,575,150 };
	drawtext(tmp=inttolpctstr(a.people), &r, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
	delete[]tmp;
	r = { 425,150,575,175 };
	drawtext(tmp=inttolpctstr(from), &r, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
	delete[]tmp;
	r = { 425,175,575,200 };
	drawtext(tmp=inttolpctstr(a.tar), &r, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
	delete[]tmp;
	r = { 425,200,575,225};
	drawtext(list[stat+15], &r, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
	for (int i = 0; i < 14; i++)
	{
		r = { 425,275 + 25 * i,575,300 + 25 * i };
		drawtext(tmp=inttolpctstr(a.require[i]), &r, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
		delete[]tmp;

	}
	r = { 425,625,575,675 };
	drawtext(tmp=inttolpctstr(a.all), &r, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
	delete[]tmp;
}

int ui::mousechoose()//1 2 3    0无响应
{
	m = GetMouseMsg();
	switch (m.uMsg)
	{
	case WM_LBUTTONDOWN:
		if (280 < m.x && m.x < 370 && 675 < m.y && m.y < 700)
		{
			return 1;
		}
		else if (380 < m.x && m.x < 470 && 675 < m.y && m.y < 700)
		{
			return 2;
		}
		else if (480 < m.x && m.x < 570 && 675 < m.y && m.y < 700)
		{
			return 3;
		}
		else
		{
			return 0;
		}
		break;
	default:
		return 0;
	}
	return 0;
}

ui::ui()
{
	initgraph(600, 750);
	BeginBatchDraw();
	setbkcolor(WHITE);
	cleardevice();
	drawNum();
	setfillcolor(PURPLE);
	drawUnit(50 , 0);
	yTar=yNow = 653;
	from = to = 1;
	x = 64;
	stat = 1;
	fillrectangle(x, yNow,x+72 ,yNow+44);
	settextcolor(PURPLE);
	settextstyle(30, 0, _T("黑体"));
	LPCTSTR list[] = {
		_T("电梯运行情况"),_T("当前载客人数"),_T("当前所在楼层"),_T("当前目标楼层"),
		_T("当前运行状态"),_T("客人去往各楼层情况"),_T("1"),_T("2"),
		_T("3"),_T("4"),_T("5"),_T("6"),
		_T("7"),_T("8"),_T("9"),_T("10"),
		_T("11"),_T("12"),_T("13"),_T("14"),
		_T("电梯运行人次"),_T("手动"),_T("文件"),_T("随机")
	};
	RECT r = { 275,25,575,125 };
	drawtext(list[0], &r, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
	settextstyle(20,0,_T("黑体"));
	for (int i = 0; i <4; i++)
	{
		r = { 275,125 + 25 * i,425,150 + 25 * i };
		drawtext(list[i+1], &r, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
	}
	settextstyle(25,0,_T("黑体"));
	r = { 275,225,575,275 };
	drawtext(list[5], &r, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
	settextstyle(20,0,_T("黑体"));
	for (int i = 0; i <14; i++)
	{
		r = { 275,275 + 25 * i,425,300 + 25 * i };
		drawtext(list[i+6], &r, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
	}
	r = { 275,625,425,675 };
	settextstyle(20,0,_T("黑体"));
	drawtext(list[20], &r, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
	rectangle(280, 675, 370, 700);
	rectangle(380, 675, 470, 700);
	rectangle(480, 675, 570, 700);
	r = { 275,675,375,700 };
	drawtext(list[21], &r, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
	settextstyle(20,0,_T("黑体"));
	r = { 375,675,475,700 };
	drawtext(list[22], &r, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
	settextstyle(20,0,_T("黑体"));
	r = { 475,675,575,700 };
	drawtext(list[23], &r, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
	settextstyle(20,0,_T("黑体"));

	LPCTSTR list2[] = { _T("0"),_T("1"),_T("0"),_T("STOP") };
	r = { 425,125,575,150 };
	drawtext(list2[0], &r, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
	r = { 425,150,575,175 };
	drawtext(list2[1], &r, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
	r = { 425,175,575,200 };
	drawtext(list2[1], &r, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
	r = { 425,200,575,225};
	drawtext(list2[3], &r, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
	for (int i = 0; i < 14; i++)
	{
		r = { 425,275 + 25 * i,575,300 + 25 * i };
		drawtext(list2[2], &r, DT_CENTER | DT_VCENTER | DT_SINGLELINE);

	}
	r = { 425,625,575,675 };
	drawtext(list2[2], &r, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
	FlushBatchDraw();
}

void ui::refreshdata(int a)//记录电梯的目标
{
	to = a;
	yTar = 50 * (14 - to) + 3;//目标坐标
	sig= (from> to ? 1 : -1);//移动方向
}

void ui::inputbyhand(Elevator &m)
{
	int a, b, c;
	a = inputbox("请输入客人所在楼层：");
	b = inputbox("请输入客人目的楼层：");
	c = inputbox("请输入客人数目：");
	if(1<=a&&a<=14&&1<=b&&b<=14&&c>0)
		m.request(a, b, c);
	else
	{
		MessageBox(NULL,_T("非法输入！"),_T("error"), MB_ICONEXCLAMATION);
	}
}

void ui::inputbyfile(Elevator &m)
{
	string filename = inputbox();
	ifstream in;
	in.open(filename);
	int a, b, c;
	while (in >> a >> b >> c)
	{
		m.request(a, b, c);
	}
	in.close();
}

void ui::inputbyrand(Elevator &m)
{
	srand(time(0));
	m.request(rand() % 14 + 1, rand() % 14 + 1, rand() % 13);
}

int ui::draw(int upordown,Elevator a)//根据设定画一帧
{
	stat = upordown;
	BeginBatchDraw();
	if (yNow != yTar) {
		drawUnit(50, 0);
		setfillcolor(PURPLE);
		yNow += sig;
		fillrectangle(x, yNow, x + 72, yNow + 44);
		if ((yNow - 3) % 50 == 0) {
			from -= sig;
		}
	}
	else {
		stat = 0;
	}
	drawConsole(a);
	FlushBatchDraw();
	return stat;
}

ui::~ui()
{
}
