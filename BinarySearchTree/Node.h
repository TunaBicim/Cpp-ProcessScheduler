#include<iostream>

using namespace std;

class Node
{
    public:
        Node(int processID = -1, int arrivalTime = -1, int runTime = -1, 
			 int priority = -1, Node *left = NULL, Node *right = NULL); //constructor 
        ~Node(){}; //destructor 
        int processID; //data items 
        int arrivalTime;
        int runTime;
        int priority;
        Node* left;
        Node* right;
		
        Node* Search(Node *head,int &nodesSearched); //Search and return the next process to be executed 
        Node* Insert(Node *head , Node *item, int &nodesVisited); //Insert the newly arrived process to the tree 
    private:


};

