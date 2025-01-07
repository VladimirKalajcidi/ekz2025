#include <stdio.h>
#include <stdlib.h>

typedef struct SystemUnit {
    int id;
    int left_id;
    int right_id;
    uint32_t config;
} SystemUnit;

typedef struct SystemStructure {
    struct SystemUnit unit;
    struct SystemUnit *left, *right;
} SystemStructure;

SystemStructure *newNode(int id, int left_id, int right_id, uint32_t config, SystemUnit *arr) {
    SystemStructure *node = (SystemStructure*)malloc(sizeof(SystemStructure));
    node->unit.id = id;
    node->unit.left_id = left_id;
    node->unit.right_id = right_id;
    node->unit.config = config;

    if (left_id == 0) {
        node->left = NULL;
    } 
    if (right_id == 0) {
        node->right = NULL;
    } 
    if (left_id != 0 && right_id != 0) {
        node->left = newNode(arr[left_id].id, arr[left_id].left_id, arr[left_id].right_id,\
                            arr[left_id].config, arr);
        node->right = newNode(arr[right_id].id, arr[right_id].left_id, arr[right_id].right_id,\
                            arr[right_id].config, arr);
    }
    return node;
}

void output(SystemStructure *root) {
    int left = 0, right = 0;
    if (root->left != NULL) {
        left = root->unit.left_id;
    }
    if (root->right != NULL) {
        right = root->unit.right_id;
    }

    printf("%d %d %d %d\n", root->unit.id, left, right, root->unit.config);
    if (root->left != NULL) {
        output(root->left);
    }
    if (root->right != NULL) {
        output(root->right);
    }
}

int main(void) {
    SystemUnit arr_init[5] = {
        {1, 2, 3, 1665823},
        {2, 4, 5, 2342906},
        {4, 0, 0, 1090863},
        {3, 0, 0, 2253386},
        {5, 0, 0, 1066789},
    };

    FILE* file = fopen("input.bin", "wb");
    fwrite(&arr_init, sizeof(SystemUnit), 10, file);
    fclose(file);

    file = fopen("input.bin", "rb");
    SystemUnit arr[1000];
    for (int i = 0; i < 5; i++) {
        int ind;
        fread(&ind, sizeof(int), 1, file);
        printf("%d\n", ind);
        arr[ind].id = ind;
        fread(&arr[ind].left_id, sizeof(int), 1, file);
        fread(&arr[ind].right_id, sizeof(int), 1, file);
        fread(&arr[ind].config, sizeof(uint32_t), 1, file);
    }

    SystemStructure *root = newNode(arr[1].id, arr[1].left_id, arr[1].right_id,\
                                    arr[1].config, arr);

    output(root);
}