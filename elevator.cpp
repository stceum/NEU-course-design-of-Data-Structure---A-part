#include "elevator.h"
#define MAX 12
#define DELAY 10

void Elevator::request(int from, int to, int num)
{
	start = present = 0;
	if (from > to)
	{
		for (int i = 0; i < num; i++)
		{
			floor[from - 1].dw.insert(to);
			floor[from - 1].dwnum++;

		}
	}
	if(from<to)
	{
		for (int i = 0; i < num; i++)
		{
			floor[from - 1].up.insert(to);
			floor[from - 1].upnum++;

		}
	}
}

Elevator::Elevator()
{
	now = tar = 1;
	stat = 1;
	people = 0;
	all = 0;
	for (int i = 0; i < 14; i++)
	{
		require[i] = 0;
	}
}

int Elevator::searchup(int from,int to=14)
{
	for (int i = from-1; i < to-1; i++)
	{
		if (floor[i].up.top())
		{
			return (i + 1);
		}
	}
	return 0;
}

int Elevator::searchdw(int from,int to=1)
{
	for (int i = from-1; i >to-1; i--)
	{
		if (floor[i].dw.top())
		{
			return (i + 1);
		}
	}
	return 0;

}

int Elevator::rsearchup(int from,int to=14)
{
	if (people == 0)
	{
		return 0;
	}
	for (int i = from - 1; i < to; i++)
	{
		if (require[i])
		{
			return (i + 1);
		}
	}
	return 0;
}

int Elevator::rsearchdw(int from,int to=1)
{
	if (people == 0)
	{
		return 0;
	}
	for (int i = from - 1; i > to-1; i--)
	{
		if (require[i])
		{
			return (i + 1);
		}
	}
	return 0;
}

void Elevator::nexttask()
{
	//根据方向找到最近的要下电梯的和想上电梯的
	//找到头了则换方向
	//两头都没有回一楼

	if (now == 14)
	{
		stat = -1;
	}
	if (now == 1)
	{
		stat = 1;
	}
	if (stat == 1 && (searchup(now) == 0) && (searchdw(14, now) == 0) && (rsearchup(now) == 0))
	{
		stat = -1;
	}
	else if (stat == -1 && (searchdw(now) == 0) && (searchup(1, now) == 0) && (rsearchdw(now) == 0))
	{
		stat = 1;
	}

	int tmp = 1;
	int required = 0, called = 0;
	if (people >= MAX)
	{
		if (stat == 1)
		{
			called = rsearchup(now);
			if (called)
			{
				tar = called;
				return;
			}
			else
			{
				called = rsearchdw(14);
				if (called)
				{
					tar = called;
					return;
				}
			}
		}
		else
		{
			called = rsearchdw(now);
			if (called)
			{
				tar = called;
				return;
			}
			else
			{
				called = rsearchup(1);
				if (called)
				{
					tar = called;
					return;
				}
			}

		}
	}
	else
	{
		if (stat == 1)
		{
			required = searchup(now);
			if (required)
			{
				called = rsearchup(now);
				if (called)
				{
					tar = called < required ? called : required;
				}
				else
				{
					tar = required;
				}
			}//no one required for it
			else
			{
				called = rsearchup(now);
				if (called)
				{
					tar = called;
				}
				else
				{
					required = searchdw(14);
					called = rsearchdw(14);
					if (required == 0 && called == 0)
					{
						if ((searchup(1)==0)&&(searchdw(14)==0)&&rsearchdw(14)==0)
						{
							if (start == 0)
							{
								time(&start);
							}
							else
							{
								time(&present);
								if (present > start + DELAY)
								{
									tar = 1;
									present = start = 0;
								}
								else
								{
									tar = now;
								}
							}
						}
						else
						{
							tar = now;
						}
					}
					else
					{
						if (required == 0 && called != 0)
						{
							tar = called;
						}
						else if (required != 0 && called == 0)
						{
							tar = required;
						}
						else
						{
							tar = required > called ? required : called;
						}
					}
				}
			}
		}//up
		else
		{
			required = searchdw(now);
			if (required) {
				called = rsearchdw(now);
				if (called)
				{
					tar = called > required ? called : required;
				}
				else
				{
					tar = required;
				}
			}
			else
			{
				called = rsearchdw(now);
				if (called)
				{
					tar = called;
				}
				else
				{
					required = searchup(1);
					called = rsearchup(1);
					if (required == 0 && called == 0)
					{
						if ((searchup(1)==0)&&(searchdw(14)==0)&&rsearchdw(14)==0)
						{
							if (start == 0)
							{
								time(&start);
							}
							else
							{
								time(&present);
								if (present > start + DELAY)
								{
									tar = 1;
									present = start = 0;
								}
								else
								{
									tar = now;
								}
							}
						}
						else
						{
							tar = now;
						}
					}
					else
					{
						if (required == 0 && called != 0)
						{
							tar = called;
						}
						else if (required != 0 && called == 0)
						{
							tar = required;
						}
						else
						{
							tar = required < called ? required : called;
						}
					}
				}
			}
		}//down
	}
}

void Elevator::onoff()//电梯到达特定楼层，人上下电梯
{
	//刷新当前楼层信息
	//刷新电梯内的人数和该楼层的链表（上，下）
	//刷新目标楼层
	//更改方向
	now = tar;
	people -= require[now - 1];//下
	all += require[now - 1];
	require[now - 1] = 0;
	if (stat == 1 && (searchup(now) == 0) && (searchdw(14, now) == 0) && (rsearchup(now) == 0))
	{
		stat = -1;
	}
	else if (stat == -1 && (searchdw(now) == 0) && (searchup(1, now) == 0) && (rsearchdw(now) == 0))
	{
		stat = 1;
	}
	while (people<MAX)//上
	{
		if (stat == 1)
		{
			if (floor[now - 1].up.top())
			{
				int tmp;
				if (tmp = floor[now-1].up.pop())
				{
					require[tmp - 1]++;
					people++;
					floor[now - 1].upnum--;
				}
				else
				{
					break;
				}
			}
			else
			{
				break;
			}
		}
		else
		{
			if (floor[now - 1].dw.top())
			{
				int tmp;
				if(tmp = floor[now-1].dw.pop())
				{
					require[tmp - 1]++;
					people++;
					floor[now - 1].dwnum--;
				}
				else
				{
					break;
				}
			}
			else
			{
				break;
			}
		}
	}
	nexttask();
	while (people<MAX)//上
	{
		if (stat == 1)
		{
			if (floor[now - 1].up.top())
			{
				int tmp;
				if (tmp = floor[now-1].up.pop())
				{
					require[tmp - 1]++;
					people++;
					floor[now - 1].upnum--;
				}
				else
				{
					break;
				}
			}
			else
			{
				break;
			}
		}
		else
		{
			if (floor[now - 1].dw.top())
			{
				int tmp;
				if(tmp = floor[now-1].dw.pop())
				{
					require[tmp - 1]++;
					people++;
					floor[now - 1].dwnum--;
				}
				else
				{
					break;
				}
			}
			else
			{
				break;
			}
		}
	}
}

