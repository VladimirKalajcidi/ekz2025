#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char *expand(char *s) {
    int n = strlen(s);
    printf("%c\n", s[n]);
    int i = 0;
    while (i < n) {
        if (s[i] == '%') {
            if (s[i + 1] == 'd') {
                s[i] = '1';
                s[i + 1] = '1';
                s = realloc(s, (n + 2) * sizeof(char));
                s[n + 1] = '\0';
                for (int j = n; j >= i + 2; j--) {
                    s[j] = s[j - 1];
                }
                s[i + 2] = '7';
                i += 3;
            } else if (s[i + 1] == 'c') {
                s[i] = '2';
                for (int j = i + 1; j < n - 1; j++) {
                    s[j] = s[j + 1];
                }
                s = realloc(s, (n) * sizeof(char));
                s[n - 1] = '\0';
                i++;
            }
        } else {
            i++;
        }
    }

    return s;
}

int main(void) {
    int n;
    scanf("%d", &n);
    char *s = (char*)malloc(n * sizeof(char));

    scanf("%s", s);
    char *res = (char*)malloc(n * sizeof(char));
    res = expand(s);
    puts(s);
}