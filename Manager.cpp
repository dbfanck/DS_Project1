#include "Manager.h"
#include <cstring>
using namespace std;

Manager::Manager()
{

}
Manager::~Manager()
{

}

void Manager::run(const char* command)
{
    // Open command & log file    
    fcmd.open(command);
    flog.open("log.txt");
    if (!fcmd)
    {
        flog << "Fail to open command file" << endl;
        exit(-1);
    }

    // Run command
    char cmd[100];
    fcmd.getline(cmd,100); //read commands line by line

    while(!fcmd.eof())
    {
        if (strcmp(cmd,"EXIT")==0) //exit
        {
            PrintSuccess("EXIT"); //success message
            exit(-1); //program end
        }
        else if(strcmp(cmd,"LOAD")==0) //load
        {
            LOAD();
        }
        else if(strcmp(cmd,"QPOP")==0) //qpop
        {
            QPOP();
        }
        else
        {
            char* cmd_temp=strtok(cmd," ");
        
            if(strcmp(cmd_temp,"ADD")==0) //add
            {
                cmd_temp=strtok(NULL,"\n"); //member information
                ADD(cmd_temp);
            }
            else if(strcmp(cmd_temp,"SEARCH")==0) //search
            {
                cmd_temp=strtok(NULL,"\n");
                SEARCH(cmd_temp);
            }
            else if(strcmp(cmd_temp,"PRINT")==0) //print
            {
                cmd_temp=strtok(NULL,"\n");
                PRINT(cmd_temp);
            }
	        else if(strcmp(cmd_temp,"DELETE")==0) //delete
	        {
                cmd_temp=strtok(NULL,"\n");
		        DELETE(cmd_temp);
	        }
            else //wrong command
            {
                PrintErrorCode(1000);
            }
        }

        fcmd.getline(cmd,100); //read commands line by line
    }

    fcmd.close();
    flog.close();
    return;
}

void Manager::PrintSuccess(const char* cmd)
{
    flog << "===== " << cmd << " =====" << endl;
    flog << "Success" << endl;
    flog << "===============" << endl << endl;
}
void Manager::PrintErrorCode(int num)
{
    flog << "===== ERROR =====" << endl;
    flog << num << endl;
    flog << "===============" << endl << endl;
}

// LOAD
void Manager::LOAD(void)
{
	ifstream fdata;
	char member_info[100];

	fdata.open("data.txt"); //file open

    if(!fdata || memberQueue.empty()==false) //no file or already exists queue
    {
        PrintErrorCode(100);
        return;
    }

    fdata.getline(member_info, 100); //read data line by line

    while(!fdata.eof())
    {
        MemberQueueNode* queueNode = new MemberQueueNode(member_info);	//make node&set queue data
        memberQueue.push(queueNode); //push node
        fdata.getline(member_info, 100); //read data line by line
    }

    fdata.close(); //file close

    //success load
    MemberQueueNode curNode=memberQueue.front();
    MemberQueueNode* curPtr=&curNode;

    flog << "===== LOAD =====" << endl;
    while(curPtr)
    {
        flog<<curPtr->getName()<<'/'<<curPtr->getAge()<<'/'<<curPtr->getCollectDate()<<'/'<<curPtr->getType()<<endl;
        curPtr=curPtr->getNext();
    }
    flog << "===============" << endl << endl;

}
// ADD
void Manager::ADD(char* member_info)
{
    //find error
    char member_copy[100];
    char *ptr;
    strcpy(member_copy, member_info);

    ptr=strtok(member_copy," \n");

    if(ptr==nullptr)
    {
        PrintErrorCode(200);
        return;
    }

    for(int i=0;i<3;i++)
    {
        ptr=strtok(NULL, " \n");
        if(ptr==nullptr)
        {
            PrintErrorCode(200);
            return;
        }
    }

    MemberQueueNode* queueNode = new MemberQueueNode(member_info);	//make node&set queue data
    memberQueue.push(queueNode); //push node

    //success add
    flog << "===== ADD =====" << endl;
    flog<<queueNode->getName()<<'/'<<queueNode->getAge()<<'/'<<queueNode->getCollectDate()<<'/'<<queueNode->getType()<<endl;
    flog << "===============" << endl << endl;

}

// QPOP
void Manager::QPOP(void)
{
    if(memberQueue.empty()==true) //no data
    {
        PrintErrorCode(300);
        return;
    }
    
    MemberQueueNode popNode;

    while(memberQueue.empty()==false)
    {
        popNode=memberQueue.pop(); //pop node
        termsList.insert(&popNode); //make TermsList&TermsBST
        nameBST.insert(&popNode); //make NameBST
    }

    PrintSuccess("QPOP");
}

// SEARCH
void Manager::SEARCH(char* member_name)
{
    NameBSTNode* rootNode=nameBST.getRoot();
    NameBSTNode* findNode=nameBST.search(rootNode, member_name);

    if(findNode==nullptr) //no data
    {
        PrintErrorCode(400); //print error code
        return;
    }

    //success search
    flog << "===== SEARCH =====" << endl;
    flog<<findNode->getName()<<"/"<<findNode->getAge()<<"/"<<findNode->getCollectDate()<<"/"<<findNode->getEndDate()<<endl;
    flog << "===============" << endl << endl;    

}

// PRINT
void Manager::PRINT(char* BST)
{
    if(strcmp(BST, "NAME")==0) //NameBST print
    {
        if(nameBST.getRoot()==nullptr) //no data
        {
            PrintErrorCode(500);
            return;
        }

        //success print
        flog << "===== PRINT =====" << endl;
        flog << "Name_BST" <<endl;
        nameBST.print(nameBST.getRoot(), flog);
        flog << "===============" << endl << endl;

    }
    else //TermsBST print
    {
        TermsListNode* curNode=termsList.search(BST[0]); //search TermsListNode

        if(curNode==nullptr) //no data
        {
            PrintErrorCode(500);
            return;   
        }

        TermsBST* termsBST = curNode->getBSTptr();

        //success print
        flog << "===== PRINT =====" << endl;
        flog << "Terms_BST " << BST <<endl;
        termsBST->print(termsBST->getRoot(), flog);
        flog << "===============" << endl << endl;
    }

}

// DELETE
void Manager::DELETE(char* delInfo)
{
    char* delTarget = strtok(delInfo," ");

    if(termsList.getHead()==nullptr||nameBST.getRoot()==nullptr) //no data
    {
        PrintErrorCode(600);
        return;
    }

    if(strcmp(delTarget, "NAME")==0) //NAME search
    {
        delTarget = strtok(NULL," ");
        
        NameBSTNode* searchNode = nameBST.search(nameBST.getRoot(), delTarget); //search data
        
        if(searchNode==nullptr) //search fail
        {
            PrintErrorCode(600);
            return;
        }
        else
        {
            char delName[20];
            char delDate[11];
            char delType = searchNode->getType();

            strcpy(delName, searchNode->getName());
            strcpy(delDate, searchNode->getEndDate());

            bool delBool = nameBST.del_Name(delTarget); //delete node in NameBST

            TermsBST* BSTptr = (termsList.search(delType))->getBSTptr();
            bool delBool2  = BSTptr->del_Name(delName, delDate); //delete node in TermsBST
            termsList.del_List(delType); //count down in TermsList

            PrintSuccess("DELETE");
        }
    }
    else if(strcmp(delTarget, "DATE")==0)
    {
        delTarget = strtok(NULL," ");
        
        TermsListNode* curList = termsList.getHead();
        
        while(curList)
        {
            TermsBST* BSTptr = curList->getBSTptr();
            
            BSTptr->del_Date(BSTptr->getRoot(), delTarget, &nameBST, &termsList); //delete node in TermsBST

            curList=curList->getNext();
        }
        
        PrintSuccess("DELETE");        
    }
}
