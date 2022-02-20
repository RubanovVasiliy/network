#include <stdlib.h>
#include <stdio.h>
#include <math.h>

double f(double x) {
	return cos(2 / x) - 2 * sin(1 / x) + 1 / x;
}

double d_f_1(double x) {
	return (2 * sin(2 / x)) / (pow(x,2)) + (2 * cos(1 / x)) / (pow(x, 2)) - 1 / (pow(x, 2));
}

double d_f_2(double x) {
	return (-4 * sin(2 / x)) / (pow(x, 3)) - (4 * cos(1 / x)) / (pow(x, 3)) + 2 / (pow(x, 3)) + (2 * sin(1 / x)) / (pow(x, 4)) - (4 * cos(2 / x)) / (pow(x, 4));
}

void newton(double a, double b, double e) { 
	int step = 0;
	int flag = 0;
	double x0;

  printf("Метод Ньютона\n");
	if (f(a) * d_f_2(a) > 0) {
		printf("Сходится для a\n");
		x0 = a;
	} else if (f(b) * d_f_2(b) > 0) {
		printf("Сходится для b\n");
		x0 = b;
		flag = 1;
	} else {
		printf("Не сходится\n");
		return;
	}

	if (!flag) 
		while (fabs(f(x0)) > e) {
			step++;
			x0 = (x0 - (f(x0) / d_f_1(x0)));

			printf("Шаг %2d ", step);
      printf("x = %.5lf\n",x0);
		}
  else 
		while (fabs(f(x0)) > e) {
			step++;
			x0 = (x0 - (f(x0) / d_f_1(x0)));

			printf("Шаг %2d ", step);
      printf("x = %.5lf\n",x0);
		}
}

void hord(double a, double b, double e) {
	double x0;
	double x;
	int flag = 0;
  int step = 0;
  
  printf("Метод хорд\n");
	if (f(a) * d_f_2(a) > 0) {
		printf("Сходится для a\n");
		x0 = a;
		x = x0 - (((b - x0) / (f(b) - f(x0)) * f(x0)));
	} else if (f(b) * d_f_2(b) < 0) {
		printf("Сходится для b\n");
		x0 = b;
		x = x0 - (((a - x0) / (f(a) - f(x0)) * f(x0)));
		flag = 1;
	} else {
		printf("Не сходится\n");
		return;
	}

	if (!flag)
		while (fabs(f(x) > e)) {
			step++;
			x = x0 - (((b - x0) / (f(b) - f(x0)) * f(x0)));
			x0 = x;
			printf("Шаг %2d ", step);
      printf("x = %.5lf\n",x0);
		}
	else 
		while (fabs(f(x) > e)) {
			step++;
			x = x0 - (((a - x0) / (f(a) - f(x0)) * f(x0)));
			x0 = x;
			printf("Шаг %2d ", step);
      printf("x = %.5lf\n",x0);
		}
}

void bisection(double a, double b, double e) {
	int step = 0;

  printf("Метод бисекций\n");
	if (f(a) * f(b) < 0) {
		double x = (a + b) / 2;
		double a0 = a;
		double b0 = b;
		while (fabs(f(x)) > e) {
			step++;
			x = (a0 + b0) / 2;
			if (f(a0) * f(x) < 0)
				b0 = x;
			else
				a0 = x;
			printf("Шаг %2d ", step);
			printf("a = %.5lf ",a0);
      printf("b = %.5lf ",b0);
      printf("x = %.5lf ",x);
      printf("\n");
		}
	}
	else
		printf("Не сходится\n");
}

int main() {
	double eps = 10e-4;
	double a = 1.1;
	double b = 2;

	bisection(a, b, eps);
  printf("\n");
	
	newton(a, b, eps);
	printf("\n");

	hord(a, b, eps);
}
