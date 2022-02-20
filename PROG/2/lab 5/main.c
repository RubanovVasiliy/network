#include "func.h"
#include "math.h"
#include "strings.h"
#include <stdio.h>
#include <stdlib.h>

int main(void)
{
    char delim[0];
    char* path = malloc(1000);
    char* out = malloc(1000);

    scan_paths(path, delim);
    out = refresh(path, delim);

    printf("%s\n", out);
    free(out);

    return 0;
}