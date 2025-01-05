#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int is_substr(char *s, const char *w) {
    int n = strlen(s), m = strlen(w), start = 0;
    int i = 0, ind = 0;
    while (i < n) {
        start = i + 1;
        while (s[i] == w[ind]) {
            i++;
            ind++;
        }
        if (ind >= m) {
            return 1;
        } else {
            i = start;
            ind = 0;
        }
    }
    return 0;
}

void erase(char *s, const char *w) {
    int ind = 0, i = 0;
    int n = strlen(s);
    int start = 0;
    while (i < n) {
        if (start == 0 || s[i++] == ' ') {
            char *tmp = (char*)malloc(n * sizeof(char));
            start = i;
            while (s[i] != ' ') {
                tmp[i - start] = s[i];
                i++;
            }
            tmp[i - start] = '\0';
            if (is_substr(tmp, w)) {
                int len = strlen(tmp);
                for (int j = start; j < n; j++) {
                    s[j] = s[j + len + 1];
                }
                s[n - len] = '\0';
            }
            free(tmp);
        }
    }
}

int main() {
    char s[100] = "this is a test string for testing the function";
    char tmp[11] = "tesingtesti";
    const char *w = "test";

    printf("Исходная строка: \"%s\"\n", s);
    
    erase(s, w);

    printf("Измененная строка: \"%s\"\n", s);

    return 0;
}