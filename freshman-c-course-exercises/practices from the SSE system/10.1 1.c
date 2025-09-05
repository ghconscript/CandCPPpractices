#include<stdio.h>
double fac(int i){
	int j;
	double sum=1;
	for (j=1;j<=i;j++){
		sum*=j;
		
	}
	return sum;
}
int main(){
	
	double e=1.0;
	int count=0;
	int temp=0;
	do{
		count++;
		temp=1.0/fac(count);
		e+=temp;
	
		printf("e = %.8f, count = %d\n",e,count);
	}while(temp>=1e-7);
		
		
		
		
	
	return 0;
	
}
