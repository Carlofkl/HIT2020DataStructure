#include <stdio.h>
#include <stdlib.h>
typedef struct node* BTREE;
struct node
{
    int x;
    BTREE lchild;
    BTREE rchild;
};
struct Node
{
    BTREE data;
    struct Node *next;
};
typedef struct Node *NodePtr;
struct QNode
{
    NodePtr rear;
    NodePtr front;
};
typedef struct QNode *Queue;
void EnQueue(BTREE T, Queue Q)
{
    NodePtr t = (NodePtr)malloc(sizeof(struct Node));
    t->data = T;
    t->next = NULL;
    if (Q->front==NULL) Q->front = Q->rear = t;
    else {Q->rear->next=t;Q->rear=t;}
}
void LeverOrder(BTREE T)
{
    Queue Q = (Queue)malloc(sizeof(struct QNode));
    Q->front = Q->rear = NULL;
    EnQueue(T, Q);
    while (Q->front!=NULL)
    {
        T = Q->front->data;
        printf("%d ",T->x);
        Q->front = Q->front->next;
        if (T->lchild!=NULL) EnQueue(T->lchild, Q);
        if (T->rchild!=NULL) EnQueue(T->rchild, Q);
    }
}
BTREE Create1(int a[], int b[], int n, int y, int z)
{
    BTREE p = (BTREE)malloc(sizeof(struct node));
    int i;
    p->x = a[y];
    p->lchild = p->rchild = NULL;
    for (i=z; i<n+z; i++) if (a[y]==b[i]) break;
    if (n==1) return p;
    else
    {
        if(i-z) p->lchild = Create1(a, b, i-z, y+1, z);
        if(n-i+z-1) p->rchild = Create1(a, b, n-i+z-1, y+i-z+1, i+1);
    }
    return p;
}
BTREE Create2(int a[],int b[],int size)
{
    BTREE root[5000];
    int i;
    for(i=0; i<size; i++)
    {
        root[i]=(BTREE)malloc(sizeof(struct node));
        if(root[i]!=NULL)//空间分配成功
        {
            root[i]->x = a[i];
            root[i]->lchild = root[i]->rchild = NULL;
        }
        else
            exit(-1);
    }
    i=0;
    while (i<size-1)
    {
        int k = 0, j = 0, m = 0;
        int  save, tem;
        for (; b[k] != a[i + 1]; k++);
        for (; b[j] != a[i]; j++);
        if (i == 0)
            save = j;
        //给根节点创建左子树
        int flag = 0;
        if (j>k)
        {
            root[i]->lchild = root[i+1];

        }
        else
        {
            root[i]->rchild = NULL;
            flag = 1;//说明其左子树为空
        }
        //给根节点创建右子树

        for (tem = (i > save ? j+1: j + 1 + i); b[m] != a[tem]; m++);
        if (m > j&&!flag&&m<size)
        {
            root[i]->rchild = root[tem];
        }
        else if (flag&&a[i+1]==b[j+1])//如果左子树为空再判断中序和前序序列中当前节点的下一个节点是否一致，如果是，说明下一个节点就是其右孩子，如果不是则说明其没有右孩子
            root[i]->rchild = root[1 + i];
        else
            root[i]->rchild = NULL;
        i++;

    }
    return root[0];
}

int main()
{
    int n,i;
    BTREE T,p,t;
    //freopen("problem1_sample.txt","r",stdin);
    //freopen("problem1.out","w",stdout);
    scanf("%d",&n);
    int a[n], b[n];
    for(i=0; i<n; i++) scanf("%d",&a[i]);
    for(i=0; i<n; i++) scanf("%d",&b[i]);
    T = Create1(a,b,n,0,0);
    //T = Create2(a,b,n);
    LeverOrder(T);
}
