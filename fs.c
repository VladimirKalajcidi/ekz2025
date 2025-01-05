#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int *get_arr(int n, int* cnt) {
    int *arr = (int*)malloc(10 * sizeof(int));
    int sum = 2, ind = 2;

    arr[0] = arr[1] = 1;

    while (sum + arr[ind - 1] + arr[ind - 2] <= n) {
        arr[ind] = arr[ind - 1] + arr[ind - 2];
        //printf("after %d, sum is %d\n", arr[ind], sum + arr[ind]);
        sum += arr[ind++];
    }

    *cnt = ind;
    return arr;
}

char *fib_str(char *s) {
    int cnt = 0, size = 0, cur = 0;
    int *arr = get_arr(strlen(s), &cnt);
    char *res = (char*)malloc(arr[0]*sizeof(char));
    
    for (int i = 0; i < cnt; i++) {
        printf("i = %d\n", i);
        if (i % 2 != 0) {
            char* tmp = (char*)malloc(arr[i] * sizeof(char));
            printf("NEW: \n");
            for (int j = 0; j < arr[i]; j++) {
                tmp[j] = s[cur + j];
                printf("%c ", tmp[j]);
            }
            printf("\n");

            cur += arr[i];
            size += arr[i];

            res = realloc(res, size * sizeof(char));
            for (int j = 0; j < size; j++) {
                printf("%c ", res[j]);
            }
            printf("\n");
            if (res == NULL) {
                printf("FAIL\n");
                free(res);
                return "1";
            }
            strcat(res, tmp);
        }
        if (i % 2 == 0) {
            cur += arr[i];
        }
        printf("size = %d, cur = %d\n", size, cur);
    }
    char* tmp = (char*)malloc((strlen(s) - cur) * sizeof(char));
    printf("NEW: \n");
    for (int j = 0; j < (strlen(s) - cur); j++) {
        tmp[j] = s[cur + j];
        printf("%c ", tmp[j]);
    }
    printf("\n");
    size += (strlen(s) - cur);

    res = realloc(res, size * sizeof(char));
    for (int j = 0; j < size; j++) {
        printf("%c ", res[j]);
    }
    printf("\n");
    if (res == NULL) {
        printf("FAIL\n");
        free(res);
        return "1";
    }
    strcat(res, tmp);
    return res;
}

int main(void) {
    int n;
    printf("Enter a number (n): ");
    scanf("%d", &n);
    
    getchar();

    char *str = (char*)malloc(16 * sizeof(char));

    printf("Enter a string: ");
    fgets(str, 100000, stdin);

    int cnt = 0;
    int *arr = get_arr(strlen(str), &cnt);

    for (int i = 0; i < cnt; i++) {
        printf("%d ", arr[i]);
    }

    char* res = fib_str(str);
    puts(res);

    free(str);
    free(arr);

    return 0;
}