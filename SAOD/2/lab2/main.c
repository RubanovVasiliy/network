#include "bstree.h"
#include "hashtab.h"
#include <inttypes.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/time.h>

#define SIZE 10000
#define LENGHT 20

int getrand(int min, int max);
double wtime();

int main(void)
{
    char** words;
    words = malloc(sizeof(char*) * SIZE);

    FILE* fp;
    char name[] = "t.txt";
    if ((fp = fopen(name, "r")) == NULL) {
        printf("Не удалось открыть файл\n");
        return 0;
    }

    for (int i = 0; i < 9000; i++) {
        words[i] = malloc(sizeof(char) * LENGHT);
        fscanf(fp, "%s", words[i]);
    }
    fclose(fp);

    int w;
    double t;
    bstree* node1;
    bstree* tree = bstree_create(1, words[0]);

    //struct listnode* node2;
    //hashtab_init(hashtab);
    //hashtab_add(hashtab, words[0], 1);

    for (int i = 1; i < 9000; i++) {
        bstree_add(tree, i, words[i]);
    }

    traverseInOrder(tree);

    for (int i = 1; i < 9000; i++) {
        if (i % 1000 == 0) {
            w = getrand(0, i);
            t = wtime();
            printf("==========================\n");
            node1 = bstree_lookup(tree, w);
            printf("==========================\n");

            t = wtime() - t;
            printf("==========================\n");

            printf("n = %d; time = %.6lf\n", i, t);
            printf("==========================\n");

            printf("Found value for key %d: %s\n", node1->key, node1->value);
            printf("==========================\n");
        }
    }

    /*

    struct bstree *tree, *node;
    tree = bstree_create(12, "Koala");
    bstree_add(tree, 4, "Flamingo");
    bstree_add(tree, 14, "Fox");
    traverseInOrder(tree);

    node = bstree_lookup(tree, 12);
    printf("Found value for key %d: %s\n", node->key, node->value);
    node = bstree_min(tree);
    printf("Minimal key: %d, value: %s\n", node->key, node->value);
    node = bstree_delete(tree, 4);
    node = bstree_min(tree);
    printf("Minimal key: %d, value: %s\n", node->key, node->value);
    traverseInOrder(tree);
    return 0;

    /*
    struct listnode* node;
    hashtab_init(hashtab);
    hashtab_add(hashtab, "Ocelot", 17);
    hashtab_add(hashtab, "Flamingo", 4);
    hashtab_add(hashtab, "Fox", 14);
    node = hashtab_lookup(hashtab, "Flamingo");
    if (node != NULL)
        printf("Node: %s, %d\n", node->key, node->value);
    */

    return 0;
}

int getrand(int min, int max)
{
    return (double)rand() / (RAND_MAX + 1.0) * (max - min) + min;
}

double wtime()
{
    struct timeval t;
    gettimeofday(&t, NULL);
    return (double)t.tv_sec + (double)t.tv_usec * 1E-6;
}