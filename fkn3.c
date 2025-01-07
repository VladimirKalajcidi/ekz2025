#include <stdio.h>

int main(void) {
    int n = 618527444;
    while (n > 0) {
        printf("%d", n % 3);
        n /= 3;
    }
}

// 21201001 12122 001 21 1 +0
/*
0
1
4
9
3 + 6 + 9 + 54 + 162
2 + 3 + 18 + 81 + 2187
*/