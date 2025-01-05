#include <stdio.h>
#include <stdlib.h>

typedef struct list {
    int k;
    struct list *next;
} list;

void push(struct list **head, int new_key) {
    struct list *new_node = (struct list *)malloc(sizeof(struct list));
    new_node->k = new_key;
    new_node->next = (*head);
    (*head) = new_node;
}

// Функция для отображения списка
void print_list(struct list *node) {
    while (node != NULL) {
        printf("%d -> ", node->k);
        node = node->next;
    }
    printf("NULL\n");
}

void rem_odd(list **head) {
    if (*head == NULL)
        return;

    list *prev = (list*)malloc(sizeof(list));
    prev->k = 0;
    prev->next = (*head)->next;
    *head = prev;
    list *cur = (*head);
    print_list((*head)->next);

    while (cur->next && cur->next->next) {
        print_list((*head)->next);
        prev = cur->next;
        cur = cur->next->next;
        prev->next = (cur->next) ? cur->next : NULL;
    }

    (*head) = (*head)->next;
}

int main() {
    list *src = NULL;

    push(&src, 6);
    push(&src, 5);
    push(&src, 4);
    push(&src, 3);
    push(&src, 2);
    push(&src, 1);

    printf("Исходный список (src): ");
    print_list(src);

    rem_odd(&src);

    printf("Список после преобразований (src): ");
    print_list(src);

    // Освобождаем память (в реальном коде это важно)
    // Не забудьте добавить функцию для освобождения памяти, чтобы избежать утечек
    return 0;
}