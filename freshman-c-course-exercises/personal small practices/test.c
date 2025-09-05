#include<stdio.h>
#include<stdlib.h>
int main(){
	int a=12;
	int b=5;
	float c;
	
	c=a;
	printf("%f",c);
	
	int*p=&a;
	int*q=malloc(b*sizeof(int));
	/*p=(int*)q;*/
	return 0;
} 
