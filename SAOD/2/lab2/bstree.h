#pragma once
#include <stdio.h>

typedef struct bstree {
    int key; /* Ключ */
    char* value; /* Значение */

    struct bstree* left;
    struct bstree* right;
} bstree;

bstree* bstree_create(int key, char* value);
void bstree_add(struct bstree* tree, int key, char* value);
bstree* bstree_lookup(struct bstree* tree, int key);
bstree* bstree_delete(struct bstree* tree, int key);
bstree* bstree_min(struct bstree* tree);
bstree* bstree_max(struct bstree* tree);
void traverseInOrder(struct bstree* tree);