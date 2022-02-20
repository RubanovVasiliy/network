#include <math.h>
#include <stdio.h>
#include <stdlib.h>

const double eps = 10e-5;

double f(double x, double y)
{
    return pow(x, 2) - 2 * y;
}

double dif_Eiler(double a, double b, int n, double y0)
{
    double *y, *x, *func;
    double h;
    y = malloc(sizeof(double) * n);
    x = malloc(sizeof(double) * n);
    func = malloc(sizeof(double) * n);
    h = (b - a) / n; // шаг

    x[0] = a;
    y[0] = y0;
    func[0] = f(x[0], y[0]);
    for (int i = 1; i < n; i++) {
        x[i] = a + h * i;
        y[i] = y[i - 1] + h * func[i - 1];
        func[i] = f(x[i], y[i]);
    }
    
    return y[n - 1];
}

void Per_Eiler(double a, double b, int n, double y0)
{
    int step = 0;
    int n0 = n, k;
    double sq[2], delta = 1;
    printf("Эйлер\n");
    for (k = 0; delta > eps; n *= 2, k ^= 1) {

        sq[k] = dif_Eiler(a, b, n, y0);
        if (n > n0) {
            delta = fabs(sq[k] - sq[k ^ 1]);
        }

        step++;
        printf("Шаг %2d ", step);
        printf("%lf\n",sq[k]);
    }
    printf("\n");
    
}

double dif_Runge_Kutta(double a, double b, int n, double y0)
{
    double *y, *x, *k1, *k2, *k3, *k4, *delta_y;
    double h;
    h = (b - a) / n; // шаг
    y = malloc(sizeof(double) * n);
    x = malloc(sizeof(double) * n);
    k1 = malloc(sizeof(double) * n);
    k2 = malloc(sizeof(double) * n);
    k3 = malloc(sizeof(double) * n);
    k4 = malloc(sizeof(double) * n);
    delta_y = malloc(sizeof(double) * n);
    x[0] = a;
    y[0] = y0;
    for (int i = 0; i < n; i++) {
        x[i] = a + h * i;
        k1[i] = f(x[i], y[i]);
        k2[i] = f(x[i] + h / 2, y[i] + (h * k1[i]) / 2);
        k3[i] = f(x[i] + h / 2, y[i] + (h * k2[i]) / 2);
        k4[i] = f(x[i] + h, y[i] + h * k3[i]);
        delta_y[i] = (h / 6) * (k1[i] + 2 * k2[i] + 2 * k3[i] + k4[i]);
        y[i + 1] = y[i] + delta_y[i];
    }
    return y[n - 1];
}

void Per_Runge_Kutta(double a, double b, int n, double y0)
{
    int step = 0;
    int n0 = n, k;
    double sq[2], delta = 1;
    printf("Рунге-Кутта\n");
    for (k = 0; delta > eps; n *= 2, k ^= 1) {
      sq[k] = dif_Runge_Kutta(a, b, n, y0);
      if (n > n0) {
        delta = fabs(sq[k] - sq[k ^ 1]) / 3.0;
      }
      step++;
      printf("Шаг %2d ", step);
      printf("%lf\n",sq[k]);
    }
    
}

int main()
{
  double a = 0.0;
  double b = 1.0;
  int n = 10;
  int y0 = 1;

  Per_Eiler(a, b, n, y0);
  Per_Runge_Kutta(a, b, n, y0);
  return 0;
}