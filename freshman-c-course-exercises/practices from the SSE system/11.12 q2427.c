#include<stdio.h>
void sort(int *a,int *pmax,int *pmin,int*maxnum,int*pminnum);
int main() {
	int a[24]= {0};
	int max=0,min=0;
	int *pmax=&max;
	int *pmin=&min;
	int maxnum=0,minnum=0;
	int *pmaxnum=&maxnum;
	int *pminnum=&minnum;
	float user;
	int i;
	for(i=0; i<24; i++) {
		printf("��������%d:00��%d:00֮���¼���û���:",i,i+1);
		
		int result = scanf(" %d",&a[i]);
		if (result!= 1) {
			printf("�����������������������\n");
			while (getchar()!= '\n') {}
			i--;
			continue;
		}
		user+=a[i];
	}
	sort(a,pmax,pmin,pmaxnum,pminnum);
	float rate=a[i]/(user*1.0);
	for (i=0; i<24; i++) {

		printf("%2d:00 - %2d:00 %15d %25.1f\n",i,i+1,a[i],rate);

	}
	printf("����¼����%d������%2d:00��%2d:00֮��\n",max,maxnum,maxnum+1);
	printf("��С��¼����%d������%2d:00��%2d:00֮��\n",min,minnum,minnum+1);
}
void sort(int *a,int *pmax,int *pmin,int*pmaxnum,int*pminnum) {
	*pmax=a[0];
	*pmin=a[0];
	int i;
	for(i=0; i<24; i++) {
		if(*pmax<a[i]) {
			*pmax=a[i];
			*pmaxnum=i;

		}
		if(*pmin>a[i]) {
			*pmin=a[i];
			*pminnum=i;
		}
	}
}
