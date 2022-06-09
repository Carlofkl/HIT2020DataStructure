#include <stdio.h>
#include <stdlib.h>
#include <math.h>
int c=0;
void INPUT(int *p,int *q)
{
    printf("输入两个整数:");
    scanf("%d %d",p,q);
}
int Step1(int x)
{
    c++;
    printf("向左滑步\n");
    return x+1;
}
int Step2(int x)
{
    c++;
    printf("向右滑步\n");
    return x-1;
}
int Jump(int x)
{
    c++;
    printf("向右跳步\n");
    return x/2;
}
SHIFT(a,b)
{
    if (b%2!=0)
    {
        int c=(b+1)/2;
        int d=(b-1)/2;
        if (abs(c-a)>=b-a || abs(d-a)>=b-a)
        {
            while (a!=b)
            {
                b=Step2(b);
            }
        }
        else if (abs(c-a)<abs(d-a))
        {
            b=Step1(b);
            b=Jump(b);
            SHIFT(a,b);
        }
        else if (abs(c-a)>abs(d-a))
        {
            b=Step2(b);
            b=Jump(b);
            SHIFT(a,b);
        }
    }
    else
    {
        if (abs(b/2 - a) > abs(b - a))
        {
            if (b>a)
            {
                while(a!=b)
                {
                    b=Step2(b);
                    return 0;
                }
            }
            else if (b<a)
            {
                while(a!=b)
                {
                    b=Step1(b);
                    return 0;
                }
            }
            else
            {
                return 0;
            }
        }
        else if (abs(b/2 - a) < abs(b - a))
        {
            b=Jump(b);
            if (b>a)
                SHIFT(a,b);
            else
            {
                while(a!=b)
                {
                    b=Step1(b);
                }
            }
        }
        else
        {
            b=Jump(b);
            return 0;
        }
    }
}
void OUTPUT()
{
    printf("Bob最少需要%d次才能捡到篮球.",c);
}
int main()
{
    int N,K,x;
    int *p,*q;
    p=&N,q=&K;
    INPUT(p,q);
    x=K;
    SHIFT(N,x);
    OUTPUT();
}
