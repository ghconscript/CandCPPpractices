#include <stdio.h>
#include <string.h>

int main() {
    int n, m;
    printf("共有多少个数?");
    scanf("%d", &n);
    printf("后移多少个?");
    scanf("%d", &m);
    int arr[n];
    int backup[m];
    char input[100];
    printf("请以,号为间隔输入%d个数。\n", n);
    scanf("%s", input);

    // 将输入字符串解析为整数数组
    int i, j = 0;
    int num = 0;
    int sign = 1;
    for (i = 0; i < strlen(input); i++) {
        if (input[i] == ',') {
            arr[j]= num * sign;
            num = 0;
            sign = 1;
            j++;
        } else if (input[i] == '-') {
            sign = -1;
        } else {
            num = num * 10+(input[i] - '0');
        }
    }
    arr[j]= num * sign;

    m %= n;  // 处理m大于n的情况

    // 保存最后m个数
    for (i = n - m; i < n; i++) {
        backup[i-(n - m)] = arr[i];
    }

    // 移动前面n - m个数
    for (i = n - m - 1; i >= 0; i--) {
        arr[i + m]= arr[i];
    }

    // 将备份的m个数放到前面
    for (i = 0; i < m; i++) {
        arr[i]= backup[i];
    }

    printf("移动后顺序为：\n");
    for (i = 0; i < n; i++) {
        printf("%d", arr[i]);
        if (i!= n - 1) {
            printf(",");
        }
    }
    printf("\n");
    return 0;
}

