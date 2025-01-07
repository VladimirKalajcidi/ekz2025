#include <stdio.h>
#include <stdint.h>

int main(void) {
    uint32_t n;
    scanf("%u", &n);

    uint32_t ans = (n >> 24) | ((n >> 8) & 0x0000FF00) \
                    | ((n >> 8) & 0x00FF0000) | (n << 24);
    printf("%u", ans);
}