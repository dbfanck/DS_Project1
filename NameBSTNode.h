#pragma once
#include "MemberQueueNode.h"

class NameBSTNode
{
private:

	char name[21]; //name
	char age[3]; //age
	char collect_date[11]; //data collect date
	char end_date[11]; //data end date
	char type; //type

	NameBSTNode*	left;
	NameBSTNode*	right;
	

public:
	NameBSTNode(MemberQueueNode* popNode)
	{
		strcpy(this->name,popNode->getName());
		strcpy(this->age,popNode->getAge());
		strcpy(this->collect_date,popNode->getCollectDate());
		this->type=popNode->getType();
		calEndDate(this->type);

		left=right=nullptr;
	}
	~NameBSTNode() {}

	void calEndDate(char type)
	{
		strcpy(this->end_date,this->collect_date);

		int year=(end_date[0]-'0')*1000+(end_date[1]-'0')*100+(end_date[2]-'0')*10+(end_date[3]-'0');
		int month=(end_date[5]-'0')*10+(end_date[6]-'0');

		if(type=='A')
		{
			month+=6;
			if(month-12>0)
			{
				month-=12;
				year++;
			}
		}
		else if(type=='B')
		{
			year++;
		}
		else if(type=='C')
		{
			year+=2;
		}
		else
		{
			year+=3;
		}

		//set end date

		end_date[0]=(year/1000)+'0';
		year=year%1000;
		end_date[1]=(year/100)+'0';
		year=year%100;
		end_date[2]=(year/10)+'0';
		end_date[3]=(year%10)+'0';

		end_date[5]=(month/10)+'0';
		end_date[6]=(month%10)+'0';
	}

	NameBSTNode*	getLeft()			{ return left; }
	NameBSTNode*	getRight()			{ return right; }
	char* getName() { return name; }
	char* getAge() { return age; }
	char* getCollectDate() { return collect_date; }
	char* getEndDate() { return end_date; }
	char getType() { return type; }

	void setLeft(NameBSTNode* left)						{ this->left = left; }
	void setRight(NameBSTNode* right)					{ this->right = right; }
	void setName(char* name) { strcpy(this->name, name); }
	void setAge(char* age) { strcpy(this->age, age); }
	void setCollectDate(char* collect_date) { strcpy(this->collect_date, collect_date); }
	void setEndDate(char* end_date) { strcpy(this->end_date, end_date); }
	void setType(char type) { this->type=type; }
};