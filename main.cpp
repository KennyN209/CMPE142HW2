#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <cstdlib>
#include <vector>
using namespace std;
int main() {
    vector<int> myintArray; // stores strings converted to ints
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
    
    // reads till eof and converts string to int
    string line;
    for (int result = 0; getline(file, line, ' '); result = stoi(line))
    {
        //cout << line << endl;
        myintArray.push_back(result);
        
        cout << result << " ";
    }
    cout << endl;
    file.close();
    return 0;
}
