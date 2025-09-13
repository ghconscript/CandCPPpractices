#include <stdio.h>
#include <stdlib.h>

#define MAXSIZE 100  // �������
#define ElemType int

// 1. ��ʼ����ά����ʵ�ֵľ�̬����
void InitList(int L[][2]) {
    // ��ʼ�����������α���ָ���һ���ڵ㣩
    for (int i = 0; i < MAXSIZE - 1; i++) {
        L[i][1] = i + 1;  // �ڶ��д��α�
    }
    L[MAXSIZE - 1][1] = -1;  // ���һ���ڵ��α�Ϊ-1
    L[0][1] = -1;  // ͷ�ڵ㣨�±�0���α�Ϊ-1���ձ�
}

// 2. �ӱ�������������нڵ㣨������������
int Malloc_SL(int L[][2]) {
    int i = L[0][1];  // ��������ĵ�һ���ڵ�����
    if (L[0][1] != -1) {
        L[0][1] = L[i][1];  // ���±�������ͷ
    }
    return i;
}

// 3. β�巨����Ԫ�أ����ڲ��ԣ�
void InsertTail(int L[][2], ElemType e) {
    int i = Malloc_SL(L);  // ������нڵ�
    if (i == -1) {
        printf("�����������޷�����\n");
        return;
    }
    L[i][0] = e;  // ��һ�д�����
    L[i][1] = -1;  // �½ڵ�Ϊβ�ڵ㣬�α�Ϊ-1

    // �ҵ���ǰβ�ڵ㣨��ͷ�ڵ㿪ʼ������
    int p = 0;  // ͷ�ڵ�����
    while (L[p][1] != -1) {
        p = L[p][1];
    }
    L[p][1] = i;  // β�ڵ��α�ָ���½ڵ�
}

// 4. ��̬�������ã������㷨��
void ReverseList(int L[][2]) {
    // �ձ��ֻ��һ���ڵ㣬��������
    if (L[0][1] == -1 || L[L[0][1]][1] == -1) {
        return;
    }

    int pre = -1;       // ǰ���ڵ�����
    int current = L[0][1];  // ��ǰ�ڵ���������һ����Ч�ڵ㣩
    int next;           // ��ʱ������һ���ڵ�����

    while (current != -1) {
        next = L[current][1];  // ���浱ǰ�ڵ����һ���ڵ�
        L[current][1] = pre;   // ��ת�α꣺ָ��pre
        pre = current;          // ǰ������
        current = next;         // ��ǰ�ڵ����
    }

    // ����ͷ�ڵ��α�Ϊԭβ�ڵ㣨���׽ڵ㣩
    L[0][1] = pre;
}

// 5. ��ӡ������֤�����
void PrintList(int L[][2]) {
    int p = L[0][1];  // �ӵ�һ����Ч�ڵ㿪ʼ
    if (p == -1) {
        printf("����Ϊ��\n");
        return;
    }
    printf("��̬����Ԫ�أ�");
    while (p != -1) {
        printf("%d ", L[p][0]);  // ��ӡ��һ�е���
        p = L[p][1];             // ���ڶ����α��ƶ�
    }
    printf("\n");
}

// ����
int main() {
    int L[MAXSIZE][2];  // ��ά���飺[��][0:����, 1:�α�]
    InitList(L);

    // �������ݣ�1->2->3->4->5
    InsertTail(L, 1);
    InsertTail(L, 2);
    InsertTail(L, 3);
    InsertTail(L, 4);
    InsertTail(L, 5);
    printf("����ǰ��");
    PrintList(L);  // �����1 2 3 4 5

    // ���ò���
    ReverseList(L);
    printf("���ú�");
    PrintList(L);  // �����5 4 3 2 1

    return 0;
}

