#include <stdio.h>
#include <stdlib.h>

typedef struct tree {
    int k;
    struct tree *left;
    struct tree *right;
} tree;

// Function to print the tree (in-order traversal)
void printTree(tree *node) {
    if (node == NULL) {
        return;
    }
    // Traverse the left subtree
    printTree(node->left);
    // Print the node's value
    printf("%d ", node->k);
    // Traverse the right subtree
    printTree(node->right);
}

tree *make_tree(int *arr, int n, int ind) {
    if (ind*2 + 1 >= n) {
        printf("TOOMUCH\n");
        tree *root = (tree*)malloc(sizeof(tree));
        root->k = arr[ind];
        root->left = NULL;
        root->right = NULL;
        return root;
    }
    tree *root = (tree*)malloc(sizeof(tree));
    printf("MALLOC\n");
    root->k = arr[ind];
    printf("ok1\n");
    root->left = make_tree(arr, n, ind*2 + 1);
    printf("PASSED1\n");
    if (ind*2 + 2 >= n) {
        root->right = NULL;
    } else {
        root->right = make_tree(arr, n, ind*2 + 2);
    }
    printf("PASSED2\n");
    return root;
}

tree *tree_from_arr(int *arr, int n, int *is_search_tree) {
    tree *root = make_tree(arr, n, 0);
    return root;
}

int main(void) {
    int array[] = {1, 3, 7, 2, 4, 6, 8}; // Пример массива
    int length = sizeof(array) / sizeof(array[0]);
    int isBST = 0; // Переменная для хранения статуса дерева поиска

    // Строим дерево
    tree *root = tree_from_arr(array, length, &isBST);

    printTree(root);
}