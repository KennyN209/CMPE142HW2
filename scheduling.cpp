#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>
using namespace std;

struct process
{
    char name;
    int arrival;
    int burst;
    bool here = 0;
    void print()
    {
        int pos = name - 'A';
        for (int i = 0; i < pos; i++)
            cout << " \t";
        cout << "X\n";
    }
};
//a function to get the total work time of the CPU
int tot_time(vector<process> jobs)
{
    int sum = 0;
    for (int i = 0; i < jobs.size(); i++)
    {
        sum += jobs[i].burst;
    }
    return sum;
}
//printer
void printHeaders(vector<process> jobs)
{
    for (int i = 0; i < jobs.size(); i++)
        cout << jobs[i].name << "\t";
    cout << endl;
}
//it goeos second by second and prints checks which process should go next and print it
void FCFS(vector<process> jobs)
{
    printHeaders(jobs);
    sort(jobs.begin(), jobs.end(), [](process a, process b)
         {
             return a.arrival < b.arrival;
             
         });
    int tot = tot_time(jobs);
    for (int i = 0; i < jobs.size(); i++)
    {
        for (int j = 0; j < jobs[i].burst; j++)
            jobs[i].print();
    }
}

void RR(vector<process> jobs)
{
    //we first print the header
    printHeaders(jobs);
    //then we sort them upon arrival time
    sort(jobs.begin(), jobs.end(), [](process a, process b) {return a.arrival < b.arrival; });
    //we need the total time as we will simulate it as the process time
    int tot = tot_time(jobs);
    int cur = -1;
    //a vector that will hold what to print
    vector<process> toprint;
    
    //now we simulate the running time
    for (int i = 0; i < tot; i++)
    {
        //first thing we need to update the here bool
        for (size_t j = 0; j < jobs.size(); j++)
        {
            //if the arrival time is not yet equal to the current time, i, we dont change the here
            if (jobs[j].arrival <= i)
                jobs[j].here = 1;
            //if it has done the burst, we remove it also be setting here to 0
            if (jobs[j].burst < 1)
                jobs[j].here = 0;
        }
        
        int s = (cur + 1) % jobs.size();//mapping cur pointer to a position in vector
        //as long as we are pointing to a job that is not here , move the pointer
        while (!jobs[s].here)
            s = (++cur + 1) % jobs.size();
        //we add it to the CPU schedule, aka printing it
        toprint.push_back(jobs[(cur + 1) % jobs.size()]);
        //we update the burst time for that process
        jobs[(cur++ + 1) % jobs.size()].burst--;
    }
    for (size_t i = 0; i < toprint.size(); i++)
        toprint[i].print();//now we print the processes that are to be scheduled
}


int main()
{
    //read the processes and then make the vector of processes and call the function
    ifstream file;
    string fileName;
    cout << "Enter file name: ";
    cin >> fileName;
    file.open(fileName, ios::in);
    
    // error handling
    if (file.fail())
    {
        cout << "Input file opening failed" << endl;
        exit(1);
    }
   
    
    
    
    //ifstream file("file.txt");
    
    //file.open("file.txt", ios::in);
    
    // error handling
    
    
    vector<process> jobs;
    while(!file.eof())
    {
        process v;
        file >> v.name >> v.arrival >> v.burst;
        jobs.push_back(v);
    }
    jobs.pop_back();
    string order;
    cout << "Enter order: ";
    cin >> order;
    if (order == "FCFS")
    {
        FCFS(jobs);
    }
    else if (order == "RR")
    {
        RR(jobs);
    }
}
