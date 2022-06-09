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
typedef Position AVLTree; /* AVL������ */
struct AVLNode{
    int Data; /* ������� */
    AVLTree Left;     /* ָ�������� */
    AVLTree Right;    /* ָ�������� */
    int Height;       /* ���� */
};

int Max ( int a, int b )
{
    return a > b ? a : b;
}

AVLTree SingleLeftRotation ( AVLTree A )
{ /* ע�⣺A������һ�����ӽ��B */
  /* ��A��B������������A��B�ĸ߶ȣ������µĸ����B */

    AVLTree B = A->Left;
    A->Left = B->Right;
    B->Right = A;
    A->Height = Max( GetHeight(A->Left), GetHeight(A->Right) ) + 1;
    B->Height = Max( GetHeight(B->Left), A->Height ) + 1;

    return B;
}

AVLTree DoubleLeftRightRotation ( AVLTree A )
{ /* ע�⣺A������һ�����ӽ��B����B������һ�����ӽ��C */
  /* ��A��B��C�����ε����������µĸ����C */

    /* ��B��C���ҵ�����C������ */
    A->Left = SingleRightRotation(A->Left);
    /* ��A��C��������C������ */
    return SingleLeftRotation(A);
}

/*************************************/
/* �ԳƵ��ҵ�������-��˫�����Լ�ʵ�� */
/*************************************/

AVLTree insert( AVLTree T, int X )
{ /* ��X����AVL��T�У����ҷ��ص������AVL�� */
    if ( !T ) { /* ��������������½�����һ�������� */
        T = (AVLTree)malloc(sizeof(struct AVLNode));
        T->Data = X;
        T->Height = 0;
        T->Left = T->Right = NULL;
    } /* if (�������) ���� */

    else if ( X < T->Data ) {
        /* ����T�������� */
        T->Left = insert( T->Left, X);
        /* �����Ҫ���� */
        if ( GetHeight(T->Left)-GetHeight(T->Right) == 2 )
            if ( X < T->Left->Data )
               T = SingleLeftRotation(T);      /* ���� */
            else
               T = DoubleLeftRightRotation(T); /* ��-��˫�� */
    } /* else if (����������) ���� */

    else if ( X > T->Data ) {
        /* ����T�������� */
        T->Right = insert( T->Right, X );
        /* �����Ҫ���� */
        if ( GetHeight(T->Left)-GetHeight(T->Right) == -2 )
            if ( X > T->Right->Data )
               T = SingleRightRotation(T);     /* �ҵ��� */
            else
               T = DoubleRightLeftRotation(T); /* ��-��˫�� */
    } /* else if (����������) ���� */
    /* else X == T->Data��������� */

    /* �����˸������� */
    T->Height = Max( GetHeight(T->Left), GetHeight(T->Right) ) + 1;

    return T;
}
