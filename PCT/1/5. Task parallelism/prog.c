#include <math.h>
#include <omp.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include <time.h>
#include <iostream>


void partition(int *v, int &i, int &j, int low, int high) {
    i = low;
    j = high;
    int pivot = v[(low + high) / 2];
    do {
        while (v[i] < pivot)
            i++;
        while (v[j] > pivot)
            j--;
        if (i <= j) {
            std::swap(v[i], v[j]);
            i++;
            j--;
        }
    } while (i <= j);
}

void quicksort(int *v, int low, int high) {
    int i, j;
    partition(v, i, j, low, high);
    if(low < j)
        quicksort(v, low, j);
    if(i< high)
        quicksort(v, i, high);
}

void quicksort_tasks(int *v, int low, int high, int threshold) {
    int i, j; 
    partition(v, i, j, low, high);
    if (high - low < threshold || (j - low < threshold || high - i < threshold)) {
        if (low < j) quicksort_tasks(v, low, j, threshold);
        if (i < high) quicksort_tasks(v, i, high, threshold); 
    } else {
        #pragma omp task untied 
        {
            quicksort_tasks(v, low, j, threshold);  
        }
        quicksort_tasks(v, i, high, threshold);
    }
}



int main(int argc, char *argv[]) {
    int n = (argc > 1) ? atoi(argv[1]) : 1000000;
    int threshold = (argc > 2) ? atoi(argv[2]) : 1000;
    int *arr = new int[n];
    //srand(time(NULL));

    #if 0
        for (int i = 0; i < n; i++) {
            arr[i] = rand() % 10000;
        } 
        
        double t = 0;
        t = omp_get_wtime();
        quicksort(arr, 0, n - 1);
        t = omp_get_wtime() - t;
        printf("# QuickSort (n = %d) Elapsed time: %.6lf sec.\n",n ,t);
    #else
        double t = 0;
    
        printf("# QuickSort (n = %d threshold = %d)\n", n, threshold);
        for (int threads = 2; threads <= 8; threads += 2) {
            printf("%d threads ", threads);

            for (int i = 0; i < n; i++) {
                arr[i] = rand() % 10000;
            } 

            t = omp_get_wtime();
            #pragma omp parallel num_threads(threads)
            {
                #pragma omp single 
                quicksort_tasks(arr, 0, n - 1, threshold); 
            }
            t = omp_get_wtime() - t;
            printf("Elapsed time: %.6lf sec.\n", t);
        }
    #endif
    
    return 0;
}


/*

# This file is called   force.dat
# Force-Deflection data for a beam and a bar
# Linear    10^6 1        10^6 2         10^8 1        10^8 2   
2           1.83            1.81           1.88          1.89
4           2.52            2.86           3.26          3.26
6           3.06            3.36           3.66          3.75
8           3.98            3.57           3,97          4.27
	


# Scale font and line width (dpi) by changing the size! It will always display stretched.
set terminal svg size 600,400 enhanced fname 'arial'  fsize 10 butt solid
set output 'out.svg'

# Key means label...
set key inside bottom right
set xlabel 'Threads'
set ylabel 'Speedup'
set title 'QuickSort'
plot  "data.txt" using 1:1 title 'Linear speedup' with lines, "data.txt" using 1:2 title 'n = 10^6 threshold = 1000  ' with linespoints, "data.txt" using 1:3 title 'n = 10^6 threshold = 10000' with linespoints, "data.txt" using 1:4 title 'n = 10^8 threshold = 1000  ' with linespoints, "data.txt" using 1:5 title 'n = 10^8 threshold = 10000' with linespoints

*/

