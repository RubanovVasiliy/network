#include "func.h"
#include <stdio.h>
#include <stdlib.h>

int main(void)
{
    char* input1 = "circle(0 0,1)";
    Circle* c1 = create_cir(input1);
    print_cir(c1);

    char* input2 = "circle(0 5,4)";
    Circle* c2 = create_cir(input2);
    print_cir(c2);

    printf("Intersection: %d\n", intersec_cir_cir(c1, c2));

    return 0;
}