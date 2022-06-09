#include <stdio.h>
#include <stdlib.h>
typedef struct polynode *polypointer;
struct polynode{
    int coef;
    int exp;
    polypointer link;
};
polypointer Create(int n)
{
    getchar();
    int i;
    polypointer head,p,rear;
    rear = NULL;
    for (i=n;i>=0;i--)
    {
        p = (polypointer)malloc(sizeof(struct polynode));
        if (i==n)
            head = p;
        if (p==NULL)
            printf("Error!");
        else
        {
            scanf ("%d",&p->coef);
            p->exp = i;
            if (i!=n)
                rear->link = p;
            rear = p;
        }
    }
    p->link = NULL;
    return head;
}
polypointer Attach (int c,int e,polypointer d)
{
    polypointer x,f;
    x = (polypointer)malloc(sizeof(struct polynode));
    f=d;
    while(d->link!=NULL)
        d=d->link;
    x->coef = c;
    x->exp = e;
    d->link = x;
    x->link = NULL;
    return f;
}
void Print(polypointer a)
{
    polypointer p;
    p=a;
    while (p!=NULL && p->coef!=0 )
    {
        printf("%d %d ",p->coef,p->exp);
        p = p->link;
    }
    printf("\n");
}
polypointer PolyAdd(polypointer a, polypointer b)
{
    polypointer d,p,q;
    int x;
    p=a, q=b;
    d = (polypointer)malloc(sizeof(struct polynode));
    d->link=NULL;
    while((p!=NULL) && (q!=NULL))
    {
        if (p->exp == q->exp)
        {
            x=p->coef + q->coef;
            if (x!=0)
                d=Attach(x,p->exp,d);
            p=p->link, q=q->link;
        }
        else if (p->exp > q->exp)
        {
            d=Attach(p->coef,p->exp,d);
            p=p->link;
        }
        else if (p->exp < q->exp)
        {
            d=Attach(q->coef,q->exp,d);
            q=q->link;
        }
    }
    while (p!=NULL)
    {
        d=Attach(p->coef,p->exp,d);
        p=p->link;
    }
    while (q!=NULL)
    {
        d=Attach(q->coef,q->exp,d);
        q=q->link;
    }
    d=d->link;
    return d;
}
polypointer PolyMul(polypointer a, polypointer b)
{
    polypointer p,q,r,t;
    int i,j,c,e;
    r = (polypointer)malloc(sizeof(struct polynode));
    r->coef = 0;
    r->exp = 0;
    r->link=NULL;
    p=a;
    while(p!=NULL)
    {
        q=b;
        t = (polypointer)malloc(sizeof(struct polynode));
        t->link=NULL;
        while(q!=NULL)
        {
            c = p->coef * q->coef;
            e = p->exp + q->exp;
            t = Attach(c,e,t);
            q = q->link;
        }
        t=t->link;
        r = PolyAdd(r,t);
        p=p->link;
    }
    return r;
}
int main()
{
    int n,m,i;
    scanf ("%d %d",&n,&m);
    polypointer a,b,c;
    a = Create(n);
    b = Create(m);
    printf("\n");
    c = PolyMul(a,b);
    Print(c);
}

polypointer PolyMin(polypointer a, polypointer b)
{
    polypointer p,q,d,c;
    double x;
    p=a,q=b;
    d=c=NULL;
    while (p->exp!=NULL && q->exp!=NULL)
    {
        if (p->exp == q->exp)
        {
            x=p->coef - q->coef;
            if (x!=0)
                d=Attach(x,p->exp,d);
            p=p->link, q=q->link;
        }
        if (p->exp > q->exp)
        {
            d=Attach(p->coef,p->exp,d);
            p=p->link;
        }
        if (p->exp < q->exp)
        {
            d=Attach(q->coef,q->exp,d);
            q=q->link;
        }
    }
    while (p!=NULL)
    {
        d=Attach(p->coef,p->exp,d);
        p=p->link;
    }
    while (q!=NULL)
    {
        d=Attach(q->coef,q->exp,d);
        q=q->link;
    }
    d->link=NULL;
    p=c;
    c=c->link;
    return c;
}
