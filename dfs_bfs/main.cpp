#include <iostream>
#include <queue>
#include <vector>
#include <list>
#include <stack>
#include <fstream>

using namespace std;

int t = 0;

stack<int> S;
queue<int> Q;


class Graph {
    public:
        int lenV;
        list<int> *adjList;
        vector<int> *parent;
        vector<int> *level;
        vector<int> *L;

        Graph(int lenV);
        
        void dfs(int v);
        void bfs(int v);
        void fillIndexAndParent(void);
};

Graph::Graph(int lenV) {
    this -> lenV;

    adjList = new list<int>[lenV];
    L = new vector<int>[lenV];
    parent = new vector<int>[lenV];
    level = new vector<int>[lenV];
}

void Graph::fillIndexAndParent(void) {
    for (int i = 0; i < lenV; i++) {
        parent[i].push_back(-1); 
        L[i].push_back(0);
    }
}



void Graph::bfs(int v) {
    Q.push(v);
    level[v].push_back(0);
    parent[v].push_back(-1);
    while (!Q.empty()) {
        int u = Q.front();
        Q.pop();
        for (auto i = adjList[u].begin(); i != adjList[u].end(); i++) {
            if (level[*i].empty()) {
                level[*i].push_back(level[u][0] + 1);
                parent[*i].push_back(u);
                Q.push(*i);
            } else if (level[*i][0] == level[u][0] + 1) {
                cout << *i << " IS UNCLE OF " << v << " <GREEN> " << endl;   
           } 
        }
    }
}


void Graph::dfs(int v) {
    S.push(v);
    while (!S.empty()) {
        int u = S.top();
        S.pop();
        if (L[u].empty()) {
            t++;
            L[u].push_back(t);
        }
        for (auto i = adjList[u].begin(); i != adjList[u].end(); i++) {
            if (L[*i].empty()) {
                parent[*i].push_back(u);
                S.push(*i);
            }
        }
        if (L[u].size() == 1) {
            t++;
            L[u].push_back(t);
            // F.push(t);
            // P.push(u);
        }
    }
}

int main(void) {       
    ifstream graphFile;
    int isConected;

    graphFile.open("instance.txt");

    

    Graph g(8);
    g.fillIndexAndParent();
    cout << g.lenV << endl;
    graphFile >> g.lenV;
    cout << g.lenV << endl;
    for (int i = 1; i < g.lenV+1; i++) {
    
        for (int j = 1; j < g.lenV+1; j++) {
        
            graphFile >> isConected;
            if (isConected) {
                cout << i << " -> " << j << endl;
                g.adjList[i].push_back(j);
            }
            
        }
        cout << endl;
    }

    graphFile.close();

    g.bfs(1);
    g.dfs(1);

    for (int a = 1; a < g.lenV+1; a++) {
        cout << a << " ";
        for (auto w = g.adjList[a].begin(); w != g.adjList[a].end(); w++) {
            cout << *w << " ";
        }
        cout << endl;
    }   
}
