#include "func.h"
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

Circle* create_cir(char* input)
{
    Circle* c = calloc(sizeof(Circle), 1);
    char str[20];
    char s[10] = "circle";
    int code = sscanf(input, "%6s(%lf %lf, %lf)", str, &c->p.x, &c->p.y, &c->r);
    if (strcmp(s, str)) {
        // printf("Error: unknown shape '%s' \n", str);
        return NULL;
    } else if (code != 4 || c->r < 0) {
        // printf("Error: invalid input format\n");
        return NULL;
    } else {
        c->perimeter = perimeter_cir(c->r);
        c->square = square_cir(c->r);
    }
    // printf("%s \n%d circle(%lf %lf, %.4lf) \n", str, code, c->p.x, c->p.y,
    // c->r);
    return c;
}

int print_cir(Circle* c)
{
    if (!c)
        return -1;

    printf("\n");
    printf("circle(%lf %lf, %.4lf) \n", c->p.x, c->p.y, c->r);
    printf("perimeter = %.4lf\n", c->perimeter);
    printf("square = %.4lf\n", c->square);
    return 0;
}

int intersec_cir_cir(Circle* c1, Circle* c2)
{
    if (!c1 || !c2)
        return -1;

    double delta = sqrt(pow(c2->p.x - c1->p.x, 2) + pow(c2->p.y - c1->p.y, 2));
    if (delta <= (c2->r + c1->r)) {
        if ((delta < c2->r || delta < c1->r)) {
            if (c2->r > c1->r) {
                if (c2->r > (c1->r + delta)) {
                    return 0;
                }
            } else {
                if (c1->r > (c2->r + delta)) {
                    return 0;
                }
            }
        }
        return 1;
    } else {
        return 0;
    }

    return -1;
}

double perimeter_cir(double r)
{
    if (r < 0) {
        return -1;
    }
    return 2 * M_PI * r;
}

double square_cir(double r)
{
    if (r < 0) {
        return -1;
    }
    return r * r * M_PI;
}