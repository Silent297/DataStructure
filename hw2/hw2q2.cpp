#include "LNode.h"

void Dispose(LinkList head_a,LinkList &head_b,LinkList &head_c){
    LinkList p_a = head_a->next;
    InitList(head_b);
    InitList(head_c);
    LinkList p_b = head_b;
    LinkList p_c = head_c;
    while(p_a){
        if(p_a->data < 0){
            p_b->next = p_a;
            p_b = p_b->next;
            p_a = p_a->next;
            p_b->next = NULL;
        }
        else if(p_a->data > 0){
            p_c->next = p_a;
            p_c = p_c->next;
            p_a = p_a->next;
            p_c->next = NULL;
        }
        else{
            p_a = p_a->next;
        }
    }
    head_a->next = NULL;   //分解完成后将A变为空表
}