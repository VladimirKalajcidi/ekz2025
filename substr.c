#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <stdio.h>

void prefix(const char *pat, int *pi, int n) {
    int q = 0;  // length of the previous longest prefix suffix
    pi[0] = 0;  // pi[0] is always 0

    for (int i = 1; i < n; i++) {  // Start from 1 since pi[0] is 0
        while (q > 0 && pat[q] != pat[i]) {
            q = pi[q - 1];  // Check the previous prefix length
        }
        if (pat[q] == pat[i]) {
            q++;  // If there's a match, increase length of the current prefix
        }
        pi[i] = q;  // Set the prefix length for the substring
    }
}

int kmp(const char *text, const char *pat, int n, int m) {
    int cnt = 0;
    int pi[m];

    prefix(pat, pi, m); // Compute the prefix function

    int q = 0; // Number of characters matched

    for (int i = 0; i < n; i++) {
        while (q > 0 && pat[q] != text[i]) {
            q = pi[q - 1]; // Fall back in the pattern
        }
        if (pat[q] == text[i]) {
            q++; // Next character matched
        }
        if (q == m) { // Found a match
            cnt++; // Increment count of matches
            q = pi[q - 1]; // Allow search for the next match
        }
    }
    return cnt;
}


int main() {
    // Примеры строк для проверки
    const char *test1 = "28012012-пересдача"; // 1
    const char *test2 = "20122012";           // 2
    const char *test3 = "abcdef";             // 0
    const char *test4 = "";                    // 0
    const char *test5 = "abc2012def2012ghi";  // 2
    const char *substr = "2012";

    printf("Count in '%s': %d\n", test1, kmp(test1, substr, strlen(test1), strlen(substr)));
    printf("Count in '%s': %d\n", test2, kmp(test2, substr, strlen(test2), strlen(substr)));
    printf("Count in '%s': %d\n", test3, kmp(test3, substr, strlen(test3), strlen(substr)));
    printf("Count in '%s': %d\n", test4, kmp(test4, substr, strlen(test4), strlen(substr)));
    printf("Count in '%s': %d\n", test5, kmp(test5, substr, strlen(test5), strlen(substr)));

    return 0;
}