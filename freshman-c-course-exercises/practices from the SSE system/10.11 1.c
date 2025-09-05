#include<stdio.h>
#define N 5
int checkR(int matrix[5][5]);
int checkC(int matrix[5][5]);
int checkD(int matrix[5][5]);
int main() {
	int matrix[5][5] = {
		{17, 24, 1, 8, 15},
		{23, 5, 7, 14, 16},
		{4, 6, 13, 20, 22},
		{10, 12, 19, 21, 3},
		{11, 18, 25, 2, 9}
	};
	
	int Rflag=checkR(matrix);
	int Cflag=checkC(matrix);
	if(Rflag==1&&Cflag==1)
	printf("It is a magic square!\n");
	int i,j;
	for (i=0; i<N; i++) {
		for (j=0; j<N; j++) {
			printf("%-4d",matrix[i][j]);
		}
		printf("\n") ;
	}

	return 0;
}
int checkR(int matrix[5][5]) {
	int i=0; 
	int j=0;
	int flag=1;
	int sum[5]= {0};
	for (j=0; j<N; j++) {
		sum[0]+=matrix[0][j];
	}
	for (i=1; i<N; i++) {
		for (j=0; j<N; j++) {
			sum[i]+=matrix[i][j];
		}
		if(sum[i]!=sum[0])
		flag=0;
	}
	return flag;
}
int checkC(int matrix[5][5]) {
	int i=0;
	int j=0;
	int flag=1;
	int sum[5]= {0};
	for (i=0; i<N; i++) {
		sum[0]+=matrix[i][0];
	}
	for (j=1; j<N; j++) {
		for (i=0; i<N; i++) {
			sum[j]+=matrix[j][i];
		}
		if(sum[j]!=sum[0])
		flag=0;
	}
	return flag;
}

