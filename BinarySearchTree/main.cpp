#include <iostream>
#include <fstream>
#include "Node.h"

using namespace std;

int main()
{
    /* reading processes from file */
    ifstream processesFile; /* input file stream */
    processesFile.open ("processes.txt");
    int numProcesses; /* number of processes */
    processesFile >> numProcesses; /* read from file */
    Node process[numProcesses]; /* create Node array */
    int processID, arrivalTime, runTime, priority;
    for(int i=0; i<numProcesses; ++i){
    /* read 4 integers from file */
    processesFile >> processID >> arrivalTime >> runTime >> priority;
    /* construct i'th element of the array */
    process[i] = Node(processID, arrivalTime, runTime, priority);
    }
    processesFile.close();
    /* end of reading from file */
	
    Node *RQ = NULL; //create the root of the Ready Queue
    int time = 0; // CPU time
    bool CPUBusy = false; // is the CPU currently running a process
    Node* currentProcess = NULL; // pointer to the process CPU is currently running
    int processIndex = 0; // Define process index to track the number of proccesses that came to that time
    int nodesVisited = 0; //Variables to keep track of number of nodes visited and searched
    int nodesSearched = 0;
    Node *prev; //Pointer to be used while searching for the next process to execute 

    while (processIndex < numProcesses || CPUBusy == true || RQ != NULL) 
    {	//While there are processes that will come or there are processes still going on or to be executed program runs
        if (processIndex < numProcesses) //If there is more processes to be read go in
        {
            if (process[processIndex].arrivalTime == time) //If the time matches the arrival time of the next proccess read it
            {
                if (RQ == NULL) //If ready queue is empty insert the process to the root 
                {
                    RQ = &process[processIndex];
                }
                else //Else insert the process to the corresponding location by the help of insert function
                {
                    RQ->Insert(RQ,&process[processIndex],nodesVisited);
                }
                processIndex++; //Increment the process index either way 
            }
        }

        if (CPUBusy == true) // CPU is running a process
        {
            currentProcess->runTime--; // 1 clock cycle elapsed
        }

        if (currentProcess != NULL && currentProcess->runTime == 0 ) // if it was last cycle of the process
        {
             cout << currentProcess->processID <<endl; // process finished execution
             CPUBusy = false; // CPU is no longer running a process
        }

        if (CPUBusy == false && RQ != NULL) // CPU is not running a process but there are processes awaiting execution
        {
            if (RQ->left == NULL && RQ->right == NULL) //if the left and right of the RQ is empty use the root as the next process
            {
                nodesSearched++; //increment the nodes searched 
                currentProcess = RQ; //update the current process 
                RQ = NULL; //update ready queue to be empty 
            }
            else //else we want to search for the smallest element by the help of search function 
            {
                prev = RQ->Search(RQ,nodesSearched); //get the node before the desired one 
                if (prev == RQ && prev->left == NULL) 
                {
                    currentProcess= RQ; //if the previous is the same as root and left is empty room is the next process
                    RQ = RQ->right; //there are items on the right so update the root to point to the right process 
                }
                else 
                {
                    currentProcess = prev->left;       // select new process and remove it from RQ
                    if (prev->left->right != NULL)    //if there are items to the right of the process we need to connect them
                    {
                        prev->left = prev->left->right; //put that branch to the left of the prev
                    }
                    else //if there are no items simply update the left of the prev to be NULL 
                    {
                        prev->left = NULL;
                    }

                }
            }
            CPUBusy = true; // CPU is now running a process
        }
        time++; //increment time after 1 execution of the while loop
    }
    cout << endl <<nodesSearched << " nodes visited for searching"<< endl; //After all processes are served display 
    cout << nodesVisited << " nodes visited for insertion"<< endl;		   // the number of nodes searched and visited
    return 0;
}
