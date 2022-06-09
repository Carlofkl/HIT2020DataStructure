#include <stdio.h>
#include <stdlib.h>
/*--------Â·¾¶Ñ¹Ëõ-------*/
int Find(int x,int a[])
{
    if(a[x]!=x)
        a[x] = Find(a[x],a);
    return a[x];
}
int find (int p, int a[])
{
    while(p != a[p])
    {
        a[p]=a[a[p]];
        a = a[p];
    }
    return a;
}
/*--------Â·¾¶Ñ¹Ëõ-------*/
int main()
{
    int a,b,sum=0;
    //freopen("problem3_sample.txt","r",stdin);
	//freopen("problem3.out","w",stdout);
    scanf("%d%d",&a,&b);
    int Infect[a];
    for(int i=0; i<a; i++)
        Infect[i] = i;
    int s,x,y,m,n;
    for(int i=1; i<=b; i++)
    {
        scanf("%d%d",&s,&x);
        m = Find(x,Infect);
        for(int j=1; j<s; j++)
        {
            scanf("%d",&y);
            n = Find(y,Infect);
            if(m!=n)
                Infect[n] = m;
        }
    }
    for(int i=0; i<a; i++)
        if(Find(i,Infect)==Find(0,Infect))
            ++sum;
    printf("%d",sum);
    return 0;
}
