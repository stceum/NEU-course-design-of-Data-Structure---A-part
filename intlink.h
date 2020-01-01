#pragma once

typedef struct NODE {
	int data;
	NODE* next;
}NODE;

class Link
{
public:
	Link(int a)
	{
		this->order=a;
		head = nullptr;
	}
	void insert(int num);
	int pop();
	int top();
private:
	int order;//±ê¼ÇÉý½µÐò 0/1
	NODE* head;
};