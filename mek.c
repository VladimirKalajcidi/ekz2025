#include <stdio.h>
#include <stdlib.h>

typedef struct list {
    int key;
    struct list *next;
} list;

void push(struct list **head, int new_key) {
    struct list *new_node = (struct list *)malloc(sizeof(struct list));
    new_node->key = new_key;
    new_node->next = (*head);
    (*head) = new_node;
}

// Функция для отображения списка
void print_list(struct list *node) {
    while (node != NULL) {
        printf("%d -> ", node->key);
        node = node->next;
    }
    printf("NULL\n");
}

void move_elts_keys(list **src, list **dst) {
    if (*src == NULL) {
        return;
    }
    list *cur = *src;
    list *prev = (list *)malloc(sizeof(list));
    prev->key = 0;
    prev->next = cur;
    while (cur->next) {
        if (cur->key % 2 == 0) {
            list *tmp = cur->next;
            cur->next = *dst;
            *dst = cur;
            cur = tmp;
            prev->next = cur;
            printf("Printing:\n");
            print_list(*src);
            print_list(*dst);
        } else {
            prev = cur;
            cur = cur->next;
        }
    }

    return;
}

int main() {
    struct list *src = NULL;
    struct list *dst = NULL;

    push(&src, 5);
    push(&src, 4);
    push(&src, 3);
    push(&src, 2);
    push(&src, 1);

    push(&dst, 8);
    push(&dst, 6);

    printf("Исходный список (src): ");
    print_list(src);

    // Перемещаем четные элементы из src в dst
    move_elts_keys(&src, &dst);

    printf("Список после перемещения четных элементов (src): ");
    print_list(src);
    printf("Список с четными элементами (dst): ");
    print_list(dst);

    // Освобождаем память (в реальном коде это важно)
    // Не забудьте добавить функцию для освобождения памяти, чтобы избежать утечек
    return 0;
}