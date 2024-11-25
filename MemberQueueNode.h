#pragma once
#include <cstring>
 
using namespace std;

class MemberQueueNode
{
private:
	char name[21]; //member name
	char age[3]; //member age
	char collect_date[11]; //data collect date
	char type; //type
	MemberQueueNode* pNext;

public:

	MemberQueueNode() {}

	MemberQueueNode(char member_info[100])
	{
		//set queue data
		char* member_temp;
		
		member_temp=strtok(member_info," ");
		setName(member_temp);

		member_temp=strtok(NULL," ");
		setAge(member_temp);

		member_temp=strtok(NULL," ");
		setCollectDate(member_temp);

		member_temp=strtok(NULL," ");
		setType(member_temp[0]);
	}
	~MemberQueueNode() {}

	void setName(char* name)
	{
		strcpy(this->name,name);
	}

	void setAge(char* age)
	{
		strcpy(this->age, age);
	}

	void setCollectDate(char* collect_date)
	{
		strcpy(this->collect_date, collect_date);
	}

	void setType(char type)
	{
		this->type=type;
	}

	void setNext(MemberQueueNode* pNext)
	{
		this->pNext=pNext;
	}

	char* getName(void)
	{
		return name;
	}

	char* getAge(void)
	{
		return age;
	}

	char* getCollectDate(void)
	{
		return collect_date;
	}

	char getType(void)
	{
		return type;
	}

	MemberQueueNode* getNext(void)
	{
		return pNext;
	}

};
