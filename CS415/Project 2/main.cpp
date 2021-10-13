//
// Created by Robert Sapien on 3/18/20.
//

#include "ADJList.hpp"
#include <string>
#include <iostream>
#include <fstream>

using namespace std;

int main() {
    // Getting data file
    string fName;
    cout << "Enter a file to read in the data: "; cin >> fName; cout << endl<< endl;

    ifstream inFile;
    inFile.open(fName);
    if(!inFile.is_open()){
        cout << "Unable to open " << fName << ".\nExiting..." << endl;
        exit(1);
    }

    inFile.close();
    string oName;
    cout << "Enter a file to output the data: "; cin >> oName; cout << endl<< endl;
    ofstream myfile;
    myfile.open(oName);
    ADJList adjList(fName);
    adjList.getData();
    adjList.createAdj();
    myfile << "There are " << adjList.getNumVert() << " clients in this file"<< endl;
    stack<int> Stack = adjList.topologicalSort();
    myfile << "Printing topological sort:" << endl;
    adjList.printTop(Stack);
    myfile<<"Printing optimal:" << endl;
    std::ofstream outFile;
    //adjList.optimalPath(0, Stack);
    // look at ADJList.hpp or README.txt for what needs to get done
    myfile.close();
    return 0;
}