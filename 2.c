#include <stdio.h>
#include <stdlib.h>

int main(void) {
    int i = 0, size = 2;

    int *arr = (int*)malloc(size*sizeof(int));
    scanf("%d", &arr[i++]);

    while (scanf("%d", &arr[i]) == 1 && arr[i++] != 0) {
        if (i > size) {
            size = 2 * size;
            arr = realloc(arr, size*sizeof(int));

            if (arr == NULL) {
                printf("FAIL\n");
                free(arr);
                return 1;
            }
        }
    }

    int n, start = 0;
    scanf("%d", &n);
    int good = 0, cnt = 0;

    for (int i = 1; i < size; i++) {
        if (arr[i - 1] == 0 && i != 1) {
            break;
        }
        printf("i = %d, arr[i] = %d, start = %d, good = %d, cnt = %d\n", i, arr[i], start, good, cnt);
        if (i - start == n) {
            if (good == start) {
                printf("-1\n");
                return 0;
            }
            cnt++;

            if (arr[i + 1] > arr[i]) {
                start = i;
                good = start;
            } else {
                start = i = good;
            }
        } else {
            if (arr[i + 1] > arr[i]) {
                good = i;
            }
        }
    }

    if (i - start <= n) {
        printf("%d", ++cnt);
        return 0;
    }
    printf("%d", cnt);
    return 0;
}