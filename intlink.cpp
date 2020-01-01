#include "intlink.h"
void Link::insert(int num)
{
	if (head == nullptr)
	{
		head = new NODE;
		head->data = num;
		head->next = nullptr;
	}
	else
	{
		if (order == 0)//ÉıĞò
		{
			if (head->data > num) {
				NODE* n = new NODE;
				n->data = num;
				n->next = head;
				head = n;
				return;
			}
			NODE* tmp = head;
			NODE* pre = head;
			while (tmp->next && tmp->data < num)
			{
				pre = tmp;
				tmp = tmp->next;
			}
			NODE* n = new NODE;
			n->data = num;
			n->next = pre->next;
			pre->next = n;
		}
		else
		{
			if (head->data < num) {
				NODE* n = new NODE;
				n->data = num;
				n->next = head;
				head = n;
				return;
			}
			NODE* tmp = head;
			NODE* pre = head;
			while (tmp->next && tmp->data > num)
			{
				tmp = tmp->next;
			}
			NODE* n = new NODE;
			n->data = num;
			n->next = pre->next;
			pre->next = n;
		}
	}
}

int Link::pop()
{
	if (head == nullptr)
	{
		return 0;
	}
	else
	{
		int tmp = head->data;
		NODE* cl = head;
		head = head->next;
		delete cl;
		return tmp;
	}
	return 0;
}

int Link::top()
{
	if (head == nullptr)
	{
		return 0;
	}
	else
	{
		return head->data;
	}
}
