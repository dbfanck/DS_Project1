#include "MemberQueue.h"

MemberQueue::MemberQueue()
{
    front_ptr=nullptr;
    rear_ptr=nullptr;
    cnt=0;
    capacity=0; //max queue nodes
}
MemberQueue::~MemberQueue()
{
	
}

bool MemberQueue::empty() //Is queue empty?
{
    if(cnt==0)
    {
        return true;
    }
    else
    {
        return false;
    }

}
bool MemberQueue::full() //Is queue full?
{
    if(cnt==capacity)
    {
        return true;
    }
    else
    {
        return false;
    }

}
void MemberQueue::push(MemberQueueNode* curNode)
{
	if(empty()==true)
    {
        curNode->setNext(nullptr);
        front_ptr=curNode;
        rear_ptr=curNode;
        cnt++; //count up
    }
    else if(full()==false)
    {
        curNode->setNext(nullptr);
        rear_ptr->setNext(curNode);
        rear_ptr=curNode;
        cnt++; //count up
    }
}
MemberQueueNode MemberQueue::pop()
{
    if(empty()==false)
    {
        MemberQueueNode* delNode=front_ptr;
        front_ptr=front_ptr->getNext(); //change front
        cnt--; //count down
        return *delNode;
    }
    else
    {
        exit(-1); //program end
    }
}
MemberQueueNode MemberQueue::front()
{
    return *front_ptr;
}
