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

typedef struct AVLNode *Position;
typedef Position AVLTree; /* AVL树类型 */
struct AVLNode{
    int Data; /* 结点数据 */
    AVLTree Left;     /* 指向左子树 */
    AVLTree Right;    /* 指向右子树 */
    int Height;       /* 树高 */
};

int Max ( int a, int b )
{
    return a > b ? a : b;
}

AVLTree SingleLeftRotation ( AVLTree A )
{ /* 注意：A必须有一个左子结点B */
  /* 将A与B做左单旋，更新A与B的高度，返回新的根结点B */

    AVLTree B = A->Left;
    A->Left = B->Right;
    B->Right = A;
    A->Height = Max( GetHeight(A->Left), GetHeight(A->Right) ) + 1;
    B->Height = Max( GetHeight(B->Left), A->Height ) + 1;

    return B;
}

AVLTree DoubleLeftRightRotation ( AVLTree A )
{ /* 注意：A必须有一个左子结点B，且B必须有一个右子结点C */
  /* 将A、B与C做两次单旋，返回新的根结点C */

    /* 将B与C做右单旋，C被返回 */
    A->Left = SingleRightRotation(A->Left);
    /* 将A与C做左单旋，C被返回 */
    return SingleLeftRotation(A);
}

/*************************************/
/* 对称的右单旋与右-左双旋请自己实现 */
/*************************************/

AVLTree insert( AVLTree T, int X )
{ /* 将X插入AVL树T中，并且返回调整后的AVL树 */
    if ( !T ) { /* 若插入空树，则新建包含一个结点的树 */
        T = (AVLTree)malloc(sizeof(struct AVLNode));
        T->Data = X;
        T->Height = 0;
        T->Left = T->Right = NULL;
    } /* if (插入空树) 结束 */

    else if ( X < T->Data ) {
        /* 插入T的左子树 */
        T->Left = insert( T->Left, X);
        /* 如果需要左旋 */
        if ( GetHeight(T->Left)-GetHeight(T->Right) == 2 )
            if ( X < T->Left->Data )
               T = SingleLeftRotation(T);      /* 左单旋 */
            else
               T = DoubleLeftRightRotation(T); /* 左-右双旋 */
    } /* else if (插入左子树) 结束 */

    else if ( X > T->Data ) {
        /* 插入T的右子树 */
        T->Right = insert( T->Right, X );
        /* 如果需要右旋 */
        if ( GetHeight(T->Left)-GetHeight(T->Right) == -2 )
            if ( X > T->Right->Data )
               T = SingleRightRotation(T);     /* 右单旋 */
            else
               T = DoubleRightLeftRotation(T); /* 右-左双旋 */
    } /* else if (插入右子树) 结束 */
    /* else X == T->Data，无须插入 */

    /* 别忘了更新树高 */
    T->Height = Max( GetHeight(T->Left), GetHeight(T->Right) ) + 1;

    return T;
}
