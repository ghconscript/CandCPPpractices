#include<stdio.h>
void inverse(char str[],int m,int n){
	void inverse(char str[], int m, int n) {
    char temp[100];
    int i;
    // 复制要逆序的部分到temp数组并逆序
    for (i = 0; i < n; i++) {
        temp[i] = str[m - 1 + n - 1 - i];
    }
    temp[i] = '\0';

    // 将原字符串中要替换的部分往后移动n个位置
    for (i = strlen(str); i >= m - 1 + n; i--) {
        str[i] = str[i - n];
    }
    // 将逆序后的字符复制回原字符串
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
