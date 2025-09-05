#include <stdio.h>
#include <stdlib.h>
//定义一个宏常量N，代表一个数值80，用于表示字符数组的长度等用途
#define N 80

// 函数声明，MyStrcat函数用于连接两个字符串，接收两个字符指针作为参数
char * MyStrcat(char *dstStr, char *srcStr);

int main()
{
    char first[2 * N];    // 定义一个字符数组first，用于存储第一个输入的字符串，长度为2 * N
    char second[N];       // 定义一个字符数组second，用于存储第二个输入的字符串，长度为N
    char *result = NULL;  // 定义一个字符指针result，初始化为NULL，用于存储连接后的字符串

    // 提示用户输入第一个字符串
    printf("Input the first string\n");
    scanf("%s", first);   // 使用scanf函数读取用户输入的第一个字符串，存储到first数组中

    // 提示用户输入第二个字符串
    printf("Input the second string\n");
    scanf("%s", second);  // 使用scanf函数读取用户输入的第二个字符串，存储到second数组中

    result = MyStrcat(first, second);  // 调用MyStrcat函数连接first和second字符串，结果存储在result指针指向的位置

    // 输出连接后的字符串
    printf("The result is %s\n", result);

    return 0;
}

// MyStrcat函数的定义，用于连接两个字符串
// 参数dstStr是目标字符串的首地址，srcStr是源字符串的首地址
char * MyStrcat(char *dstStr, char *srcStr)
{
    char *pStr = dstStr;  // 保存目标字符串的起始地址到pStr指针

    // 移动dstStr指针到目标字符串的末尾（即'\0'字符处）
    while (*dstStr!= '\0')
    {
        dstStr++;
    }

    // 将源字符串中的字符逐个复制到目标字符串的末尾
    for (; *srcStr!= '\0'; dstStr++, srcStr++)
    {
        *dstStr = *srcStr;
    }

    *dstStr = '\0';  // 在连接后的字符串末尾添加'\0'，表示字符串结束

    return pStr;  // 返回连接后的字符串的起始地址（即最初的目标字符串的起始地址）
}
