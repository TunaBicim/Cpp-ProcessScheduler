#include "Node.h"

Node::Node(int ProcessID, int ArrivalTime, int RunTime, int Priority, Node *Left, Node *Right) //constructor 
{
    processID = ProcessID; //Set data values 
    arrivalTime = ArrivalTime;
    runTime = RunTime;
    priority = Priority;
    left = Left;
    right = Right;
    return;
}


Node* Node::Search(Node *head,int &nodesSearched)
{
    nodesSearched++; //increment the number of searched nodes 
    Node *prev = head; //keep previous and current values 
    Node *temp = head;
    while (temp->left != NULL) //Since this is a binary search tree the item we want is always the left most one 
    {
        prev = temp; //update the pointers while searching for the smallest number 
        temp = temp->left;
        nodesSearched++; //increment the number of searched nodes 
    }
    return prev; //return the previous pointer so that we can update the branches coming out of the lowest priority process 
}


Node* Node::Insert(Node *head , Node *item, int &nodesVisited)
{
    nodesVisited++; //increment the number of nodes visited 
    if (item->priority < head->priority) //if the item has a smaller priority go left 
    {
        if (head->left ==NULL) //if the left is empty insert the item 
        {
            head->left = item;
            nodesVisited++;
            return item;
        } //else recursively look for the next left 
        this->Insert(head->left,item,nodesVisited);
    } else //else go right 
    {
        if (head->right ==NULL) //if the right is empty insert the item 
        {
            head->right = item;
            nodesVisited++;
            return item;
        } //else recursively look for the next right 
        this->Insert(head->right,item,nodesVisited); // Key is smaller than root's key
    }
    return item; //the compiler can't interpret logic as humans so it thinks we might reach the end without returning so this 
}                //return is here to make the warning disappear 




