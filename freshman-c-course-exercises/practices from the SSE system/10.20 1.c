#include<stdio.h>
#include<string.h>
void sort(char*strings[],int n)
{
    int i, j;
    for (i = 0; i < n - 1; i++)
    {
        for (j = i + 1; j < n; j++)
        {
            if (strcmp(strings[i], strings[j]) > 0)
            {
                char temp[20];
                strcpy(temp, strings[i]);
                strcpy(strings[i], strings[j]);
                strcpy(strings[j], temp);
            }
        }


    }
}
    int main()
    {
        int n;
        printf("«Î ‰»În(n<10):");
        scanf("%d", &n);
        getchar();
        char* strings[n];
        int i;
        for (i = 0; i < n; i++)
        {
            gets(strings[i]);
            getchar();
            strings[i][strcspn(strings[i], "\n")] = '\0';
        }
        sort(strings,n);
         for (i = 0; i < n; i++)
        {
            puts(strings[i]);
        
        }
    }
