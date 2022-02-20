#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "IntVector.h"

int main(void) {
	int n = 8;
	IntVector *vector = int_vector_new(10);
	IntVector *vec = malloc(sizeof(IntVector));

	for (int i = 0; i < vector->capacity / 2; i++) {
		printf("\tPush back %d: %d\n", i, int_vector_push_back(vector, i));
	}
	printVector(vector);

	printf("\tShrink: %d\n", int_vector_shrink_to_fit(vector));
	printVector(vector);

	printf("\tСopy:\n");
	vec = int_vector_copy(vector);
	printVector(vec);

	printf("\tPop back: \n");
	int_vector_pop_back(vector);
	printVector(vector);

	printf("\tReserve to %d: %d\n", n, int_vector_reserve(vector, n));
	printVector(vector);

	printf("\tResize to %d: %d\n", 2, int_vector_resize(vector, 2));
	printVector(vector);

	printf("\tPush back %d: %d\n", n, int_vector_push_back(vector, n));
	printVector(vector);

	printf("\tSet item %d ot %d: \n", 10, 0);
	int_vector_set_item(vector, 0, 10);
	printVector(vector);

  printf("\tShrink: %d\n", int_vector_shrink_to_fit(vector));
	printVector(vector);

  printf("\tPush back %d: %d\n", 5, int_vector_push_back(vector, 5));
	printVector(vector);

  printf("\tResize to %d: %d\n", 00, int_vector_resize(vector, 0));
	printVector(vector);

  printf("\tPush back %d: %d\n", n, int_vector_push_back(vector, n));
	printVector(vector);

  printf("\tReserve to %d: %d\n", 0, int_vector_reserve(vector, 0));
	printVector(vector);
	return 0;
}