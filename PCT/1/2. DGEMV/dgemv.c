#include <omp.h>
#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <inttypes.h>
#include "hpctimer.h"



int n = 25000;
int m = 25000;
int threads = 2;

/* * matrix_vector_product: Compute matrix-vector product c[m] = a[m][n] * b[n] */

void matrix_vector_product(double *a, double *b, double *c, int m, int n) {
	for (int i = 0; i < m; i++) {
		c[i] = 0.0;
		for (int j = 0; j < n; j++)
			c[i] += a[i * n + j] * b[j];
	}
}

void run_serial() {
	double *a, *b, *c;
	a = malloc(sizeof(*a) * m * n);
	b = malloc(sizeof(*b) * n);
	c = malloc(sizeof(*c) * m);
	for (int i = 0; i < m; i++) {
		for (int j = 0; j < n; j++)
			a[i * n + j] = i + j;
	}
	for (int j = 0; j < n; j++)
		b[j] = j;
	double t = hpctimer_getwtime();
	matrix_vector_product(a, b, c, m, n);
	t = hpctimer_getwtime() - t;
	printf("Elapsed time (serial): %.6f sec.\n", t);
	free(a);
	free(b);
	free(c);
}

/* matrix_vector_product_omp: Compute matrix-vector product c[m] = a[m][n] * b[n] */

void matrix_vector_product_omp(double *a, double *b, double *c, int m, int n) {
	#pragma omp parallel num_threads(threads) 
	{
		int nthreads = omp_get_num_threads();
		int threadid = omp_get_thread_num();
		int items_per_thread = m / nthreads;
		int lb = threadid * items_per_thread;
		int ub =
			(threadid == nthreads - 1) ? (m - 1) : (lb + items_per_thread - 1);
			
		for (int i = lb; i <= ub; i++) {
			c[i] = 0.0; // Store –запись в память
			for (int j = 0; j < n; j++)
				// 4обращения к памяти: Load c[i], Load a[i][j], Load b[j],
				// Store c[i] 2 арифметические операции + и
				c[i] = c[i] + a[i * n + j] * b[j];
		}
	}
}

void run_parallel() {
	double *a, *b, *c;
	// Allocate memory for 2-d array a[m, n]
	a = malloc(sizeof(*a) * m * n);
	b = malloc(sizeof(*b) * n);
	c = malloc(sizeof(*c) * m);
	for (int i = 0; i < m; i++) {
		for (int j = 0; j < n; j++)
			a[i * n + j] = i + j;
	}
	for (int j = 0; j < n; j++)
		b[j] = j;
	double t = hpctimer_getwtime();
	matrix_vector_product_omp(a, b, c, m, n);
	t = hpctimer_getwtime() - t;
	printf("Elapsed time (parallel): %.6f sec.\n Threads: %d\n", t, threads);

		printf(" %f\n",c[0]);
		printf(" %f\n",c[5000]);
		printf(" %f\n",c[10000]);
	
	free(a);
	free(b);
	free(c);
}

int main(int argc, char **argv) {
	printf("Matrix-vector product (c[m] = a[m, n] * b[n]; m = %d, n = %d)\n", m, n);
	printf("Memory used: %" PRIu64 " MiB\n", ((m * n + m + n) * sizeof(double)) >> 20);
	run_serial();
	run_parallel();


	return 0;
}    



/*

# This file is called   force.dat
# Force-Deflection data for a beam and a bar
# Linear    15000       20000       25000
2           1.91      	1.93		1.93
4           3.61      	3.51 		3.56
6           2.95      	2.97		3.17
8          	3.68      	3.74		3.80


# Scale font and line width (dpi) by changing the size! It will always display stretched.
set terminal svg size 400,300 enhanced fname 'arial'  fsize 10 butt solid
set output 'out.svg'

# Key means label...
set key inside top left
set xlabel 'Threads'
set ylabel 'Speedup'
set title 'DGEMV OpenMP'
plot  "data.txt" using 1:1 title 'Lienar speedup' with lines, "data.txt" using 1:2 title 'n = 15000' with linespoints, "data.txt" using 1:3 title 'n = 20000' with linespoints,"data.txt" using 1:4 title 'n = 25000' with linespoints





*/