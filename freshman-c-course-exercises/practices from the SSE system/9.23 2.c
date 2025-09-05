#include <stdio.h>
#define N 200000
int is_self_defend(int i);

int main() {
    
    printf("It exists following automorphic numbers smaller than 200000:\n");
   
    for (int i = 1; i <= N; i++) {
       
        if (is_self_defend(i)) {
            
            printf("  %ld", i);
        }
    }
    return 0;
}

int is_self_defend(int i) {
    int tmp1 = i;
    int j1 = 1;
    int sqr = i * i;
    int tmp2 = sqr;
    int j2 = 1;
   
    while (tmp1 > 0) {
        tmp1 /= 10;
        j1 *= 10;
    }
   
    while (tmp2 > 0) {
        tmp2 /= 10;
        j2 *= 10;
    }
    
    if (sqr % j2 == i % j1) {
        return 1;
    } else {
        return 0;
    }
}

