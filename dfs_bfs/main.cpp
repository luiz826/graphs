#include <iostream>
#include <queue>
#include <vector>
#include <stack>
#include <fstream>

using namespace std;

int t = 0;
queue<int> F;
stack<int> P;


class Graph {
    public:
        int lenV;
        string textFile;
        vector<int> *adjList;
        vector<int> *parent;
        vector<int> *level;
        vector<int> *L;

        Graph(string textFile);
        
        void dfs(int v);
        void bfs(int v);
        void initGraph(void);
        void fillIndexAndParent(void);
};

Graph::Graph(string textFile) {
    this -> textFile = textFile;
    this -> lenV;

    adjList = new vector<int>[lenV];
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


void Graph::initGraph(void) {
    ifstream graphFile;
    int isConected;

    graphFile.open(textFile);

    // number of vertices
    graphFile >> lenV; 
     
    for (int i=1; i< lenV+1; i++) {
        for (int j = i; j < lenV; j++) {
            graphFile >> isConected;
            if (isConected) {
                adjList[i].push_back(j);
                adjList[j].push_back(i);    
            }
            
        }
        cout << endl;
    }  


    graphFile.close();
}

void Graph::dfs(int v) {
    while (!F.empty()) {
        int v = F.front();
        F.pop();
        
        vector<int>::iterator w;
        
        for (w = adjList[v].begin(); w != adjList[v].end(); w++) {
            if (L[*w].back() == 0) {
                parent[*w].push_back(v);
                level[*w].push_back(level[v].back()+1);
                t += 1;
                L[*w].push_back(t);
                F.push(*w);
            } 
            else if (level[*w].back() == level[v].back()) {
                if (parent[*w].back() == parent[v].back()) {
                    cout << *w << "IS BROTHER OF " << v << " <RED> " << endl;
                }
                else {
                    cout << *w << "IS COUSIN OF " << v << " <ORANGE> " << endl;    
                }
            }
            else if (level[*w].back() == level[v].back()+1){
                cout << *w << "IS UNCLE OF " << v << " <GREEN> " << endl;    
            }

        }
    }
}           

void Graph::bfs(int v) {
    while (!P.empty()) {
        int v = P.top();
        P.pop();
        
        vector<int>::iterator w;
        
        for (w = adjList[v].begin(); w != adjList[v].end(); w++) {
            if (L[*w].back() == 0) {
                parent[*w].push_back(v);
                level[*w].push_back(level[v].back()+1);
                t += 1;
                L[*w].push_back(t);
                P.push(*w);
                cout << v << "IS FATHER OF " << *w << " <RED> " << endl;
            } 
            else if (level[*w].back() == level[v].back()) {
                if (parent[*w].back() == parent[v].back()) {
                    cout << v << "IS BROTHER OF " << *w << " <RED> " << endl;
                }
                else {
                    cout << v << "IS COUSIN OF " << *w << " <ORANGE> " << endl;    
                }
            }
            else if (level[*w].back() == level[v].back()+1){
                cout << v << "IS UNCLE OF " << *w << " <GREEN> " << endl;    
            }

        }
    }
}    



int main(void) {       
    // int len_v;
    // int a;
    // cin >> len_v;
    // cout << "N " << len_v << endl;

    // for (int i=1; i< len_v+1; i++) {
    //     for (int j = i; j < len_v; j++) {
    //         cin >> a;
    //         cout << "(" << i << "," << j << ") -> " << a << " | ";
    //     }
    //     cout << endl;
    // }
    // int v = 0;

    Graph g("instance.txt");
    g.fillIndexAndParent();
    g.initGraph();
    cout << g.lenV << endl;
    cout << g.adjList << endl;
    // g.level[v].push_back(0);
    // t += 1;
    // g.L[v].push_back(t);
    // F.push(v);
    // g.dfs();
    // g.bfs();
    
    
}
