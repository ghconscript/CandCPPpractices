#include <stdio.h>
#include <stdlib.h>
//����һ���곣��N������һ����ֵ80�����ڱ�ʾ�ַ�����ĳ��ȵ���;
#define N 80

// ����������MyStrcat�����������������ַ��������������ַ�ָ����Ϊ����
char * MyStrcat(char *dstStr, char *srcStr);

int main()
{
    char first[2 * N];    // ����һ���ַ�����first�����ڴ洢��һ��������ַ���������Ϊ2 * N
    char second[N];       // ����һ���ַ�����second�����ڴ洢�ڶ���������ַ���������ΪN
    char *result = NULL;  // ����һ���ַ�ָ��result����ʼ��ΪNULL�����ڴ洢���Ӻ���ַ���

    // ��ʾ�û������һ���ַ���
    printf("Input the first string\n");
    scanf("%s", first);   // ʹ��scanf������ȡ�û�����ĵ�һ���ַ������洢��first������

    // ��ʾ�û�����ڶ����ַ���
    printf("Input the second string\n");
    scanf("%s", second);  // ʹ��scanf������ȡ�û�����ĵڶ����ַ������洢��second������

    result = MyStrcat(first, second);  // ����MyStrcat��������first��second�ַ���������洢��resultָ��ָ���λ��

    // ������Ӻ���ַ���
    printf("The result is %s\n", result);

    return 0;
}

// MyStrcat�����Ķ��壬�������������ַ���
// ����dstStr��Ŀ���ַ������׵�ַ��srcStr��Դ�ַ������׵�ַ
char * MyStrcat(char *dstStr, char *srcStr)
{
    char *pStr = dstStr;  // ����Ŀ���ַ�������ʼ��ַ��pStrָ��

    // �ƶ�dstStrָ�뵽Ŀ���ַ�����ĩβ����'\0'�ַ�����
    while (*dstStr!= '\0')
    {
        dstStr++;
    }

    // ��Դ�ַ����е��ַ�������Ƶ�Ŀ���ַ�����ĩβ
    for (; *srcStr!= '\0'; dstStr++, srcStr++)
    {
        *dstStr = *srcStr;
    }

    *dstStr = '\0';  // �����Ӻ���ַ���ĩβ���'\0'����ʾ�ַ�������

    return pStr;  // �������Ӻ���ַ�������ʼ��ַ���������Ŀ���ַ�������ʼ��ַ��
}
