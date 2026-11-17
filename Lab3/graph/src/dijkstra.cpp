#include "../include/dijkstra.h"
#include <iostream>
#define INFINITY 1000000

void dijkstra::ssp(int s)
{
    for(int i = 0; i < g.vertex_num; i++){
        vertex[i].sure = 0;
        vertex[i].dist = INFINITY;
        vertex[i].path = -1;
    }//TODO:实现以s为起始点的dijkstra算法求最短路径
    vertex[s].sure = 1;
    vertex[s].dist = 0;
    vertex[s].path = -1;
    graph::Edge* p = g.vertex[s].head;
    while(p != nullptr){
        vertex[p->adj].dist = p->weight;
        vertex[p->adj].path = s;
        p = p->next;
    }

    int min_len = INFINITY;
    int min_vex;
    for(int i = 0; i < g.vertex_num - 1; i++){
        min_len = INFINITY;
        for(int j = 0; j < g.vertex_num; j++){
            if(vertex[j].sure == 1)
                continue;
            if(vertex[j].dist < min_len){
                min_len = vertex[j].dist;
                min_vex = j;
            }
        }
        if(min_len == INFINITY)
            break;
        vertex[min_vex].sure = 1;

        p = g.vertex[min_vex].head;
        while(p != nullptr){
            if(vertex[p->adj].sure == 0){
                if(vertex[p->adj].dist > vertex[min_vex].dist + p->weight){
                    vertex[p->adj].dist = vertex[min_vex].dist + p->weight;
                    vertex[p->adj].path = min_vex;
                }
            }
            p = p->next;
        }
    }
    for(int i = 0; i < g.vertex_num; i++){
        if(vertex[i].dist == INFINITY){
            std::cout << i << ": " << "Cannot reach" << std::endl;
            continue;
        }
        std::cout << i << ": " << vertex[i].dist << "   Path: ";
        print(i);
        std::cout << std::endl;
    }
}

void dijkstra::print(int u)
{//TODO:用于输出最短路径的辅助函数，可以使用递归实现
    if(vertex[u].path != -1)
        print(vertex[u].path);
    std::cout << u << ' ';
}