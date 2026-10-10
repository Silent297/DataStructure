#include "LNode.h"

int Subtract(LinkList head_a,LinkList head_b, LinkList &head_c)
{
    //head_a,head_b分别表示A和B的头结点，默认A，B已经存在;head_c为用来储存结果的链表
    LinkList p_a = head_a->next;
    LinkList p_b = head_b->next;
    InitList(head_c);
    while(p_a && p_b)
    {   
        if(p_a->data < p_b->data){
            Append(head_c, p_a->data);
            p_a = p_a->next;
        } 
        else if(p_a->data > p_b->data){
            p_b = p_b->next;
        }
        else{
            p_a = p_a->next;
            p_b = p_b->next;
        }
    }
    while(p_a){
        Append(head_c,p_a->data);
        p_a = p_a->next;
    }
    return ListLength(head_c);
}
