#include "../include/graph.h"
#include<iostream>

void graph::init(int u[],int v[],int w[])
{
    int cur_vex = u[0];
    int j = 0;
    vertex[j].head = new Edge;
    vertex[j].head->adj = v[0];
    vertex[j].head->weight = w[0];
    vertex[j].head->next = nullptr;
    Edge* p = vertex[j].head;
    for(int i = 1; i < edge_num; i++)
    {
        if(u[i] == cur_vex){
            p->next = new Edge;
            p = p->next;
            p->adj = v[i];
            p->weight = w[i];
            p->next = nullptr;
        }
        else{
            cur_vex = u[i];
            j++;
            vertex[j].head = new Edge;
            vertex[j].head->adj = v[i];
            vertex[j].head->weight = w[i];
            vertex[j].head->next = nullptr;
            p = vertex[j].head;
            
        }
    }//TODO:完成邻接表存储图
}

void graph::dfs(int s)
{
    if(vertex[s].visited == 0){
        std::cout << s << ' ';
        vertex[s].visited = 1;
    }//TODO:完成图的深度优先遍历，输出顶点编号
    Edge* p = vertex[s].head;
    while(p != nullptr ){
        if(vertex[p->adj].visited == 0)
            dfs(p->adj);
        p = p->next;
    }
}
