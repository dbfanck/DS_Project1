#include "NameBST.h"

NameBST::NameBST() : root(nullptr)
{

}
NameBST::~NameBST()
{

}

NameBSTNode* NameBST::getRoot()
{
	return root;
}

// insert
void NameBST::insert(MemberQueueNode* popNode)
{
	NameBSTNode* newNode = new NameBSTNode(popNode); //make node

	NameBSTNode* pp=nullptr;
	NameBSTNode* p=root;
	
	while(p)
	{
		pp=p;
	
		if(strcmp(newNode->getName(), p->getName())<0) //newNode end_date is smaller
		{
			p=p->getLeft();
		}
		else
		{
			p=p->getRight();
		}
	}

	p=newNode;

	if(root!=nullptr)
	{
		if(strcmp(p->getName(), pp->getName())<0) //newNode end_date is smaller
		{
			pp->setLeft(p); //set left child
		}
		else
		{
			pp->setRight(p); //set right child
		}
	}
	else //no node
	{
		root=p;
	}

}

// search
NameBSTNode* NameBST::search(NameBSTNode* curNode, char* key_name)
{
	if(curNode==nullptr)
	{
		return nullptr;
	}

	if(strcmp(key_name, curNode->getName())<0)
	{
		return search(curNode->getLeft(), key_name); //move left child
	}

	if(strcmp(key_name, curNode->getName())>0)
	{
		return search(curNode->getRight(), key_name); //move right child
	}

	if(strcmp(key_name, curNode->getName())==0) //find key_name
	{
		return curNode;
	}
}

// print
void NameBST::print(NameBSTNode* curNode, ofstream& flog)
{
	if(curNode!=nullptr)
	{
		print(curNode->getLeft(), flog); //left child visit
		flog<<curNode->getName()<<"/"<<curNode->getAge()<<"/"<<curNode->getCollectDate()<<"/"<<curNode->getEndDate()<<endl;
		print(curNode->getRight(), flog); //right child visit
	}	
}

// delete
bool NameBST::del_Name(char* del_name)
{
	NameBSTNode* p = root, *q=nullptr;

	while(p && strcmp(del_name,p->getName())!=0) //find node
	{
		q=p;
		if(strcmp(del_name,p->getName())<0) //del_name is smaller
		{
			p=p->getLeft();
		}
		else //del_name is greater
		{
			p=p->getRight();
		}
	}

	if(p==0) //search fail
	{
		return false;
	}

	if(p->getLeft()==nullptr && p->getRight()==nullptr) //p is leaf node
	{
		if(q==0) //one node tree
		{
			root=nullptr;
		}
		else if(q->getLeft()==p)
		{
			q->setLeft(nullptr); //delete
		}
		else
		{
			q->setRight(nullptr); //delete
		}

		delete p; //delete node
		return true;
	}

	if(p->getLeft()==nullptr) //p has only right child
	{
		if(q==0)
		{
			root=p->getRight(); //delete
		}
		else if(q->getLeft()==p)
		{
			q->setLeft(p->getRight()); //delete
		}
		else
		{
			q->setRight(p->getRight()); //delete
		}

		delete p; //delete node
		return true;
	}

	if(p->getRight()==nullptr) //p has only left child
	{
		if(q==0)
		{
			root=p->getLeft(); //delete
		}
		else if(q->getLeft()==p)
		{
			q->setLeft(p->getLeft()); //delete
		}
		else
		{
			q->setRight(p->getLeft()); //delete
		}

		delete p; //delete node
		return true;
	}

	//p has left and right child
	NameBSTNode *prevprev=p, *prev=p->getRight(), *curr=(p->getRight())->getLeft();

	//find smallest node in right subtree
	while(curr)
	{
		prevprev=prev;
		prev=curr;
		curr=curr->getLeft();
	}

	p->setName(prev->getName());
	p->setAge(prev->getAge());
	p->setCollectDate(prev->getCollectDate());
	p->setEndDate(prev->getEndDate());
	p->setType(prev->getType());

	if(prevprev==p)
	{
		prevprev->setRight(prev->getRight());		
	}
	else
	{
		prevprev->setLeft(prev->getRight());
	}

	delete prev;
	return true;
}