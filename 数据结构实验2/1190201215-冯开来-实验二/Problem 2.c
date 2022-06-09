#include <stdio.h>
#include <stdlib.h>
struct node
{
    int data;
    struct node *lchild;
    struct node *rchild;
};
typedef struct node *TREE;
TREE Insert(int x, TREE T)
{
    if (T==NULL)
    {
        T = (TREE)malloc(sizeof(struct node));
        T->data = x;
        T->lchild = T->rchild = NULL;
    }
    else
    {
        if(x < T->data)
            T->lchild = Insert(x,T->lchild);
        else
            T->rchild = Insert(x,T->rchild);
    }
    return T;
}
TREE FindMin(TREE T)
{
    TREE R = T;
    if(T==NULL) return NULL;
    else if (T->lchild==NULL) return T;
    else return FindMin(T->lchild);
}
TREE Delete(int x, TREE T)
{
    if (T==NULL) printf("error!");
    else if (x<T->data) T->lchild = Delete(x,T->lchild);
    else if (x>T->data) T->rchild = Delete(x,T->rchild);
    else
    {
        if (T->lchild==NULL) T = T->rchild;
        else T = T->lchild;
    }
    return T;
}
int main()
{
    int N,i,x,y,sum=0;
    TREE T = NULL;
    //freopen("problem2_sample.txt","r",stdin);
	//freopen("problem2.out","w",stdout);
    scanf("%d",&N);
    for (i=0;i<N;i++)
    {
        scanf("%d",&x);
        T = Insert(x,T);
    }
    while(T->lchild!=NULL || T->rchild!=NULL)
    {
        x = FindMin(T)->data;
        T = Delete(x,T);
        y = FindMin(T)->data;
        T = Delete(y,T);
        T = Insert(x+y,T);
        sum = sum + x + y;
    }
    printf("%d",sum);
}
