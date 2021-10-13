//
// Created by Robert Sapien on 3/20/20.
//

#include "ADJList.hpp"
#include <vector>
#include <iostream>
#include <list>
#include <limits.h>
#include <stack>
#define NINF INT_MIN

// ----- Client Functions ----- //

ADJList::Client::Client(int s, int e, int w, int v){
    sDay = s;
    eDay = e;
    weight = w;
    cNum = v;
    visited = false;
    end = false;
}
int ADJList::Client::getSD(){return sDay;}
int ADJList::Client::getED(){return eDay;}
int ADJList::Client::getWeight(){return weight;}
int ADJList::Client::getCNum(){return cNum;}
bool ADJList::Client::isVisited(){return visited;}
void ADJList::Client::setVisited(bool b){visited = b;}
bool ADJList::Client::isEnd() { return end;}
void ADJList::Client::setEnd(bool b) {end = b;}

// ----- ADJList Functions ----- //

ADJList::ADJList(string& dFile): numVert{0} {
    inFile.open(dFile, std::ios::in);
}

// gets data form file and puts it in fcfs queue
void ADJList::getData(){
    int num;
    queue<int> nums;
    while(inFile >> num){ // pushes all numbers from file into fcfs queue
        nums.push(num);
    }

    // creates clients from data and pushes them to vector ClientList
    pData(nums);

    // adds adjacent vertices
    createAdj();
}

// creates and returns a Client
void ADJList::pData(queue<int>& nums){
    while(!nums.empty()){
        int sd;
        int ed;
        int w;

        sd = nums.front();
        nums.pop();

        ed = nums.front();
        nums.pop();

        w = nums.front();
        nums.pop();

        ++numVert;
        Client c(sd, ed, w, numVert);
        ClientList.push_back(c);
    }
}

void ADJList::createAdj(){
    for(int i = 0; i < ClientList.size(); i++){
        for(int j = 0; j < ClientList.size(); j++){
            if(ClientList[j].getSD() > ClientList[i].getED() && i != j){
                if(!checkADJ(ClientList[i].adjList, ClientList[j].getCNum())){
                    ClientList[i].adjList.push_back(ClientList[j]);
                    ClientList[j].setEnd(true);
                }
            }
        }
    }
}

void ADJList::printAdj() {
    for(auto & i : ClientList){
        cout << "Client " << i.getCNum() << " : ";
        for(auto & j : i.adjList){
            cout << "c" << j.getCNum() << ' ';
        }
        cout << endl;
    }
}

void printTop(stack<int> Stack){
    while (Stack.empty() == false)
    {
        cout << Stack.top() << " ";
        Stack.pop();
    }
}

void ADJList::resetVisited() {
    for(auto & c : ClientList){
        c.setVisited(false);
    }
}

bool ADJList::checkADJ(vector<ADJList::Client> adj, int num){
    for(auto & a : adj){
        if(a.getCNum() == num) return true;
    }
}

//void ADJList::topologicalSortUtil(int v, stack<int> &Stack)

void ADJList::topologicalSortUtil(int v, bool visited[], stack<int> &Stack)
{

    // Mark the current node as visited.
    ClientList[v].setVisited(true);
    int breakNumber = 0;
    // Recur for all the vertices adjacent to this vertex
    // Traverses down adj list
    for(int i = 0; i < ClientList[v].adjList.size(); i++) {
        if (!ClientList[v].adjList[i].isVisited()) {
            for (int j = 0; j < numVert; j++) {
                if (ClientList[v].adjList[i].getCNum() == ClientList[j].getCNum()) {
                    if (ClientList[j].isVisited() == true)
                        breakNumber++;
                }
            }
            if (breakNumber == 0) {
                int next = ClientList[v].adjList[i].getCNum() - 1;
                topologicalSortUtil(next, visited, Stack);
            }
        }
    }


    // Push current vertex to stack which stores result
    Stack.push(ClientList[v].getCNum()); //need to push the cnum onto stack
}

// The function to do Topological Sort. It uses recursive
// topologicalSortUtil()
stack<int> ADJList::topologicalSort() {
    // Mark all the vertices as not visited
    stack<int> Stack;
    bool visited[numVert];
    for (int i = 0; i < numVert; i++)
        visited[i] = false;
    resetVisited();

    // Call the recursive helper function to store Topological
    // Sort starting from all vertices one by one
    for (int i = 0; i < numVert; i++) {
        if (!ClientList[i].isVisited())
            topologicalSortUtil(i, visited, Stack);
    }
    return Stack;
}

void ADJList::printTop(stack<int> Stack) {
    while (Stack.empty() == false)
    {
        cout << Stack.top() << " ";
        Stack.pop();
    }

}

void ADJList::optimalPath(int s, stack<int> Stack) {
    int dist[numVert+1];
    vector<int> opPath;

    for (int i = 0; i < numVert; i++)
        dist[i] = NINF;
    dist[s] = 0;

    while(!Stack.empty()){
        int u = Stack.top();
        Stack.pop();

        if(dist[u] != NINF){
            for(auto & i : ClientList[u].adjList){
                if(dist[i.getCNum()] < dist[u] + i.getWeight())
                    dist[i.getCNum()-1] = dist[u] + i.getWeight();
            }
        }
    }

    for (int i = 0; i < numVert; i++)
        (dist[i] == NINF) ? cout << "INF " : cout << dist[i] << " ";
}
int ADJList::optPath(int c, int g, vector<int> &opPath) {
    if(ClientList[c].adjList.empty()) return g;
    for(auto & i : ClientList[c].adjList){
        opPath.push_back(i.getCNum());
        if(g <optPath(i.getCNum()-1,g,opPath)){}
    }
}

int ADJList::getNumVert() { return numVert;}