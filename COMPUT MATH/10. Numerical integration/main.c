#include <math.h>
#include <stdio.h>
#include <stdlib.h>

double func(double x)
{
    return log(1 + x) / x;
}

const double eps = 1E-9;
const int n0 = 1000;

double medium_rectangle(double a, double b)
{
    printf("Численное интегрирование \n");
    int n = n0;
    double s = 0.0;
    double h = (b - a) / n;
    for (int i = 0; i < n; i++) {
        s += func(a + h * (i + 0.5));
    }
    s *= h;
    return s;
}

double runge_medium_rectangle(double a, double b)
{
    printf("Рунге \n");
    int step = 0;
    int n = n0, k;
    double sq[2], delta = 1;
    for (k = 0; delta > eps; n *= 2, k ^= 1) {
        double h = (b - a) / n;
        double s = 0.0;
        for (int i = 0; i < n; i++) {
            s += func(a + h * (i + 0.5));
        }
        sq[k] = s * h;
        if (n > n0) {
            delta = fabs(sq[k] - sq[k ^ 1]) / 3.0;
        }
        step++;
        printf("Шаг %2d ", step);
        printf("x = %.5lf\n",sq[k]);
    }
    return sq[k ^ 1];
}

int main(int argc, char** argv)
{
	const double a = 0.1;
  const double b = 2.1;

  printf("%lf\n\n",medium_rectangle(a, b));
  printf("%lf\n",runge_medium_rectangle(a, b));
  return 0;
}
