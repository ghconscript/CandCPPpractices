#include <stdio.h>
#include <math.h>
int main()
{
    int i;
    int sum;
    for (i = 1000; i < 10000; i++)
    {
        int tmp = i;
        int a[4]={0};
        int j;
        for (j = 0; tmp != 0; j++)
        {
            
            a[j] = tmp % 10;
            tmp=tmp / 10;

        }
        sum = pow(a[0],4)+pow(a[1],4)+pow(a[2],4)+pow(a[3],4);
        if (sum ==i){
            printf("%d\t",i);
        }
    }
    return 0;
}
