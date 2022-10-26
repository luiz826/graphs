#include <iostream>
#include <queue>
#include <vector>
#include <stack>

using namespace std;

int t = 0;
queue<int> F;
stack<int> P;


class Graph {
    public:
        int v;
        vector<int> *adjList;
        vector<int> *parent;
        vector<int> *level;
        vector<int> *L;

        Graph(int v);
        
        void dfs(void);
        void bfs(void);
        void fillIndexAndParent(void);
};

Graph::Graph(int v) {
    this -> v = v;

    adjList = new vector<int>[v];
    L = new vector<int>[v];
    parent = new vector<int>[v];
    level = new vector<int>[v];
}

void Graph::fillIndexAndParent(void){
    for (int i = 0; i < v; i++) {
        parent[i].push_back(-1); 
        L[i].push_back(0);
    }
}

void Graph::dfs(void) {
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

void Graph::bfs(void) {
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
    int len_v;
    int a;
    cin >> len_v;
    cout << "N " << len_v << endl;

    for (int i=1; i< len_v+1; i++) {
        for (int j = i; j < len_v; j++) {
            cin >> a;
            cout << "(" << i << ", " << j << ") -> " << a << " | ";
        }
        cout << endl;
    }
    // int v = 0;

    // Graph g(len_v);
    // g.fillIndexAndParent();
        
    // g.level[v].push_back(0);
    // t += 1;
    // g.L[v].push_back(t);
    // F.push(v);
    // g.dfs();
    // g.bfs();
    
    
}
