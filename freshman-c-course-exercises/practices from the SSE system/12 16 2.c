#include<stdio.h>
void inverse(char str[],int m,int n){
	void inverse(char str[], int m, int n) {
    char temp[100];
    int i;
    // ����Ҫ����Ĳ��ֵ�temp���鲢����
    for (i = 0; i < n; i++) {
        temp[i] = str[m - 1 + n - 1 - i];
    }
    temp[i] = '\0';

    // ��ԭ�ַ�����Ҫ�滻�Ĳ��������ƶ�n��λ��
    for (i = strlen(str); i >= m - 1 + n; i--) {
        str[i] = str[i - n];
    }
    // ���������ַ����ƻ�ԭ�ַ���
    for (i = 0; i < n; i++) {
        str[m - 1 + i] = temp[i];
    }
}

	
}
int main(){
	int m,n;
	char str[100];
	printf("input m,n:");
	scanf("%d,%d",&m,&n);
	getchar();
	printf("input the string:");
	gets(str);
	inverse(str,m,n);
	printf("the inverse string:%s",str);
	return 0;
}
