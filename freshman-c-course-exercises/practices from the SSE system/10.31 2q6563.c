#include<stdio.h>
#include<string.h>
int Find(char*str) {
	int len = strlen(str);
	int maxlen = 1;
	int i, j, k;
	for (i = 1; i < len; i++) {
		for (j = i - 1, k = i + 1; str[j] == str[k] && j >=0 && k < len; j--, k++) {
			if (k - j + 1 > maxlen)
				maxlen = k - j + 1;
		}
		if (str[i] == str[i + 1]) {
			for (j = i - 1, k = i + 2; str[j] == str[k] && j >= 0 && k < len; j--, k++) {
				if (k - j + 1 > maxlen)
					maxlen = k - j + 1;
			}
		}

	}
	return maxlen;
}
int main() {
	char str[1000] ;
	printf("Please input string:\n");
	scanf("%s", str);
	int result = Find(str);
	printf("%5d", result);
	return 0;
}
