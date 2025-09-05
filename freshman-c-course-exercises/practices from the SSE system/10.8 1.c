#include<stdio.h>
int isTPrime(long int a){
	int j;
	int cnt;
	for (j=1;j<=a;a++){
		if(a%j==0)
		cnt ++;
	}
	if (cnt==3)
	return 1;
	else 
	return 0;
	
}
int main(){
	int n; 
	scanf("%d",&n);
	int i;
	long int a[n];
	for(i=0;i<n;i++){
		scanf("%ld",&a[n]);
	}
	int k;
	for (k=0;k<n;k++){
		if(isTPrime(a[n]))
		printf("YES");
		else
		printf("NO");
	} 
	return 0;
}
