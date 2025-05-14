/*=============================================================================
 * Title        : assignment_5.cpp
 * Description  : This program implements 6 scheduling algorithms: FCFS, RR, SPN, SRT, HRRN, FEEDBACK
 *                First it stores the processes to a ready queue as a nested queue, then fetches that queue to the schedulers.
 * Author       : Halmuhammet Muhamedorazov
 * Date         : 01/01/2001Version : 1.0
 * Usage        : Compile and run this program using the GNUC++ compiler
 * Notes        : This program has no requirements.
 * C++ Version  :
 * =============================================================================*/

//import the necessary libraries

#include <iostream>
#include <fstream>
#include <deque>
#include <sstream>
#include <cmath>
#include <algorithm>
#include <vector>
using namespace std;

//Use deque data structure because it has a combination of vector and queue.
//It gives the convenience of indexing and pushing or popping elements in the queue.

deque <deque<string>> processes;

//This function is used in the built-in sorting function for the process service time.
// It checks whether number a is less than number b.

bool compareServiceTime(const deque<string>& a, const deque<string>& b){
    // Convert Service times from string to int for comparison
    int arrivalTimeA = stoi(a[2]);
    int arrivalTimeB = stoi(b[2]);
    return arrivalTimeA < arrivalTimeB;
}

//This function is used in the built-in sorting function for the process response ration.
//It checks whether number a is greater than number b.

bool compareHighestResponseRatio(const deque<string>& a, const deque<string>& b){
    // Convert response ratio from string to double for comparison
    double hrrA = stod(a[4]);
    double hrrB = stod(b[4]);
    return hrrA > hrrB;
}

// This function is used in the built-in sorting function for the arrival time.
// It checks whether number a is less than number b

bool compareArrivalTime(const deque<string>& a, const deque<string>& b) {
    // Convert arrival times from string to int for comparison
    int arrivalTimeA = stoi(a[1]);
    int arrivalTimeB = stoi(b[1]);
    return arrivalTimeA < arrivalTimeB;
}

// First Come, First Served scheduler function selects the process in front of the ready queue
// and serves it until it finishes its job. The time quantum is 10ms.

void fcfs(deque<deque<string>> readyQueue){

    //open the output file for writing
    ofstream FCFS_output_file;
    string filepath = "C:\\Users\\muhsm\\CLionProjects\\assignment_5\\fcfs.out";
    FCFS_output_file.open(filepath);

    //loop through each processes in the ready queue
    for(int i = 0; i < readyQueue.size(); i++){

        //get the time quantum required to finish the selected job
        int timeQuantum = int(ceil(stod(readyQueue[i][2])/10.0));

        //print the process on its own line to represent each 10ms time quantum
        for(int j = 0; j < timeQuantum; j++){
            FCFS_output_file<< readyQueue[i][0]<<endl;
        }
    }
}

//This function implements Round Robin scheduling algorithm.
//It adds processes to the ready queue based on their arrival time.
//It then serves for time quantum of 10ms and determines to remove it from the
//queue or to add it to the back of ready queue.

void rr10(deque<deque<string>> process_queue){
    //open the output file for writing
    ofstream RR10_output_file;
    string filepath = "C:\\Users\\muhsm\\CLionProjects\\assignment_5\\rr_10.out";
    RR10_output_file.open(filepath);

    deque <deque<string>> ready; // use a ready queue for process arrival
    //initialize the queue with the first processes arrived
    for (int i = 0; i < process_queue.size(); i++) {
            if (stoi(process_queue[i][1]) == 0) {
                ready.push_back(process_queue[i]);
            }
        }
    // set the clock time to 0
    int wall_clock_time = 0;
    //use loop to implement the Round Robin scheduling algorithm
    while(true) {
        //write the process identifier to the file
        RR10_output_file << ready.front()[0]<< endl;
        //in each loop, decrease the process's service time by 10
        int serviceTimeOfFrontReadyQueue = stoi(ready.front()[2]);
        int remainingServiceTimeOfFrontReadyQueue = serviceTimeOfFrontReadyQueue - 10;
        ready.front()[2] = to_string(remainingServiceTimeOfFrontReadyQueue);
        //increase the clock time by 10 each time a processes gets served in 10 time quantum
        wall_clock_time += 10;
        //loop through and check if any processes arrived at the current clock time
        //if yes, add it to the ready queue
        for (int i = 0; i < process_queue.size(); i++) {
            if (stoi(process_queue[i][1]) == wall_clock_time) {
                ready.push_back(process_queue[i]);
            }
        }
        //if the remaining service time of the process in the ready queue becomes 0, then remove it
        if(remainingServiceTimeOfFrontReadyQueue <= 0){
            ready.pop_front();
        }else{//otherwise, push it to the back of ready queue
            deque <string> frontElement = ready.front();
            ready.pop_front();
            ready.push_back(frontElement);
        }
        //check if the ready queue is empty. And if it is, break the Round Robin algorithm
        if(ready.empty()){
            break;
        }
    }
}

//Similar to the above function, except with time quantum of 40ms.
//This function implements Round Robin scheduling algorithm.
//It adds processes to the ready queue based on their arrival time.
//It then serves for time quantum of 40ms and determines whether to remove it from the
//queue or to add it to the back of ready queue based on remaining service time.

void rr40(deque<deque<string>> process_queue){
    //open the output file for writing
    ofstream RR40_output_file;
    string filepath = "C:\\Users\\muhsm\\CLionProjects\\assignment_5\\rr_40.out";
    RR40_output_file.open(filepath);

    deque <deque<string>> ready; // use a ready queue for process arrival
    //populate/initialize the queue with the first processes arrived
    for (int i = 0; i < process_queue.size(); i++) {
        //get the arrival time of a process and check if it is 0
        //if zero, push that process to the ready queue
        if (stoi(process_queue[i][1]) == 0) {
            ready.push_back(process_queue[i]);
        }
    }
    // set the clock time to 0
    int wall_clock_time = 0;
    //use loop to implement the Round Robin scheduling algorithm
    while(true) {
        //get how much time quantum is required to finish the job
        int timeQuantum = int(ceil(stod(ready.front()[2])/10.0));
        //if the process requires time quantum of more than 4,
        //then serve the process for 4 time quantum and
        //push the process to the back of the queue
        if(timeQuantum > 4){
            //print the process on its own line to represent each 10ms time quantum
            for(int i = 0; i < 4; i++){
                //write the process identifier to the file
                RR40_output_file << ready.front()[0]<< endl;
                //increase the clock time by 10 each time a processes gets served in 10 time quantum
                wall_clock_time += 10;
                //loop through and check if any processes arrived at the current clock time
                //if yes, add it to the ready queue
                for (int i = 0; i < process_queue.size(); i++) {
                    if (stoi(process_queue[i][1]) == wall_clock_time) {
                        ready.push_back(process_queue[i]);
                    }
                }
            }
        }else{
            for(int j = 0; j < timeQuantum; j++){
                RR40_output_file << ready.front()[0]<< endl;
                //increase the clock time by 10 each time a processes gets served in 10 time quantum
                wall_clock_time += 10;
                //loop through and check if any processes arrived at the current clock time
                //if yes, add it to the ready queue
                for (int i = 0; i < process_queue.size(); i++) {
                    if (stoi(process_queue[i][1]) == wall_clock_time) {
                        ready.push_back(process_queue[i]);
                    }
                }
            }
        }


        //in each loop, decrease the process's service time by 40
        int serviceTimeOfFrontReadyQueue = stoi(ready.front()[2]);
        int remainingServiceTimeOfFrontReadyQueue = serviceTimeOfFrontReadyQueue - 40;
        ready.front()[2] = to_string(remainingServiceTimeOfFrontReadyQueue);

        //if the remaining service time of the process in the ready queue becomes 0, then remove it
        if(remainingServiceTimeOfFrontReadyQueue <= 0){
            ready.pop_front();
        }else{//otherwise, push it to the back of ready queue
            deque <string> frontElement = ready.front();
            ready.pop_front();
            ready.push_back(frontElement);
        }
        //check if the ready queue is empty. And if it is, break the Round Robin algorithm
        if(ready.empty()){
            break;
        }
    }
}

//Shortest Process Next scheduling algorithm selects the process with the shortest service time
//After the selected process is finished, SPN makes the decision to select the process with the shortest service time

void spn(deque<deque<string>> process_queue){
    //open the output file for writing
    ofstream SPN_output_file;
    string filepath = "C:\\Users\\muhsm\\CLionProjects\\assignment_5\\spn.out";
    SPN_output_file.open(filepath);

    deque <deque<string>> ready; // use a ready queue for process arrival
    //initialize the queue with the first processes arrived
    for (int i = 0; i < process_queue.size(); i++) {
        if (stoi(process_queue[i][1]) == 0) {
            ready.push_back(process_queue[i]);
        }
    }
    //sort the queue by having the process with the shortest service time at the top of queue
    sort(ready.begin(), ready.end(), compareServiceTime);

    // set the clock time to 0
    int wall_clock_time = 0;

    while(true){
        //get the time quantum required to finish the selected job
        int timeQuantum = int(ceil(stod(ready.front()[2]) / 10.0));

        //print the process on its own line to represent each 10ms time quantum
        for (int j = 0; j < timeQuantum; j++) {
            SPN_output_file << ready.front()[0] << endl;
            wall_clock_time += 10;
            //check if any new processes arrived in the ready queue
            for (int i = 0; i < process_queue.size(); i++) {
                if (stoi(process_queue[i][1]) == wall_clock_time) {
                    ready.push_back(process_queue[i]);
                }
            }
        }
        //remove the front process in the queue since it has finished its job
        ready.pop_front();
        //sort the next process to select by the shortest service time
        sort(ready.begin(), ready.end(), compareServiceTime);
        //if the ready queue is empty, break the loop and terminate the SPN algorithm
        if(ready.empty()){
            break;
        }
    }
}

//Shortest Remaining Time scheduling algorithm selects makes the decision to select a process whenever a new process
//arrives at the ready queue. It selects the process with the shortest service time.

void srt(deque<deque<string>> process_queue){
    //open the output file for writing
    ofstream SRT_output_file;
    string filepath = "C:\\Users\\muhsm\\CLionProjects\\assignment_5\\srt.out";
    SRT_output_file.open(filepath);

    deque <deque<string>> ready; // use a ready queue for process arrival
    //initialize the queue with the first processes arrived
    for (int i = 0; i < process_queue.size(); i++) {
        if (stoi(process_queue[i][1]) == 0) {
            ready.push_back(process_queue[i]);
        }
    }
    //sort the queue by having the process with the shortest service time at the top of queue
    sort(ready.begin(), ready.end(), compareServiceTime);

    // set the clock time to 0
    int wall_clock_time = 0;

    while(true){
        bool newProcessArrivedFlag = false;

        //get the time quantum required to finish the selected job
        int timeQuantum = int(ceil(stod(ready.front()[2]) / 10.0));

        //print the process on its own line to represent each 10ms time quantum
        for (int j = 0; j < timeQuantum; j++) {
            SRT_output_file << ready.front()[0] << endl;
            wall_clock_time += 10;

            //check if any new processes arrived in the ready queue at this time
            for (int i = 0; i < process_queue.size(); i++) {
                if (stoi(process_queue[i][1]) == wall_clock_time) {
                    ready.push_back(process_queue[i]);
                    newProcessArrivedFlag = true;
                }
            }

            //in each loop, decrease the process's service time by 10
            int serviceTimeOfFrontReadyQueue = stoi(ready.front()[2]);
            int remainingServiceTimeOfFrontReadyQueue = serviceTimeOfFrontReadyQueue - 10;
            ready.front()[2] = to_string(remainingServiceTimeOfFrontReadyQueue);

            //if the remaining service time of the process in the ready queue becomes 0, then remove it
            if(remainingServiceTimeOfFrontReadyQueue <= 0) {
                ready.pop_front();
            }
            //use a flag to break the loop if a new process arrived in the ready queue because a new decision is required
            //to select a process to serve
            if(newProcessArrivedFlag == true){
                break;
            }
        }
        //sort the processes by the shortest service time
        sort(ready.begin(), ready.end(), compareServiceTime);

        //if the ready queue is empty, break the loop and terminate the SRT algorithm
        if(ready.empty()){
            break;
        }
    }
}

//Highest Response Ratio selects a process using the following formula: (wait_time + service_time)/service_time
//Once a process is selected, it gets to run with no preemption.

void hrrn(deque<deque<string>> process_queue){
    //open the output file for writing
    ofstream HRRN_output_file;
    string filepath = "C:\\Users\\muhsm\\CLionProjects\\assignment_5\\hrrn.out";
    HRRN_output_file.open(filepath);

    //populate/initialize the wait time and response ratio of each process
    for(int i = 0; i < process_queue.size(); i++){
        process_queue[i].push_back("0");
        process_queue[i].push_back(("1"));
    }

    deque <deque<string>> ready; // use a ready queue for process arrival
    //initialize the queue with the first processes arrived
    for (int i = 0; i < process_queue.size(); i++) {
        if (stoi(process_queue[i][1]) == 0) {
            ready.push_back(process_queue[i]);
        }
    }

    //to break the tie, sort the queue by having the process with the shortest arrival time at the top of queue
    sort(ready.begin(), ready.end(), compareArrivalTime);

    // set the clock time to 0
    int wall_clock_time = 0;

    while(true){
        //get the time quantum required to finish the selected job
        int timeQuantum = int(ceil(stod(ready.front()[2]) / 10.0));

        //print the process on its own line to represent each 10ms time quantum
        for (int j = 0; j < timeQuantum; j++) {
            //print out the process identifier on its corresponding time quantum line
            HRRN_output_file << ready.front()[0] << endl;
            //increment the time wall clock time by 10
            wall_clock_time += 10;

            //check if any new processes arrived to the ready queue by this time
            for (int i = 0; i < process_queue.size(); i++) {
                if (stoi(process_queue[i][1]) == wall_clock_time) {
                    ready.push_back(process_queue[i]);
                }
            }

            //update the wait and response ratio of each process in the ready queue
            for(int i = 1; i < ready.size(); i++){
                //convert the wait time, service time, and response ratio to double to perform math operations
                double wait_time = stod(ready[i][3]);
                double service_time = stod(ready[i][2]);
                double response_ratio = (wait_time + service_time)/service_time;

                //important we update the wait time of processes after the response ratio is calculated
                //because these new jobs just arrived and has not waited yet.
                // So the old wait time needs to be used in the response ratio calculation
                wait_time += 10;

                //convert the wait time and response ratio to string to write them to string type queue
                ready[i][3] = to_string(wait_time);
                ready[i][4] = to_string(response_ratio);
            }
        }
        //remove the front process from the queue since its job is done
        ready.pop_front();
        //sort the queue by having the process with the highest response ratio at the top of the queue
        sort(ready.begin(), ready.end(), compareHighestResponseRatio);

        //check if the queue is empty; if so, break the loop and terminate the hrrn algorithm
        if(ready.empty()){
            break;
        }
    }
}

void feedback_helper(vector <deque <deque<string>>>& priority_queue, deque<deque<string>> process_queue,
                     ofstream& FEEDBACK_output_file,int wall_clock_time, int number_of_queue){

    for(int i = 0; i < priority_queue.size(); i++){
        while(!priority_queue[i].empty()){
            //write the process identifier to the file
            FEEDBACK_output_file << priority_queue[i].front()[0]<< endl;
            //in each loop, decrease the process's service time by 10
            int serviceTimeOfFrontProcess = stoi(priority_queue[i].front()[2]);
            int remainingServiceTimeOfFrontProcess = serviceTimeOfFrontProcess - 10;
            //update the remaining service time
            priority_queue[i].front()[2] = to_string(remainingServiceTimeOfFrontProcess);
            //increase the clock time by 10 each time a processes gets served in 10 time quantum
            wall_clock_time += 10;
            bool newProcessArrived = false;
            //loop through and check if any processes arrived at the current clock time
            //if yes, add it to the back of first priority queue
            for (int i = 0; i < process_queue.size(); i++) {
                if (stoi(process_queue[i][1]) == wall_clock_time) {
                    priority_queue[0].push_back(process_queue[i]);
                    newProcessArrived = true;
                }
            }
            //if the remaining service time of the process in the ready queue becomes 0, then remove it
            if(remainingServiceTimeOfFrontProcess <= 0){
                priority_queue[i].pop_front();
            }else{//otherwise, push it to the back of the next lower priority queue
                deque <string> frontElement = priority_queue[i].front();
                priority_queue[i].pop_front();
                //if the process sits at the last priority queue and wants to run more,
                //then push it to the back of the queue it is sitting
                //otherwise, push it to the back of the next lower priority queue
                if(i != number_of_queue){
                    priority_queue[i+1].push_back(frontElement);
                }else{
                    priority_queue[i].push_back(frontElement);
                }
            }
            if(newProcessArrived == true){
                feedback_helper(priority_queue, process_queue, FEEDBACK_output_file, wall_clock_time, number_of_queue);
            }
        }
    }
}


void feedback(deque<deque<string>> process_queue){
    //open the output file for writing
    ofstream FEEDBACK_output_file;
    string filepath = "C:\\Users\\muhsm\\CLionProjects\\assignment_5\\feedback.out";
    FEEDBACK_output_file.open(filepath);

    //contain multiple queues inside a vector
    int number_of_queue = 30;
    vector <deque <deque<string>>> priority_queue(number_of_queue);

    //initialize the first priority queue with the processes that arrive at time zero
    for(int i = 0; i < process_queue.size(); i++){
        if(stoi(process_queue[i][1]) == 0){
            priority_queue[0].push_back(process_queue[i]);
        }
    }

    // set the clock time to 0
    int wall_clock_time = 0;

    for(int i = 0; i < priority_queue.size(); i++){
        while(!priority_queue[i].empty()){
            //write the process identifier to the file
            FEEDBACK_output_file << priority_queue[i].front()[0]<< endl;
            //in each loop, decrease the process's service time by 10
            int serviceTimeOfFrontProcess = stoi(priority_queue[i].front()[2]);
            int remainingServiceTimeOfFrontProcess = serviceTimeOfFrontProcess - 10;
            //update the remaining service time
            priority_queue[i].front()[2] = to_string(remainingServiceTimeOfFrontProcess);
            //increase the clock time by 10 each time a processes gets served in 10 time quantum
            wall_clock_time += 10;
            bool newProcessArrived = false;
            //loop through and check if any processes arrived at the current clock time
            //if yes, add it to the back of first priority queue
            for (int i = 0; i < process_queue.size(); i++) {
                if (stoi(process_queue[i][1]) == wall_clock_time) {
                    priority_queue[0].push_back(process_queue[i]);
                    newProcessArrived = true;
                }
            }
            //if the remaining service time of the process in the ready queue becomes 0, then remove it
            if(remainingServiceTimeOfFrontProcess <= 0){
                priority_queue[i].pop_front();
            }else{//otherwise, push it to the back of the next lower priority queue
                deque <string> frontElement = priority_queue[i].front();
                priority_queue[i].pop_front();
                //if the process sits at the last priority queue and wants to run more,
                //then push it to the back of the queue it is sitting
                //otherwise, push it to the back of the next lower priority queue
                if(i != number_of_queue){
                    priority_queue[i+1].push_back(frontElement);
                }else{
                    priority_queue[i].push_back(frontElement);
                }
            }
            if(newProcessArrived == true){
                feedback_helper(priority_queue, process_queue, FEEDBACK_output_file, wall_clock_time, number_of_queue);
            }
        }
    }
}

int main() {
    string filepath = "C:\\Users\\muhsm\\CLionProjects\\assignment_5\\input.in";
    ifstream input_file;
    // open the file
    input_file.open(filepath);
    // check if the file exists and opened successfully
    if (!input_file.is_open()) {
        cerr << "Error: Unable to open the file '" << filepath << "'" << endl;
        return 1; // if not opened successfully, return non-zero to show failure to open the file
    }

    string line;
    //read the file line by line
    while (getline(input_file, line)) {
        istringstream lineToSplit(line);
        string tokenInLine;
        deque <string> process;
        //separate (by tabs) the tokens in the line into elements in queue
        while (getline(lineToSplit, tokenInLine, '\t')) {
            process.push_back(tokenInLine);
        }
        processes.push_back(process);
    }
    // sort the processes based on their arrival time
    sort(processes.begin(), processes.end(), compareArrivalTime);

    fcfs(processes);
    rr10(processes);
    rr40(processes);
    spn(processes);
    srt(processes);
    hrrn(processes);
    feedback(processes);

    for(int i = 0; i < processes.size(); i++) {
        for (int j = 0; j < processes[i].size(); j++) {
            cout << processes[i][j] << "\t";
        }
        cout << endl;
    }

    //close the file
    input_file.close();
    return 0;
}
