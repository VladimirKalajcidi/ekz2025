#include <stdio.h>
#include <stdlib.h>

typedef struct list {
    int val;
    struct list *next;
} list;

list *transform(list *node) {
    list* prev = node;
    list *root = node;
    int cumsum = 0, cumsum_prev = 0;

    list *lp = prev;
    list *rp = node;

    while (node->next) {
        printf("BEGIN: cumsum = %d, node->val = %d, cumsum_prev = %d\n", cumsum, node->val, cumsum_prev);
        if (cumsum + node->val > cumsum_prev && cumsum_prev != 0) {
            printf("1\n");
            rp = node;
        } 
        if (cumsum + node->val <= 0) {
            printf("2\n");
            lp = node;
            cumsum = 0;
        } else if (node->val < 0) {
            printf("3\n");
            rp = prev;
            cumsum_prev = cumsum;
            cumsum += node->val;
        } 
        if (node->val > 0) {
            printf("4\n");
            cumsum += node->val;
        }
        prev = node;
        node = node->next;
        printf("END: cumsum = %d, node->val = %d, cumsum_prev = %d, lp->val = %d, rp->val = %d\n", cumsum, node->val, cumsum_prev, lp->val, rp->val);
    }

    printf("lp->next = %d, rp = %d, root = %d, lp = %d, rp->next = %d, node = %d\n", \
            lp->next->val, rp->val, root->val, lp->val, rp->next->val, node->val);

    list* res = lp->next;
    lp->next = rp->next;
    rp->next = root;
    node->next = NULL;

    return res;
}

list* newNode(int val) {
    list *node = (list*)malloc(sizeof(list));
    node->next = NULL;
    node->val = val;
    return node;
}

int main(void) {
    list *node = newNode(2);
    node->next = newNode(-1);
    node->next->next = newNode(1);
    node->next->next->next = newNode(2);
    node->next->next->next->next = newNode(-2);
    node->next->next->next->next->next = newNode(1);
    node->next->next->next->next->next->next = newNode(1);

    node = transform(node);
    /*while (node->next) {
        printf("%d -> ", node->val);
    }*/
}