#include <stdio.h>
#include <stdlib.h>
#include <math.h>
typedef struct stack *STACK;
struct stack{
    int a;
    char c[100];
    STACK next;
};
int transform(char* p)
{
    int a,i=0,j;
    char *q;
    q=p;
    while (*q!='\0')
    {
        i++;
        q++;
    }
    q--;
    if (p[0]=='-')
    {
        for (j=0;j<i-1;j++)
        {
            a=a+(*q)*pow(10,j);
        }
    }
    else
    {
        for (j=0;j<i-1;j++)
        {
            a=a+(*q)*pow(10,j);
        }
    }
    return a;
}
int main()
{
    int i,j;
    STACK s,p,q;
    s = (STACK)malloc(sizeof(struct stack));
    s->next=NULL;
    p = (STACK)malloc(sizeof(struct stack));
    p->next=NULL;
    q = (STACK)malloc(sizeof(struct stack));
    for (j=0;j<5;j++)
    {
        p->c[100]='\0';
        gets(p->c);
        p->a = transform(p->c);
        printf("%d\n",p->a);
        p->next = s->next;
        s->next = p;
        if (s->next->c[0] == '+')
        {
            q->a=s->next->next->a + s->next->next->next->a;
            q->next = s->next->next->next->next;
            s->next = q;
        }
        else if (s->next->c[0] == '-' && s->next->c[1]=='\0')
        {
            q->a=s->next->next->next->a - s->next->next->a;
            q->next = s->next->next->next->next;
            s->next = q;
        }
        else if (s->next->c[0] == '*')
        {
            q->a=s->next->next->a * s->next->next->next->a;
            q->next = s->next->next->next->next;
            s->next = q;
        }
        else if (s->next->c[0] == '/')
        {
            q->a=s->next->next->next->a / s->next->next->a;
            q->next = s->next->next->next->next;
            s->next = q;
        }
        p = (STACK)malloc(sizeof(struct stack));
        p->next=NULL;
    }
    printf("%d",s->next->a);
}
