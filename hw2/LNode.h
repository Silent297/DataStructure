#include <stdio.h>
#include <stdlib.h>

#define OK 1
#define ERROR 0
#define TRUE 1
#define FALSE 0

typedef int Status;
typedef int ElemType;   /* 集合元素类型，可按题目要求修改 */

/* 单链表数据表示，带头结点 */
typedef struct LNode {
    ElemType data;
    struct LNode *next;
} LNode, *LinkList;

/* 初始化带头结点的空链表 */
Status InitList(LinkList &L) {
    L = (LNode *)malloc(sizeof(LNode));
    if (L == NULL) return ERROR;

    L->next = NULL;
    return OK;
}

/* 销毁整个链表，包括头结点 */
void DestroyList(LinkList &L) {
    LNode *p = L;
    while (p != NULL) {
        LNode *q = p->next;
        free(p);
        p = q;
    }
    L = NULL;
}

/* 清空链表，保留头结点 */
void ClearList(LinkList &L) {
    if (L == NULL) return;

    LNode *p = L->next;
    while (p != NULL) {
        LNode *q = p->next;
        free(p);
        p = q;
    }
    L->next = NULL;
}

/* 判断链表是否为空 */
Status ListEmpty(LinkList L) {
    if (L == NULL || L->next == NULL)
        return TRUE;
    return FALSE;
}

/* 求链表长度，即集合元素个数 */
int ListLength(LinkList L) {
    if (L == NULL) return 0;

    int len = 0;
    LNode *p = L->next;
    while (p != NULL) {
        len++;
        p = p->next;
    }
    return len;
}

/* 按位查找：取第 i 个元素，用引用 e 返回 */
Status GetElem(LinkList L, int i, ElemType &e) {
    if (L == NULL || i < 1) return ERROR;

    LNode *p = L->next;
    int j = 1;

    while (p != NULL && j < i) {
        p = p->next;
        j++;
    }

    if (p == NULL) return ERROR;

    e = p->data;
    return OK;
}

/* 按值查找：返回第一个值为 e 的结点指针，找不到返回 NULL */
LNode *LocateElem(LinkList L, ElemType e) {
    if (L == NULL) return NULL;

    LNode *p = L->next;
    while (p != NULL && p->data < e) {   /* 利用递增有序特性 */
        p = p->next;
    }

    if (p != NULL && p->data == e)
        return p;

    return NULL;
}

/* 在第 i 个位置前插入元素 e */
Status ListInsert(LinkList &L, int i, ElemType e) {
    if (L == NULL || i < 1) return ERROR;

    LNode *p = L;
    int j = 0;

    while (p != NULL && j < i - 1) {
        p = p->next;
        j++;
    }

    if (p == NULL) return ERROR;

    LNode *s = (LNode *)malloc(sizeof(LNode));
    if (s == NULL) return ERROR;

    s->data = e;
    s->next = p->next;
    p->next = s;

    return OK;
}

/* 删除第 i 个元素，用引用 e 返回其值 */
Status ListDelete(LinkList &L, int i, ElemType &e) {
    if (L == NULL || i < 1) return ERROR;

    LNode *p = L;
    int j = 0;

    while (p->next != NULL && j < i - 1) {
        p = p->next;
        j++;
    }

    if (p->next == NULL) return ERROR;

    LNode *q = p->next;
    e = q->data;
    p->next = q->next;
    free(q);

    return OK;
}

/* 尾插法：在链表尾部插入元素 e */
Status Append(LinkList &L, ElemType e) {
    if (L == NULL) return ERROR;

    LNode *p = L;
    while (p->next != NULL) {
        p = p->next;
    }

    LNode *s = (LNode *)malloc(sizeof(LNode));
    if (s == NULL) return ERROR;

    s->data = e;
    s->next = NULL;
    p->next = s;

    return OK;
}

/* 按值有序插入：保持链表递增，且集合中不插入重复元素 */
Status InsertSorted(LinkList &L, ElemType e) {
    if (L == NULL) return ERROR;

    LNode *pre = L;
    LNode *p = L->next;

    while (p != NULL && p->data < e) {
        pre = p;
        p = p->next;
    }

    /* 已存在该元素，不插入 */
    if (p != NULL && p->data == e)
        return ERROR;

    LNode *s = (LNode *)malloc(sizeof(LNode));
    if (s == NULL) return ERROR;

    s->data = e;
    s->next = pre->next;
    pre->next = s;

    return OK;
}

/* 由数组创建递增有序且不重复的集合链表 */
Status CreateSortedList(LinkList &L, ElemType a[], int n) {
    if (InitList(L) != OK) return ERROR;

    for (int i = 0; i < n; i++) {
        InsertSorted(L, a[i]);
    }

    return OK;
}

/* 遍历输出链表 */
void PrintList(LinkList L) {
    if (L == NULL) {
        printf("NULL\n");
        return;
    }

    LNode *p = L->next;
    while (p != NULL) {
        printf("%d ", p->data);
        p = p->next;
    }
    printf("\n");
}