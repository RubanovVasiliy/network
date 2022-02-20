#include "IntVector.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

IntVector* int_vector_new(size_t initial_capacity)
{
    IntVector* v = malloc(sizeof(IntVector));
    if (v == NULL) {
        return NULL;
    }

    v->ptr = malloc(initial_capacity * sizeof(int));

    if (v->ptr == NULL) {
        free(v);
        return NULL;
    }

    v->capacity = initial_capacity;
    v->size = 0;
    return v;
}

IntVector* int_vector_copy(IntVector* v)
{
    IntVector* vCopy = int_vector_new(v->capacity);
    memcpy(vCopy->ptr, v->ptr, v->size * sizeof(int));

    if (vCopy->ptr == NULL) {
        return NULL;
    }

    vCopy->size = v->size;
    vCopy->capacity = v->capacity;
    return vCopy;
}

void int_vector_free(IntVector* v)
{
    free(v->ptr);
    free(v);
}

int int_vector_get_item(const IntVector* v, size_t index)
{
    return v->ptr[index];
}

int int_vector_set_item(IntVector* v, size_t index, int item)
{
    if (v->size >= index) {
        v->ptr[index] = item;
        return 0;
    }
    return -1;
}

size_t int_vector_get_size(const IntVector* v)
{
    return v->size;
}

size_t int_vector_get_capacity(const IntVector* v)
{ //+++
    return v->capacity;
}

void int_vector_pop_back(IntVector* v)
{
    if (v->size > 0) {
        v->ptr[v->size - 1] = 0;
        v->size--;
    }
}

int int_vector_shrink_to_fit(IntVector* v)
{
    if (v->size == v->capacity) {
        return -1;
    }

    int* ptr = realloc(v->ptr, v->size * sizeof(int));
    if (ptr == NULL) {
        printf("sdfsdfds");
        return -1;
    }

    v->ptr = ptr;
    v->capacity = v->size;

    return 0;
}

int int_vector_reserve(IntVector* v, size_t new_capacity)
{
    if (v->capacity < new_capacity) {
        if (v->capacity == 0)
            v->capacity = 1;
        int* ptr = realloc(v->ptr, new_capacity * sizeof(int));

        if (ptr == NULL) {
            return -1;
        }
        v->ptr = ptr;
        v->capacity = new_capacity;
    } else {
        return -1;
    }
    return 0;
}

int int_vector_resize(IntVector* v, size_t new_size)
{
    if (v->capacity < new_size) {
        v->size = new_size;
        return int_vector_reserve(v, v->size * 2);
    }

    while (v->size > new_size) {
        int_vector_pop_back(v);
    }
    return 0;
}

int int_vector_push_back(IntVector* v, int item)
{
    if (v->capacity == v->size) {
        if (int_vector_reserve(v, v->size * 2) == -1) {
            return -1;
        }
    }
    v->ptr[v->size] = item;
    v->size++;
    return 0;
}

void printVector(IntVector* v)
{
    printf("Vector:");
    for (int i = 0; i < v->capacity; i++) {
        printf(" %d", int_vector_get_item(v, i));
    }
    printf("\n");
    printf("Capacity: %d  \n", v->capacity);
    printf("Size: %d  \n", v->size);
    printf("\n");
}