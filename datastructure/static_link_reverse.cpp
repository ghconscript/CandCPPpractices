#include <stdio.h>
#include <stdlib.h>

#define MAXSIZE 100  // 最大容量
#define ElemType int

// 1. 初始化二维数组实现的静态链表
void InitList(int L[][2]) {
    // 初始化备用链表（游标列指向后一个节点）
    for (int i = 0; i < MAXSIZE - 1; i++) {
        L[i][1] = i + 1;  // 第二列存游标
    }
    L[MAXSIZE - 1][1] = -1;  // 最后一个节点游标为-1
    L[0][1] = -1;  // 头节点（下标0）游标为-1（空表）
}

// 2. 从备用链表申请空闲节点（返回行索引）
int Malloc_SL(int L[][2]) {
    int i = L[0][1];  // 备用链表的第一个节点索引
    if (L[0][1] != -1) {
        L[0][1] = L[i][1];  // 更新备用链表头
    }
    return i;
}

// 3. 尾插法插入元素（用于测试）
void InsertTail(int L[][2], ElemType e) {
    int i = Malloc_SL(L);  // 申请空闲节点
    if (i == -1) {
        printf("链表已满，无法插入\n");
        return;
    }
    L[i][0] = e;  // 第一列存数据
    L[i][1] = -1;  // 新节点为尾节点，游标为-1

    // 找到当前尾节点（从头节点开始遍历）
    int p = 0;  // 头节点索引
    while (L[p][1] != -1) {
        p = L[p][1];
    }
    L[p][1] = i;  // 尾节点游标指向新节点
}

// 4. 静态链表逆置（核心算法）
void ReverseList(int L[][2]) {
    // 空表或只有一个节点，无需逆置
    if (L[0][1] == -1 || L[L[0][1]][1] == -1) {
        return;
    }

    int pre = -1;       // 前驱节点索引
    int current = L[0][1];  // 当前节点索引（第一个有效节点）
    int next;           // 临时保存下一个节点索引

    while (current != -1) {
        next = L[current][1];  // 保存当前节点的下一个节点
        L[current][1] = pre;   // 反转游标：指向pre
        pre = current;          // 前驱后移
        current = next;         // 当前节点后移
    }

    // 更新头节点游标为原尾节点（新首节点）
    L[0][1] = pre;
}

// 5. 打印链表（验证结果）
void PrintList(int L[][2]) {
    int p = L[0][1];  // 从第一个有效节点开始
    if (p == -1) {
        printf("链表为空\n");
        return;
    }
    printf("静态链表元素：");
    while (p != -1) {
        printf("%d ", L[p][0]);  // 打印第一列的数
        p = L[p][1];             // 按第二列游标移动
    }
    printf("\n");
}

// 测试
int main() {
    int L[MAXSIZE][2];  // 二维数组：[行][0:数据, 1:游标]
    InitList(L);

    // 插入数据：1->2->3->4->5
    InsertTail(L, 1);
    InsertTail(L, 2);
    InsertTail(L, 3);
    InsertTail(L, 4);
    InsertTail(L, 5);
    printf("逆置前：");
    PrintList(L);  // 输出：1 2 3 4 5

    // 逆置操作
    ReverseList(L);
    printf("逆置后：");
    PrintList(L);  // 输出：5 4 3 2 1

    return 0;
}

