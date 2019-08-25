#include "Node.h"

Node::Node(int ProcessID, int ArrivalTime, int RunTime, int Priority, Node *Next)
{
    processID = ProcessID; //Set data values provided 
    arrivalTime = ArrivalTime;
    runTime = RunTime;
    priority = Priority;
    next = Next; 
    return;
}

Node* Node::deleteFirst(Node *head)
{
    Node* temp = head->next; //Since the process we want is always at the front we delete the first element in the list 
    head->next=temp->next;   //keep the task in temp to return and update the head to point to the next process 
    return temp;             //Return the task to be done 
}


void Node::insertAfter(Node *p)
{
    p->next = next; //Insert the process after the current node 
    next=p; //Update the next pointer of the current node 
    return; 
}

