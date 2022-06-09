#include <stdio.h>
#include <stdlib.h>
#define MAXSIZE 50
typedef struct node
{
    int a;
    int b;
}NList[MAXSIZE];
void Radix_Sort(int figure, Queue A, int n)
{   //figure =2
    Queue Q[n];
    int data, r;
    for (int pass=0; pass<figure; pass++)
    {
        for (int i=0;i<n;i++)
            MakeNull(Q[i]);
        while(!Empty(A))
        {
            data = Front(A);
            Dequeue(A);
            r = Radix(data, key, pass, n);
            Enqueue(data, Q[i]);
        }
        for (int j=0;j<n;j++)
        {
            while(!Empty(Q[i]))
            {
                data = Front(Q[i]);
                Dequeue(Q[i]);
                Enqueue(data, A);
            }
        }
    }
}
int Radix (int k, int p, int n)
{
    int power = 1;
    for (int i=0;i<p;i++)
        power *= n;
    return (k%(power*n))/power;
}
int main()
{
    int A[MAXSIZE];
    int i,n;
    srand((int)time(NULL));
    printf("input n(n<50):\n");
    scanf("%d",&n);
    for (i=0; i<n; i++)
    {
        A[i] = rand()%(n*n);
        printf("%d\t",A[i]);
    }
    printf("\n");
    system("PAUSE");
    printf("\nAfter RadixSort:\n");
    Radix_Sort(A, n);
}

