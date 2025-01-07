#include <stdio.h>
#include <stdlib.h>

typedef struct node {
    int val;
    int left;
    int right;
} node;

int count(node *Nodes, int ind, int *last) {
    printf("init val = %d\n", Nodes[ind].val);
    if (Nodes[ind].left == -1 && Nodes[ind].right == -1) {
        printf("1: val = %d\n", Nodes[ind].val);
        return 0;
    } else if (*last == 1 && Nodes[ind].right == -1) {
        printf("2: val = %d\n", Nodes[ind].val);
        return 0;
    } else if (*last == -1 && Nodes[ind].left == -1) {
        printf("3: val = %d\n", Nodes[ind].val);
        return 0;
    } else if (*last == 1 && Nodes[ind].right != -1) {
        printf("4: val = %d\n", Nodes[ind].val);
        *last = -1;
        printf("right ind = %d\n", Nodes[ind].right);
        return 1 + count(Nodes, Nodes[ind].right, last);
    }  else if (*last == -1 && Nodes[ind].right != -1) {
        printf("5: val = %d\n", Nodes[ind].val);
        *last = 1;
        return 1 + count(Nodes, Nodes[ind].left, last);
    }
    return -1;
}

int main() {
    // Создаем массив узлов дерева
    node nodes[10] = {
        {1, 1, 2},   // Узел 0
        {2, 3, 4},   // Узел 1
        {3, -1, 5},  // Узел 2
        {4, 6, 7},   // Узел 3
        {5, -1, 8},  // Узел 4
        {6, -1, -1}, // Узел 5
        {7, -1, -1}, // Узел 6
        {8, -1, -1}, // Узел 7
        {9, 9, -1},  // Узел 8
        {10, -1, -1} // Узел 9
    };


    int totalNodes = 10; // Количество узлов

    // Открываем файл для записи в бинарном режиме
    FILE *file = fopen("input.bin", "wb");
    if (!file) {
        perror("Ошибка открытия файла");
        return 1;
    }

    // Сначала записываем количество узлов
    fwrite(&totalNodes, sizeof(int), 1, file);
    
    // Затем записываем узлы
    fwrite(nodes, sizeof(node), totalNodes, file);

    // Закрываем файл
    fclose(file);

    file = fopen("input.bin", "rb");
    if (!file) {
        perror("Ошибка открытия файла");
        return 1;
    }

    node Nodes[20240];
    
    fread(&totalNodes, sizeof(int), 1, file);

    for (int i = 0; i < totalNodes; i++) {
        fread(&Nodes[i].val, sizeof(int), 1, file);
        fread(&Nodes[i].left, sizeof(int), 1, file);
        fread(&Nodes[i].right, sizeof(int), 1, file);
    }

     for (int i = 0; i < totalNodes; i++) {
        printf("%d %d %d\n", Nodes[i].val, Nodes[i].left, Nodes[i].right);
    }

    int last1 = 1;
    int last2 = -1;
    int cnt1 = count(Nodes, 0, &last1);
    printf("\n\n");
    int cnt2 = count(Nodes, 0, &last2);
    printf("%d %d", cnt1, cnt2);
}