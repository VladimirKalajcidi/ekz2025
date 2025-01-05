#include <stdio.h>
#include <stdint.h>

#define MAX_BYTES 10000

int main() {
    uint8_t data[] = {0x01, 0x10, 0x01, 0x10, 0x01, 0x10, 0x01};
    FILE *file = fopen("input.bin", "wb");
    fwrite(data, sizeof(data[0]), sizeof(data) / sizeof(data[0]), file);
    fclose(file);
    file = fopen("input.bin", "rb");
    if (!file) {
        perror("Cannot open input.bin");
        return 1;
    }

    uint8_t bytes[MAX_BYTES];
    size_t bytesRead = fread(bytes, sizeof(uint8_t), MAX_BYTES, file);
    printf("%zu\n", bytesRead);
    fclose(file);

    // Обработка байтов
    for (size_t i = 0; i < bytesRead; i += 3) {
        // Поскольку мы знаем, что у нас есть группы по 4 байта
        if (i + 3 <= bytesRead) {
            // Восстанавливаем второй байт
            uint32_t value = (bytes[i] << 24) | (0x00 << 16) | (bytes[i + 1] << 8) | (bytes[i + 2]);
            printf("%x + %x + %x + %x\n", (bytes[i]), (0x00), (bytes[i + 1]), (bytes[i + 2]));
            printf("%x\n", value);
            printf("%u\n", value);
        } else {
            // Обработка неполной группы (2 байта или меньше)
            break; // Останавливаем обработку при недостаточном количестве байтов
        }
    }

    return 0;
}
