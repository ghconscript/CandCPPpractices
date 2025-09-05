#include<stdio.h>
unsigned short ReadNumber(int num[])
{
    unsigned short i = 0;
    while (scanf("%d",&num[i]) != -1){
	
    
       i++;
       
    }
    return i;
}
void SortNumberDescending(int a[], unsigned short n)
{
    int t;
    int i,j;
    int temp; 
    for (i = 0; i < n - 1; i++)
    {
        t = i;
        for (j = i; j <= n - 1; j++)
        {
            if (a[i] < a[j])
            {
                t = j;
            }
            
        }
        if (t != j)
            {
                temp = a[i];
                a[i] = a[t];
                a[t] = temp;
            }
    }
}
void SummingAveraging(int num[], unsigned short n, int *pSum, float *pAver)
{
    int i;
    for (i = 0; i < n - 1; i++)
    {
        *pSum += num[i];
    }
    * pAver = (*pSum*1.0)/ n;
}
void  PrintNumber(int num[], unsigned short n){
    int i;
    for(i=0;i<n-1;i++)
    printf("%d\n",num[i]);
}
int main()
{
    int sum;float Aver;
    int num[21]={0};
    int *pSum=&sum;
    float *pAver=&Aver;
    printf("Input Numbers:");
    int n=ReadNumber(num);
    SortNumberDescending(num,n);
    PrintNumber(num,n);
    SummingAveraging(num,n,pSum,pAver);
    printf("\nSort in descending order:\n");
    printf("\nSum=%d,Aver=%.2f\n",sum,Aver);
    return 0;
}
