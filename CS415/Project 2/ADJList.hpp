//
// Created by Robert Sapien on 3/20/20.
//

#ifndef CS415PROJ2_MASTER_ADJLIST_HPP
#define CS415PROJ2_MASTER_ADJLIST_HPP


#include <vector>
#include <queue>
#include <fstream>
using namespace std;

class ADJList {
public:
    explicit ADJList(string& dFile);

    class Client{
    public:
        Client(int s, int e, int w, int v);

        int getSD();
        int getED();
        int getWeight();
        int getCNum();
        bool isVisited();
        void setVisited(bool b);
        void setEnd(bool b);
        bool isEnd();


        vector<Client> adjList; // Holds adjacency list

    private:
        int sDay, eDay, weight, cNum; // start Day, end Day, weight
        bool visited, end;
    };

    // gets data from the file
    void getData();
    void pData(queue<int>& nums);
    int getNumVert();
    void createAdj();
    void printAdj();
    void resetVisited();
    void topologicalSortUtil(int v, bool visited[] ,stack<int> &Stack);
    stack<int> topologicalSort();
    void optimalPath(int s, stack<int> Stack);
    void printTop(stack<int> Stack);
    bool checkADJ(vector<Client> adj, int num);
    int optPath(int c, int g, vector<int>& opPath);
private:
    vector<Client> ClientList; // Holds all clients

    int numVert;
    ifstream inFile;

};




#endif //CS415PROJ2_MASTER_ADJLIST_HPP