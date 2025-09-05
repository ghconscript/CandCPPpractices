#include<stdio.h>
float FindMax(float income[],int n){
	float max=0;
	int j;
	for (j=0;j<n;j++){
		if (income[j]>max){
			max=income[j];
		}
	}
	return max;
}
int main(){
	int n,i;
	float maxincome;
	scanf("%d",&n);
	float income[30]={0};
	for (i=0;i<n;i++){
		scanf("%f",&income[i]);
	}
	maxincome=FindMax(income,n);
	printf("The highest income is %10.2f\n",maxincome);
	return 0;
}

