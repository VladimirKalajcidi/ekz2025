#include <stdio.h>
#include <stdlib.h>

typedef struct list {
    int val;
    struct list *next;
} list;

list *transform(list *node) {
    struct list *prev = NULL;
    struct list *root = node;
    struct list *lp = NULL;
    struct list *rp = NULL; 

    int cumsum = 0, cumsum_prev = 0;

    while (node != NULL && node->next != NULL) {
        if (cumsum + node->val > cumsum_prev && cumsum_prev != 0) {
            rp = node;
        } 
        if (cumsum + node->val <= 0) {
            lp = node;
            cumsum = 0;
        } else if (node->val < 0) {
            rp = prev;
            cumsum_prev = cumsum;
            cumsum += node->val;
        } 
        if (node->val > 0) {
            cumsum += node->val;
        }
        prev = node;
        node = node->next;
    }
    printf("rp = %d, root = %d, rp->next = %d, node = %d\n", \
            rp->val, root->val, rp->next->val, node->val);
    if (lp == NULL || rp == NULL) {
        return root;
    }

    list* res = lp->next;
    lp->next = rp->next;
    
    rp->next = root;

    return res;
}

list* newNode(int val) {
    list *node = (list*)malloc(sizeof(list));
    node->next = NULL;
    node->val = val;
    return node;
}

int main(void) {
    list *node = newNode(1);
    node->next = newNode(-1);
    node->next->next = newNode(1);
    node->next->next->next = newNode(2);
    node->next->next->next->next = newNode(-2);
    node->next->next->next->next->next = newNode(1);
    node->next->next->next->next->next->next = newNode(1);

    node = transform(node);
    while (node->next) {
        printf("%d -> ", node->val);
        node = node->next;
    }
}