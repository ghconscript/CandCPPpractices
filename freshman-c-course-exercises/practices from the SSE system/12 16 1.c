#include<stdio.h>
#include<string.h>
int main() {
	char str[15];
	printf("Input string:");
	gets(str);
	char *pStart=str;
	int len = strlen(str);
	char *pEnd = str + len - 1;
	int i;
	while (pStart < pEnd) {
        if (*pStart!= *pEnd) {
            break;
        }
        pStart++;
        pEnd--;
    }

    if (pStart >= pEnd) {
        printf("Yes!\n");
    } else {
        printf("No!\n");
    }

	
	return 0;
}
