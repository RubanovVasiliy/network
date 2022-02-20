#include <inttypes.h>
#include <math.h>
#include <omp.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include <time.h>


double func1(double x)
{
    return log(1 + x) / x;
}

const double eps = 1E-5;
const int n0 = 10000000;

double medium_rectangle_serial(double a, double b)
{
    int n = n0, k;
    double sq[2], delta = 1;
    for (k = 0; delta > eps; n *= 2, k ^= 1) {
        double h = (b - a) / n;
        double s = 0.0;
        for (int i = 0; i < n; i++) {
            s += func1(a + h * (i + 0.5));
        }
        sq[k] = s * h;
        if (n > n0) {
            delta = fabs(sq[k] - sq[k ^ 1]) / 3.0;
        }
    }
    return sq[k ^ 1];
}

double medium_rectangle_parallel(double a, double b, int threads)
{
    double sq[2];
    double s;

	#pragma omp parallel num_threads(threads)
    {
        int n = n0, k;
        double delta = 1;
        for (k = 0; delta > eps; n *= 2, k ^= 1) {
            double h = (b - a) / n;
            s = 0.0;
            sq[k] = 0.0;

			#pragma omp barrier
			#pragma omp for reduction(+:s)
            for (int i = 0; i < n; i++) {
                s += func1(a + h * (i + 0.5));
            }

            
            sq[k] = s * h;

			#pragma omp barrier
            if (n > n0) {
                delta = fabs(sq[k] - sq[k ^ 1]) / 3.0;
            }
        }
        sq[0] = sq[k ^ 1];
    }
    return sq[0];
}



double getrand_r(unsigned int* seed) { 
	return (double)rand_r(seed) / RAND_MAX; 
}

double func2(double x, double y)
{
    return pow(exp(x + y),2); 
}

double Monte_Carlo(int n)
{
    double in = 0;
    double s = 0;
    unsigned int seed = 0;
    for (int i = 0; i < n; i++) {
        double x = getrand_r(&seed); 
        double y = getrand_r(&seed); 
        if (x > 0 && x < 1 && y < 1 - x) {
            in++;
            s += func2(x, y);
        }
    }
    double v = in / n;
    double res = v * s / in;
    return res;
}

double Monte_Carlo_parallel(int n, int threads)
{
    double in = 0;
    double s = 0;

	#pragma omp parallel num_threads(threads)
    {
        unsigned int seed = omp_get_thread_num();
		#pragma omp for reduction(+ : in, s)
        for (int i = 0; i < n; i++) {
            double x = getrand_r(&seed);
            double y = getrand_r(&seed);
            if (x > 0 && x < 1 && y < 1 - x) {
                in++;
                s += func2(x, y);
            }
        }
    }
    double v = in / n;
    double res = v * s / in;
    return res;
}

int main(int argc, char** argv)
{
	const int n7 = 10000000;
	const int n8 = 100000000;
	const double a = 0.1;
    const double b = 1.0;
    double t;
    double res;

    t = omp_get_wtime();
    res = medium_rectangle_serial(a, b);
    t = omp_get_wtime() - t;
    printf("\nElapsed time medium rectangle serial: %.6lf sec.\n", t);


    for (int i = 2; i <= 8; i+=2) {
        printf("%d threads ", i);
        t = omp_get_wtime();
        res = medium_rectangle_parallel(a, b, i);
        t = omp_get_wtime() - t;
        printf("Elapsed time parallel: %.6lf sec.\n", t);
    }
	printf("\n");
	

    t = omp_get_wtime();
    res = Monte_Carlo(n7);
    t = omp_get_wtime() - t;
    printf("Elapsed time Monte Carlo 10^7: %.6lf sec.\n", t);

    for (int i = 2; i <= 8; i+=2) {
        printf("%d threads ", i);
        t = omp_get_wtime();
        res = Monte_Carlo_parallel(n7, i);
        t = omp_get_wtime() - t;
        printf("Elapsed time parallel 10^7: %.6lf sec.\n", t);
    }
    printf("\n");


    t = omp_get_wtime();
    res = Monte_Carlo(n8);
    t = omp_get_wtime() - t;
    printf("Elapsed time Monte Carlo 10^8: %.6lf sec.\n", t);

    for (int i = 2; i <= 8; i+=2) {
        printf("%d threads ", i);
        t = omp_get_wtime();
        res = Monte_Carlo_parallel(n8, i);
        t = omp_get_wtime() - t;
        printf("Elapsed time parallel 10^8: %.6lf sec.\n", t);
    }
    return 0;
}


/*

# This file is called   force.dat
# Force-Deflection data for a beam and a bar
# Linear    10^7        10^8       
2           1.95      	1.96		
4           3.27      	3.73 		
6           4.63      	4.75		
8          	5.77      	6.00		


# Scale font and line width (dpi) by changing the size! It will always display stretched.
set terminal svg size 400,300 enhanced fname 'arial'  fsize 10 butt solid
set output 'out.svg'

# Key means label...
set key inside top left
set xlabel 'Threads'
set ylabel 'Speedup'
set title 'Monte Carlo OpenMP'
plot  "data.txt" using 1:1 title 'Lienar speedup' with lines, "data.txt" using 1:2 title 'n = 10^7' with linespoints, "data.txt" using 1:3 title 'n = 10^8' with linespoints

*/

/*

# This file is called   force.dat
# Force-Deflection data for a beam and a bar
# Linear    10^7          
2           2.00      			
4           3.85      			
6           4.14      			
8          	5.26      			


# Scale font and line width (dpi) by changing the size! It will always display stretched.
set terminal svg size 400,300 enhanced fname 'arial'  fsize 10 butt solid
set output 'out.svg'

# Key means label...
set key inside top left
set xlabel 'Threads'
set ylabel 'Speedup'
set title 'Runge OpenMP'
plot  "data.txt" using 1:1 title 'Lienar speedup' with lines, "data.txt" using 1:2 title 'eps = 1E-5' with linespoints

*/