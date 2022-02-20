#include <math.h>
#include <stdio.h>
#include <stdlib.h>

double Lagrange(double* x, double* y, int count, double X)
{
    double Y = 0;
    for (int i = 0; i < count; i++) {
        double polynomial_term = 1;
        for (int j = 0; j < count; j++) {
            if (i != j) {
                polynomial_term *= (X - x[j]) / (x[i] - x[j]);
            }
        }
        Y += y[i] * polynomial_term;
    }
    return Y;
}

void table_of_difference(double** dif, double* x, double* y, int count)
{
    int n = count - 1;
    int row = 0;
    for (int i = 0; i < n; i++) {
        dif[row][i] = (y[i + 1] - y[i]) / (x[i + 1] - x[i]);
    }
    row++;
    n--;
    while (row < count - 1) {
        for (int j = 0; j < n; j++) {
            dif[row][j] = (dif[row - 1][j + 1] - dif[row - 1][j]) / (x[row + j + 1] - x[j]);
        }
        row++;
        n--;
    }
}

double Newton(double* x, double* y, int count, double X)
{
    double Y = y[0];
    double* dif[count - 1];
    for (int i = 0; i < count - 1; i++) {
        dif[i] = malloc(sizeof(double) * (count - 1));
    }

    table_of_difference(dif, x, y, count);
    for (int i = 0; i < count - 1; i++) {
        double temp = dif[i][0];
        for (int j = 0; j < i + 1; j++) {
            temp *= (X - x[j]);
        }
        Y += temp;
    }
    return Y;
}

double function(double X)
{
    return sin(X);
}

int main()
{
    double Y, X;
    double x[] = { 2, 4, 6, 8, 10, 12, 14 };
    double* y = malloc(sizeof(x));
    for (int i = 0; i < sizeof(x) / sizeof(double); i++) {
        y[i] = function(x[i]);
        printf("y[%d] = %7.4lf, при x[%d] = %7.4lf\n", i, y[i], i, x[i]);
    }
    printf("\n");
    X = 3.14;
    Y = Lagrange(x, y, sizeof(x) / sizeof(double), X);
    printf("Лагранж\ny = %.4lf, при x = %.2lf\n\n", Y, X);

    Y = Newton(x, y, sizeof(x) / sizeof(double), X);
    printf("Ньютон\ny = %.4lf, при x = %.2lf\n", Y, X);
    return 0;
}
