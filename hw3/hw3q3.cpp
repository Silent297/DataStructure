#include "LNode.h"

int Max_int(LinkList f){
    if(f == NULL)
        return INT_MIN;
    int rest_max = Max_int(f->next);
    if(f->data >= rest_max)
        return f->data;
    else
        return rest_max;
}

int Node_amount(LinkList f){
    if(f == NULL)
        return 0;
    else
        return Node_amount(f->next) + 1;
}

int Sum(LinkList f){
    if(f == NULL)
        return 0;
    else
        return f->data + Sum(f->next);
}

double Mean(LinkList f){
    return (double)Sum(f)/Node_amount(f);
}