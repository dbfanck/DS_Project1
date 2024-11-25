#pragma once
#include "MemberQueueNode.h"
#include <iostream>

class MemberQueue
{
private:
	MemberQueueNode* front_ptr;
	MemberQueueNode* rear_ptr;
	int cnt;
	int capacity;

public:
	MemberQueue();
	~MemberQueue();

	bool empty();
	bool full();
	void push(MemberQueueNode* curNode);
	MemberQueueNode pop();
	MemberQueueNode front();

};

