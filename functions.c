#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#define M 5

// Prefix function
void prefix(char *pat, int* pi, int n) {
    int q, k;
    pi[1] = 0, k = 0;

    for (int q = 2; q < n; q++) {
        while (k > 0 && pat[k + 1] != pat[q]) {
            k = pi[k];
        }
        if (pi[k + 1] == pat[q]) {
            k++;
        }
        pi[q] = k;
    }
}

// KMP function
void kmp(char* text, char* pat, int n, int m) {
    int k;
    int pi[m + 1];
    prefix(pat, pi, m);

    int q = 0;
    for (int i = 0; i <= n; i++) {
        while (q > 0 && pat[q+1] != text[i]) {
            q = pi[q];
        }
        if (pat[q+1] == text[i]) {
            q++;
        }
        if (q == m) {
            printf("образец входит со сдвигом %d\n", i-m);
            q = pi[q];
        }
    }
}

// Stack implementation
struct stack {
    int sp; // stack pointer
    int size;
    char *stack;
} stack = { .sp = -1, .size = 0, .stack = NULL};

void push(char c) {
    if (stack.size == stack.sp + 1) {
        stack.size = 2 * stack.size + 1;
        stack.stack = realloc(stack.stack, stack.size * sizeof(char));
    }
    stack.stack[++stack.sp] = c;
}

char pop() {
    if (stack.sp < 0) {
        return 1;
    }
    return stack.stack[stack.sp--];
}


// Graph implementation
typedef struct ldr {
    char key;
    int count;
    struct ldr *next;
    struct trl *trail;
} leader;

typedef struct trl {
    struct ldr *id;
    struct trl *next;
} trailer;

leader *head, *tail;
int num;

leader *find(char w) {
    leader *h = head;
    tail->key = w;
    while (h->key != w) {
        h = h->next;
    }
    if (h == tail) {
        tail = malloc(sizeof(leader));
        num++;
        h->count = 0;
        h->trail = NULL;
        h->next = tail;
    }
    return h;
}


// QuickSort
void QuickSort(int *a, int left, int right) {
    int comp, tmp, i, j;
    i = left, j = right;
    comp = a[(left + right) / 2];
    do {
        while (a[i] < comp && i < right) {
            i++;
        }
        while (comp < a[j] && j > left) {
            j--;
        }
        if (i <= j) {
            tmp = a[i];
            a[i] = a[j];
            a[j] = tmp;
            i++, j--;
        }
    } while (i <= j);

    if (left < j) {
        QuickSort(a, left, j);
    }
    if (i < right) {
        QuickSort(a, i, right);
    }
}

// AVL Tree
typedef struct Node {
    int key;
    int data;
    struct Node *left, *right;
    int height;
} Node;

int getHeight(Node *node) {
    return (node == NULL) ? 0 : node->height;
}

int max(int a, int b) {
    return (a > b) ? a : b;
}

Node* newNode(int key, int data) {
    Node* node = (Node*)malloc(sizeof(Node));
    node->key = key;
    node->data = data;
    node->left = NULL;
    node->right = NULL;
    node->height = 1;
    return node;
}

Node *rightRotate(Node *node) {
    Node *res = node->left;
    Node *tmp = res->right;

    res->right = node;
    node->left = tmp;

    node->height = max(height(node->left), height(node->right)) + 1;
    res->height = max(height(res->left), height(res->right)) + 1;

    return res;
}

Node *leftRotate(Node *node) {
    Node *res = node->right;
    Node *tmp = res->left;

    res->left = node;
    node->right = tmp;

    node->height = max(height(node->left), height(node->right)) + 1;
    res->height = max(height(res->left), height(res->right)) + 1;

    return res;
}

int getBalanceVal(Node *node) {
    return (node == NULL) ? 0 : height(node->left) - height(node->right);
}

Node* balanceNode(Node* node) {
    if (node == NULL) return NULL;

    node->height = 1 + max(height(node->left), height(node->right));

    if (getBalanceVal(node) > 1) {
        if (getBalanceVal(node->left) < 0) {
            node->left = leftRotate(node->left);
        }
        return rightRotate(node);
    }

    if (getBalanceVal(node) < -1) {
        if (getBalanceVal(node->right) > 0) {
            node->right = rightRotate(node->right);
        }
        return leftRotate(node);
    }

    return node;
}

Node* insertNode(Node* root, int key, int data) {
    if (root == NULL)
        return newNode(key, data);

    if (key < root->key) {
        root->left = insertNode(root->left, key, data);
    } else if (key > root->key) {
        root->right = insertNode(root->right, key, data);
    } else {
        root->data = data;
        return root;
    }

    return balanceNode(root);
}

Node* findMinNode(Node* node) {
    return (node->left) ? findMinNode(node->left) : node;
}

Node* removeMinNode(Node* node) {
    if (node->left == NULL)
        return node->right;

    node->left = removeMinNode(node->left);
    return balanceNode(node);
}

Node* removeNode(Node* root, int key) {
    if (root == NULL) return NULL;

    if (key < root->key)
        root->left = removeNode(root->left, key);
    else if (key > root->key)
        root->right = removeNode(root->right, key);
    else {
        Node* leftChild = root->left;
        Node* rightChild = root->right;

        if (rightChild == NULL) {
            free(root);
            return leftChild;
        }

        Node* minNode = findMinNode(rightChild);
        minNode->right = removeMinNode(rightChild);
        minNode->left = leftChild;

        free(root);
        return balanceNode(minNode);
    }

    return balanceNode(root);
}

Node* search(Node* root, int key) {
    if (root == NULL || root->key == key)
        return root;

    if (key < root->key)
        return search(root->left, key);
    
    return search(root->right, key);
}

void freeTree(Node* root) {
    if (root) {
        freeTree(root->left);
        freeTree(root->right);
        free(root);
    }
}


// Heap sort
void sift(int *a, int l, int r) {
    int i = 1, j = 2, x = a[i];
    if (j < r && a[j] < a[j + 1]) {
        j++;
    }
    while (j <= r && x < a[j]) {
        a[i] = a[j];
        a[j] = x;
        i = j;
        j = 2 * j;
        if (j < r && a[j] < a[j + 1]) {
            j++;
        }
    }
}

void HeapSort(int *a, int n) {
    int x;
    for (int i = n / 2 - 1; i >= 0; i--) {
        sift(a, i, n - 1);
    }
    for (int i = n - 1; i > 0; i--) {
        x = a[0]; 
        a[0] = a[i]; 
        a[i] = x;
        sift(a, 0, i - 1);
    }
}

// Trie
typedef enum {word, node} tag_t;

struct record {
    char *key;
    int value;
};

struct tree {
    tag_t tag;
    union {
        struct record *r;
        struct tree *nodes[M+1];
    }; /* анонимное объединение */
};

static inline int ord(char c) {
    return c ? c - 'A'+ 1 : 0; // ASCII only! Другие кодировки не гарантируют букв подряд
}
struct record *find(struct tree *t, char *key){
    int i =0;
    while (t) {
        switch (t -> tag){
            case word:
            for (key[i] != t -> r-> key[i])
                return NULL:
            return t -> r -> key[i] ? NULL : t -> r;
            case node:
                t = t -> nodes[ord(key[i])];
                if (key[i])
                i++;
        }
    }
    return NULL;
}

struct record *make_record(char *key, int value){
    struct record *r = malloc(sizeof(struct record));
    r -> key = strdup(key);
    r -> value = value;
    return r;
}
struct tree *make_from_record(struct record *r) {
    struct tree *t = malloc(sizeof(struct tree));
    t -> tag = word;
    t -> r = r;
    return t;
}
struct tree *make_word(char *key, int value) {
    return make_from_record(make_record(key, value));
}

struct tree *make_node(void) {
    struct tree *t = calloc(1, sizeof(struct tree));
    t -> tag = node;
}

struct tree *insert(struct tree *t, char *key, int value){
    if (!t)
        return make_word(key, value);
    int i = 0;
    struct tree *root = t;

    /* skip all nodes */
    while (t -> tag == node) {
        struct tree **p = &t -> nodes[ord(key[i++])];
        if (!*p) {
            *p = make_word(key, value);
            return root;
        }
        t = *p;
    }

    /* all words skipped -- key exists, update value */
    if (i && !key[i-1]){
        t -> r -> value = value;
        return root;
    }
    /* compare the remaining part */
    int j = i;
    for (; key[i]; i++)
        if (key[i] != t -> r -> key[i])
            break;
    /* key already exists -- update value */
    if (!key[i] && !t -> r ->key[i]){
        t ->r->value = value;
        return root;
    }
    /* turn t into a node */
    struct record *other = t->r;
    t->tag = node;
    memset(t->nodes, 0, sizeof(t->nodes));
    /*make new nodes for remaining common prefix */
    for (; j < i ; j++) {
        struct tree *p = make_node();
        t -> nodes[ord(key[j])] = p;
        t = p;
    }
    /* accommodate both other and new record */
    t -> nodes[ord(other->key[i])] = make_from_record(other);
    t->nodes[ord(key[i])] = make_word(key, value);
    return root;
}