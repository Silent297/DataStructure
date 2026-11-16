#define MAX_VERTEX_NUM 100
#include <stack>
#include <iostream>
#include <vector>

struct ArcNode {
    int adjvex;          
    ArcNode *nextarc;        
};

struct VNode {
    char data;               
    ArcNode *firstarc;       
};

struct ALGraph {
    VNode vertices[MAX_VERTEX_NUM]; 
    int vexnum, arcnum;             
};

bool visited[MAX_VERTEX_NUM];

void DFS_NonRecursive(ALGraph G, int v){
    for(int i = 0; i < G.vexnum; i++)
        visited[i] = false;

    std::stack<int> s;
    std::cout << G.vertices[v].data << ' ';
    visited[v] == true;
    s.push(v);

    while(s.empty() == false){
        int cur = s.top();
        ArcNode* p = G.vertices[cur].firstarc;
        while (p != nullptr && visited[p->adjvex]) {
            p = p->nextarc;
        }
        if (p != nullptr) {
            int w = p->adjvex;
            std::cout << G.vertices[w].data << " "; 
            visited[w] = true;
            s.push(w); 
        } 
        else {
            s.pop();
        }
    }
}

bool K_length(ALGraph &G, int u, int v, int k, int cur_len, std::vector<bool> &visited){
    if(u == v && cur_len == k)
        return true;
    if(cur_len > k)
        return false;
    
    visited[u] == true;
    ArcNode *p = G.vertices[u].firstarc;
    while(p !=nullptr){
        int cur = p->adjvex;
        if(visited[cur] == false){
            if(K_length(G, cur, v, k, cur_len + 1, visited))
                return true;
        }
        p = p->nextarc;
    }
    
    visited[u] = false;
    return false;
}

