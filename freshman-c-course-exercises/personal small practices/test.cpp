#include<stdio.h>

int main(){
	int number[4]={0};
	int i=0;
	for (;i<4;i++){
		printf("%d",number[i]);
	}
	number[4]=5;
	printf("%d",number[4]);
	return 0;
 
}
  
