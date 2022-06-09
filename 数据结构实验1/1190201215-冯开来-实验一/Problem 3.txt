#include <stdio.h>
#include <stdlib.h>
#include <string.h>
const int N = 100;
int main()
{
    char s[50];
    s[50]='0';
    int len,count,i,L;
    gets(s);
    len = strlen(s);
    for (L=1; L<len/2+1; L++)
    {
        if (len%L==0)
        {
            i=L;
            count = 0;
            while (i!=len)
            {
                if (s[i%L] == s[i])
                {
                    count ++;
                    i++;
                }
                else break;
            }
            if (L+count == len)
            {
                printf("1");
                return 0;
            }
        }
        else continue;
    }
    printf("0");
    return 0;
}
