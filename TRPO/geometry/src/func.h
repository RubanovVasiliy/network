#include <stdio.h>

typedef struct Point {
    double x;
    double y;
} Point;

typedef struct Circle {
    Point p;
    double r;
    double square;
    double perimeter;
} Circle;

Circle* create_cir(char* input);
int print_cir(Circle* c);
int intersec_cir_cir(Circle* c1, Circle* c2);
double perimeter_cir(double r);
double square_cir(double r);