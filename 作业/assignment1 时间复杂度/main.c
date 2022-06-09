#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <windows.h>
#include <time.h>
#include <mmsystem.h>
#pragma comment(lib,"Winmm.lib")

int main()
{
    unsigned n=0;
    unsigned m=0;
    int i,j,k,l;
    int begintime,endtime;
        printf("please input n or exit(0):");
        scanf("%ld",&n);
        if (n==0)
            exit(0);
        else
            {
            printf("1. log(n)");
            begintime=clock();
            for (i=1;i<=n;i*=2)
            {
                j=1;
            }
            endtime = clock();
            printf("\nrun_time£º%dms\n\n",endtime-begintime);

            printf("2. sqrt(n)");
            m = sqrt(n);
            begintime=clock();
            for (i=0;i<m;i++)
                j=1;
            endtime = clock();
            printf("\nrun_time£º%dms\n\n",endtime-begintime);

            printf("3. n");
            begintime=clock();
            for (i=0;i<n;i++)
                j=1;
            endtime = clock();
            printf("\nrun_time£º%dms\n\n",endtime-begintime);

            printf("4. pow(n,2)");
            begintime=clock();
            for (i=0;i<n;i++)
            {
                for (j=0;j<n;j++)
                    k=1;
            }
            endtime = clock();
            printf("\nrun_time£º%dms\n\n",endtime-begintime);

            printf("5. pow(n,3)");
            begintime=clock();
            for (i=0;i<n;i++)
            {
                for (j=0;j<n;j++)
                {
                    for (k=0;k<n;k++)
                        l=1;
                }
            }
            endtime = clock();
            printf("\nrun_time£º%dms\n\n",endtime-begintime);

            printf("6. pow(2,n)");
            m = pow(2,n);
            begintime=clock();
            for (i=0;i<m;i++)
            {
                l=1;
            }
            endtime = clock();
            printf("\nrun_time£º%dms\n\n",endtime-begintime);

            printf("7. pow(3,n)");
            m = pow(3,n);
            begintime=clock();
            for (i=0;i<m;i++)
            {
                l=1;
            }
            endtime = clock();
            printf("\nrun_time£º%dms\n\n",endtime-begintime);

            printf("8. n!");
            m=1;
            for (i=1;i<=n;i++)
            {
                m=m*i;
            }
            begintime=clock();
            for (i=0;i<m;i++)
            {
                l=1;
            }
            endtime = clock();
            printf("\nrun_time£º%dms\n\n",endtime-begintime);

            printf("9. pow(n,n)");
            m = pow(n,n);
            begintime=clock();
            for (i=0;i<m;i++)
            {
                l=1;
            }
            endtime = clock();
            printf("\nrun_time£º%dms\n\n",endtime-begintime);
        }
}
