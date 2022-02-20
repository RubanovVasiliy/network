#include "bstree.h"
#include <stdio.h>
#include <stdlib.h>

bstree* bstree_create(int key, char* value)
{
    bstree* node;

    node = malloc(sizeof(*node));
    if (node != NULL) {
        node->key = key;
        node->value = value;
        node->left = NULL;
        node->right = NULL;
    }
    return node;
};

void bstree_add(bstree* tree, int key, char* value)
{
    if (tree == NULL)
        return;
    bstree *parent, *node;

    while (tree != NULL) {
        parent = tree;
        if (key < tree->key)
            tree = tree->left;
        else if (key > tree->key)
            tree = tree->right;
        else
            return;
    }

    node = bstree_create(key, value);

    if (key < parent->key)
        parent->left = node;
    else
        parent->right = node;
};

bstree* bstree_lookup(bstree* tree, int key)
{
    while (tree != NULL) {
        if (key == tree->key)
            return tree;
        else if (key < tree->key)
            tree = tree->left;
        else
            tree = tree->right;
    }
    return tree;
};

void replace_node(bstree* parent, bstree* node, bstree* child)
{
    if (parent != NULL) {
        if (node->key < parent->key) {
            parent->left = child;
        } else {
            parent->right = child;
        }
    }
}

bstree* delete_node(bstree* tree, bstree* node, bstree* parent)
{
    if (node->left == NULL) {
        replace_node(parent, node, node->right);
        if (parent == NULL) {
            tree = node->right;
        }
    } else if (node->right == NULL) {
        replace_node(parent, node, node->left);
        if (parent == NULL) {
            tree = node->left;
        }
    } else {
        bstree* min = node->right;
        bstree* minParent = min;
        while (min->left != NULL) {
            minParent = min;
            min = node->right;
        }
        replace_node(parent, node, min);
        if (parent == NULL) {
            tree = min;
        }
        if (node->right != min) {
            minParent->left = min->right;
            min->left = node->left;
            min->right = node->right;
        } else {
            min->left = node->left;
        }
    }
    free(node);
    return tree;
}

bstree* bstree_delete(bstree* tree, int key)
{
    bstree* parent = NULL;
    bstree* node = tree;
    while (node != NULL && node->key != key) {
        parent = node;
        if (key < node->key) {
            node = node->left;
        } else {
            node = node->right;
        }
    }
    if (node == NULL) {
        return tree;
    }
    return delete_node(tree, node, parent);
}

bstree* bstree_min(bstree* tree)
{
    if (tree == NULL)
        return NULL;

    while (tree->left != NULL)
        tree = tree->left;
    return tree;
};

bstree* bstree_max(bstree* tree)
{
    if (tree == NULL)
        return NULL;

    while (tree->right != NULL)
        tree = tree->right;
    return tree;
};

void traverseInOrder(struct bstree* tree)
{
    if (tree != NULL) {
        traverseInOrder(tree->left);
        printf(" %d: %s\n", tree->key, tree->value);
        traverseInOrder(tree->right);
    }
}