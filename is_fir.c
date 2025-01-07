#include <stdio.h>
#include <stdlib.h>

typedef struct node {
    int deg;
    struct node **next;
} node;

node *findStart(node *node, int* flag) {
    if (node->deg == 3) {
        *flag = 1;
        return node;
    }
    *flag = 0;
    for (int i = 0; i < node->deg; i++) {
        node = findStart(node->next[i], flag);
        if (*flag == 1) {
            break;
        }
    }
    return node;
}

int notMoreThanFive(node *node) {
    if (node->deg > 5) {
        return 1;
    }
    for (int i = 0; i < node->deg; i++) {
        if (notMoreThanFive(node->next[i]) == 1) {
            return 1;
        }
    }
    return 0;
}

int isFir(node* node) {
    if (notMoreThanFive(node) == 1) {
        return 0;
    }
    int flag_first = 0;
    node = findStart(node, &flag_first);
    int flag = 1;
    while (flag == 1) {
        flag = 0;
        for (int i = 0; i < node->deg; i++) {
            if (node->next[i]->deg == 4) {
                node = node->next[i];
                flag = 1;
                continue;
            }
        }
    }
    if (node->deg == 4) {
        return 1;
    }
    return 0;
}


// Функция для создания узла
struct node* createNode(int deg) {
    struct node* newNode = (struct node*)malloc(sizeof(struct node));
    newNode->deg = deg;
    newNode->next = (struct node**)malloc(deg * sizeof(struct node*));
    return newNode;
}

// Функция main
int main() {
    // Создаем узлы
    struct node* node1 = createNode(3);
    struct node* node2 = createNode(1);
    struct node* node3 = createNode(3);
    struct node* node4 = createNode(1);
    struct node* node5 = createNode(1);
    struct node* node6 = createNode(1);
    struct node* node7 = createNode(1); 

    node1->next[0] = node2;
    node1->next[1] = node3;
    node1->next[2] = node4;

    node3->next[0] = node1;
    node3->next[1] = node5;
    node3->next[2] = node6;
    //node3->next[3] = node7;

    node2->next[0] = node1;
    node4->next[0] = node1;

    node5->next[0] = node3;
    node6->next[0] = node3;
    //node7->next[0] = node3;

    if (isFir(node2)) {
        printf("Дерево является 'елочкой'.\n");
    } else {
        printf("Дерево не является 'елочкой'.\n");
    }

    free(node1->next);
    free(node2->next);
    free(node3->next);
    free(node4->next);
    free(node5);
    free(node6);
    free(node1);
    free(node2);
    free(node3);
    free(node4);

    return 0;
}