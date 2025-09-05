#include<stdio.h>
#define N 15
void  CaculateYH(int a[][N], int  n);
void  PrintYH(int a[][N], int  n);
int main() {
	int a[N][N];
	int n;
	printf("Input n(n<15):\n");
	scanf("%d",&n);
	CaculateYH(a, n);
	PrintYH(a, n);
	return  0;
}
void  CaculateYH(int a[N][N], int  n) {
	int i=0;
	int j;
	for(i=0; i<n; i++) {

		for(j=0; j<=i; j++) {

			if(j==0||j==i)
				a[i][j]=1;
			else
				a[i][j]=a[i-1][j-1]+a[i-1][j];
		}
	}
}
void  PrintYH(int a[N][N], int  n) {
	int i;
	int j;
	for(i=0; i<n; i++) {

		for(j=0; j<=i; j++) {

			printf("%5d",a[i][j]);
		}
		printf("\n");
	}

}
