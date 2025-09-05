#include <stdio.h>
#include <string.h>

int main() {
    int n, m;
    printf("���ж��ٸ���?");
    scanf("%d", &n);
    printf("���ƶ��ٸ�?");
    scanf("%d", &m);
    int arr[n];
    int backup[m];
    char input[100];
    printf("����,��Ϊ�������%d������\n", n);
    scanf("%s", input);

    // �������ַ�������Ϊ��������
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

    m %= n;  // ����m����n�����

    // �������m����
    for (i = n - m; i < n; i++) {
        backup[i-(n - m)] = arr[i];
    }

    // �ƶ�ǰ��n - m����
    for (i = n - m - 1; i >= 0; i--) {
        arr[i + m]= arr[i];
    }

    // �����ݵ�m�����ŵ�ǰ��
    for (i = 0; i < m; i++) {
        arr[i]= backup[i];
    }

    printf("�ƶ���˳��Ϊ��\n");
    for (i = 0; i < n; i++) {
        printf("%d", arr[i]);
        if (i!= n - 1) {
            printf(",");
        }
    }
    printf("\n");
    return 0;
}

