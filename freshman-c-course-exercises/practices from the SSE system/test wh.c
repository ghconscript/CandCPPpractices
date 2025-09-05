#include<stdio.h>
int main(){
	int a=1;
	int b=0;
	if(!a)
		b++;
	else if(a==0)
		if(a) b+=2;
		else b+=3;
	printf("%d\n",b);
	int x=10;
	while(x--);
	printf("x=%d\n",x);
}
