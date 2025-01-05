#include <stdio.h>
#include <stdlib.h>

struct avltree {
    int x;
    struct avltree *left;
    struct avltree *right;
};

// Функция для вычисления минимального количества узлов
int min_nodes(int h) {
    if (h == 0) return 0;
    if (h == 1) return 1;
    return 1 + min_nodes(h - 1) + min_nodes(h - 2);
}

// Функция для построения AVL-дерева с передачей текущего значения
struct avltree *build(int h, int *current_value) {
    if (h <= 0) return NULL;

    struct avltree *root = malloc(sizeof(struct avltree));
    if (root == NULL) {
        fprintf(stderr, "Ошибка выделения памяти для узла.\n");
        exit(EXIT_FAILURE);
    }
    root->x = (*current_value)++;

    // Рекурсивно строим левые и правые поддеревья
    root->left = build(h - 1, current_value);
    root->right = build(h - 2, current_value);

    return root;
}

// Функция для печати дерева в виде структуры
void print_tree(struct avltree *node, int space) {
    if (node == NULL) return;

    // Увеличиваем отступ
    space += 4;

    // Печать правого поддерева
    print_tree(node->right, space);

    // Печать текущего узла с отступом
    printf("\n");
    for (int i = 4; i < space; i++)
        printf(" "); // Печатаем пробелы для отступа
    printf("%d\n", node->x);

    // Печать левого поддерева
    print_tree(node->left, space);
}

// Функция для освобождения памяти
void free_tree(struct avltree *node) {
    if (node) {
        free_tree(node->left);
        free_tree(node->right);
        free(node);
    }
}

// Пример использования
int main() {
    int height = 5; // Задайте высоту дерева
    int n = min_nodes(height); // Количество узлов в дереве
    int current_value = 1; // Начальное значение для уникальных ключей

    printf("Строим дерево высоты: %d, количество узлов: %d\n", height, n);

    struct avltree *tree = build(height, &current_value);

    // Печать дерева в виде структуры
    printf("Содержимое AVL-дерева:\n");
    print_tree(tree, 0);

    // Освобождаем память
    free_tree(tree);
    return 0;
}
