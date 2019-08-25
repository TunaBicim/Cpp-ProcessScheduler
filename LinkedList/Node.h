#include<iostream>

using namespace std;

class Node
{
    public:
        Node(int processID = -1, int arrivalTime = -1, int runTime = -1, int priority = -1, Node *next = NULL); //constructor 
        ~Node(){}; //destructor 
        int processID; //data items 
        int arrivalTime;
        int runTime;
        int priority;
        Node* next; //pointer to the next node 

        Node* deleteFirst(Node *head); //return the pointer of the first element to execute that process 
        void insertAfter(Node *p); //insert a new process to the list 

    private:

};
