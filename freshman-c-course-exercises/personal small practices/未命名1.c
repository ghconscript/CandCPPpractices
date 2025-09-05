#include<stdio.h>
#include<math.h>
void func(int N, int prime[], int *prime_count, int composite[], int *composite_count);
int isprime(int a);
int main()
{
    int N;
    int j = 0;
    int i = 0;
    int pcnt = 0;
    int ccnt = 0;
    int *prime_count = &pcnt;
    int *composite_count = &ccnt;
    int  prime[];
    int composite[];
    if (scanf("%d", &N) == 1)
    {
        if (N >= 10 && N <= 100)
            break;
        else
        {
            while (getchar(N) != '\n');
            printf(¡±Input error! Please input an integer N, 10 <= N <= 100.\n¡±);

        }

    }
    else
    {
        while (getchar(N) != '\n');
        printf(¡±Input error! Please input an integer N, 10 <= N <= 100.\n¡±);
    }
    func(N, prime, prime_count, composite, composite_count);
    printf("%d\n", "%d\n", *prime_count);
    for (i = 0; i <= *prime_count; i++)
    {
        printf("%d"prime[i]);
    }
    printf("%d\n", *composite_count);
    for (j = 0; j <= *composite_count; i++)
    {
        printf("%d"composite[i]);
    }


    void func(int N, int prime[], int *prime_count, int composite[], int *composite_count)
    {
        int i;
        int a[N + 1];
        int ccnt = 0;
        int pcnt = 0;
        for (i = 2; i <= N; i++)
        {
            a[i] = i;
        }
        for (i = 2; i <= sqrt(n); i++)
        {
            for (j = i; j < N; j++)
            {
                if (a[i] != 0) && (a[j] != 0) && (a[j] % a[i] == 0)
                {
                    composite[*prime_count] = j;
                    *composite_count++;

                }
                else
                {
                    prime[*prime_count] = i;
                    *prime_count++;
                }
            }
        }
    }
