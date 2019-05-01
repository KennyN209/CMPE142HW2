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

int main()
{
    
    ifstream file;
    string fileName;
    cout << "Enter file name: ";
    cin >> fileName;
    file.open(fileName, ios::in);
    
  
    if (file.fail())
    {
        cout << "Input file opening failed" << endl;
        exit(1);
    }
   
    
    
  
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


void printHeaders(vector<process> jobs)
{
    for (int i = 0; i < jobs.size(); i++)
        cout << jobs[i].name << "\t";
    cout << endl;
}

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

int tot_time(vector<process> jobs)
{
    int sum = 0;
    for (int i = 0; i < jobs.size(); i++)
    {
        sum += jobs[i].burst;
    }
    return sum;
}

void RR(vector<process> jobs)
{
   
    printHeaders(jobs);
   
    sort(jobs.begin(), jobs.end(), [](process a, process b) {return a.arrival < b.arrival; });
    
    int tot = tot_time(jobs);
    int cur = -1;
   
    vector<process> toprint;
    
    
    for (int i = 0; i < tot; i++)
    {
        
        for (size_t j = 0; j < jobs.size(); j++)
        {
            
            if (jobs[j].arrival <= i)
                jobs[j].here = 1;
            
            if (jobs[j].burst < 1)
                jobs[j].here = 0;
        }
        
        int s = (cur + 1) % jobs.size();
        
        while (!jobs[s].here)
            s = (++cur + 1) % jobs.size();
     
        toprint.push_back(jobs[(cur + 1) % jobs.size()]);
       
        jobs[(cur++ + 1) % jobs.size()].burst--;
    }
    for (size_t i = 0; i < toprint.size(); i++)
        toprint[i].print();


