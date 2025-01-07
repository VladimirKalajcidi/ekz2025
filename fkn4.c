#include <stdio.h>
#include <stdlib.h>

typedef struct node {
    int val;
    int left;
    int right;
} node;

int count(node *Nodes, int ind, int *last) {
    if (Nodes[ind].left == -1 && Nodes[ind].right == -1) {
        return 0;
    } else if (*last == 1 && Nodes[ind].right == -1) {
        return 0;
    } else if (*last == -1 && Nodes[ind].left == -1) {
        return 0;
    } else if (*last == 1 && Nodes[ind].right != -1) {
        *last = -1;
        return 1 + count(Nodes, Nodes[ind].right, last);
    }  else if (*last == -1 && Nodes[ind].right != -1) {
        *last = 1;
        return 1 + count(Nodes, Nodes[ind].left, last);
    }
    return -1;
}

int main() {
    node nodes[10] = {
        {1, 1, 2},
        {2, 3, 4},
        {3, -1, 5},
        {4, 6, 7},
        {5, -1, 8},
        {6, -1, -1},
        {7, -1, -1},
        {8, -1, -1},
        {9, 9, -1},
        {10, -1, -1}
    };


    int totalNodes = 10;

    FILE *file = fopen("input.bin", "wb");
    if (!file) {
        return 1;
    }

    fwrite(&totalNodes, sizeof(int), 1, file);
    fwrite(nodes, sizeof(node), totalNodes, file);

    fclose(file);

    file = fopen("input.bin", "rb");
    if (!file) {
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