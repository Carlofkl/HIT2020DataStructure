#include <stdio.h>
#include <stdlib.h>
char s;
int main()
{
    char s;
    int d[100],x,top=-1;
    for (s=getchar();s!='!';s=getchar())
	{
	    if (s==' ')
            continue;
	    if (s=='+')
        {
            d[top-1] += d[top];
            top--;
        }
        else if (s=='*')
        {
            d[top-1] *= d[top];
            top--;
        }
        else if (s=='/')
        {
            d[top-1] /= d[top];
            top--;
        }
        else if (s=='-')
        {
            s = getchar();
            if (s == ' ')
            {
                d[top-1] -=d[top];
                top--;
            }
            else
            {
                x=0;
                while (s<='9' && s>='0')
                {
                    x = 10*x + s-'0';
                    s = getchar();
                }
                top++;
                d[top] = -x;
            }
        }
        else
        {
            x=0;
            while (s<='9' &&s>='0')
            {
                x = x*10 + s-'0';
                s = getchar();
            }
            top++;
            d[top] = x;
        }
	}
	printf("%d",d[0]);
}
