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
	
    Node *RQ; //Create the Ready Queue pointer
    RQ = new Node; //Create the head of the Ready Queue
    int time = 0; // CPU time
    bool CPUBusy = false; // is the CPU currently running a process
    Node* currentProcess = NULL; // pointer to the process CPU is currently running
    int processIndex = 0; // Define process index to track the number of proccesses that came to that time
    int nodesVisited = 0; //Variables to keep track of number of nodes visited and searched
    int nodesSearched = 0;
	Node *curr; //Temp pointer to be used when traversing the list
	
    while (processIndex < numProcesses || RQ->next != NULL || CPUBusy == true) 
    { //While there are processes that will come or there are processes still going on or to be executed program runs
        if (processIndex < numProcesses) //If there is more processes to be read go in
        {
            if (process[processIndex].arrivalTime == time) //If the time matches the arrival time of the next proccess read it
            {
                if (RQ->next==NULL) //If ready queue is empty insert the process after the head 
                {
                    RQ->insertAfter(&process[processIndex]);
                    nodesVisited++;
                }
                else //Else traverse the list to find the appopriate place according to the priority 
                {   curr = RQ;
                    while (curr->next != NULL && (curr->next->priority < process[processIndex].priority))
                    {
                        curr = curr->next; //While the priority of the process is bigger than the next node traverse 
                        nodesVisited++; //Increments number of nodes visited 
                    }
                    curr->insertAfter(&process[processIndex]); //After the traversal insert the new process 
                    nodesVisited++; //Increments number of nodes visited
                }
                processIndex++; //After reading the process increment the index
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

        if (CPUBusy == false && RQ->next != NULL) // CPU is not running a process but there are processes awaiting execution
        {
            currentProcess = RQ->deleteFirst(RQ); // select new process and remove it from RQ
            nodesSearched++; //since the process we select is always the first one increment once 
            CPUBusy = true; // CPU is now running a process
        }
        time++; //increment time after 1 execution of the while loop
    }
    cout << endl <<nodesSearched << " nodes visited for searching"<< endl; //After all processes are served display 
    cout << nodesVisited << " nodes visited for insertion"<< endl;         // the number of nodes searched and visited
    return 0;
}
