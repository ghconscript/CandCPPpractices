#include<stdio.h>
int isInf(int m,int n);
int cal(int m ,int n); 
int main (){
	int m,n;
	printf("please input a fraction (m/n))  (0< m< n<=100):");
	scanf("%d/%d",&m,&n);
	printf("%d/%d it's accuracy value is:0." "\n\tand it is a infinite cyclic fraction from %d\n" "\tdigit to %d digit after decimal point.\n",m,n);
}

