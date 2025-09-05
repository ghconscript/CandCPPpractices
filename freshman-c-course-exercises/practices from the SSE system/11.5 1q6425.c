#include<stdio.h>
void fun1(int a[],int n) {
	int i;
	for(i=1; i<=n-2; i++) {
		a[i+2]=a[i]+a[i+1];
	}
}
float fun2(int zi[],int mu[],int n) {
	int i;
	float sum=0.0;
	for(i=1; i<=n; i++) {
		sum+=(1.0*zi[i])/(1.0*mu[i]);
	}
	return sum;
}
int main() {
	float sum;
	int n;
	printf("请输入分式序列前n项和的值:");
	scanf("%d",&n);
	float result;
	int zi[n+1];
	int mu[n+1];
	zi[0]=0;
	zi[1]=2;
	zi[2]=3;
	mu[0]=0;
	mu[1]=1;
	mu[2]=2;
	fun1(zi,n);
	fun1(mu,n);
	result=fun2(zi,mu,n);
	printf("sum=%6.2f",result);
	return 0;
}
