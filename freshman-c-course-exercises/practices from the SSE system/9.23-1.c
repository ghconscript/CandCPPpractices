#include<stdio.h>


int a=1,square;
int i,n;

int main(){
    printf("This program prints a table of squares.\n" "Enter number of entries in table:\n");
    scanf("%d",&n);
    
    for(i=0;i<n;i++){
        int sum=a*a;
        a++;
        printf("%10d%10d\n",a,sum);
        
    }
    return 0;
}
