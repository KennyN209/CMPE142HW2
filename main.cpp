#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <cstdlib>
#include <vector>
using namespace std;
int main() {
    vector<int> myintArray; // stores strings converted to ints on heap
    ifstream file;
    string fileName;
    
    // get file name
    cout << "Enter file name: ";
    cin >> fileName;
    file.open(fileName, ios::in);
    
    // error handling
    if (file.fail())
    {
        cout << "Input file opening failed" << endl;
        exit(1);
    }
    
    
    string line;
    int result;
    
    // reads till eof and converts string to int
    while (getline(file, line, ' '))
    {
        // use stoi to convert string to int
        result = stoi(line);
        // store in array on heap
        myintArray.push_back(result);
        cout << result << " ";
    }
    
    
    
    cout << endl;
    file.close();
    return 0;
}
