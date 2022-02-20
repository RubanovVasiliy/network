#include <iostream>
#include <omp.h>
#include "CLI11.hpp"
#include <pthread.h>

void matrix_vector_product_omp(double *a, double *b, double *c, int n, int threads) {

#pragma omp parallel num_threads(threads)
    {
        int nthreads = omp_get_num_threads();
        int threadid = omp_get_thread_num();
        int items_per_thread = n / nthreads;
        int lb = threadid * items_per_thread;
        int ub =
                (threadid == nthreads - 1) ? (n - 1) : (lb + items_per_thread - 1);

        int i, j, k;

        for (i = lb; i <= ub; i++) {
            for (j = 0; j < n; j++) {
                *(a + i * n + j) = 1.1;
                *(b + i * n + j) = 2.2;
                *(c + i * n + j) = 0.0;
            }
        }

        for (i = lb; i <= ub; i++) {
            for (k = 0; k < n; k++) {
                for (j = 0; j < n; j++) {
                    *(c + i * n + j) += *(a + i * n + k) * *(b + k * n + j);
                }
            }
        }
    }
}

struct thread_data {
    double *A;
    double *B;
    double *C;
    int N;
    int thread_id;
    int nthreads;
};

void *dgemm_pthread(void *threadarg) {

    struct thread_data *my_data;
    my_data = (struct thread_data *) threadarg;
    std::cout << "Thread ID : " << my_data->thread_id << std::endl;

    int items_per_thread = my_data->N / my_data->nthreads;
    int lb = my_data->thread_id * items_per_thread;
    int ub =
            (my_data->thread_id == my_data->nthreads - 1) ? (my_data->N - 1) : (lb + items_per_thread - 1);

    int i, j, k;


    for (i = lb; i <= ub; i++) {
        for (j = 0; j < my_data->nthreads; j++) {
            *(my_data->A + i * my_data->N + j) = 1.1;
            *(my_data->B + i * my_data->N + j) = 2.2;
            *(my_data->C + i * my_data->N + j) = 0.0;
        }
    }

    for (i = lb; i <= ub; i++) {
        for (k = 0; k < my_data->N; k++) {
            for (j = 0; j < my_data->N; j++) {
                *(my_data->C + i * my_data->N + j)
                        += *(my_data->A + i * my_data->N + k)
                           * *(my_data->B + k * my_data->N + j);
            }
        }
    }

    pthread_exit(nullptr);
}

int main(int argc, char *argv[]) {
    int N = 1000;
    int n_threads = 2;
    std::string mode = "OMP";

    CLI::App app("DGEMM");
    app.add_option("-s,--size", N, "")->
            check(CLI::Range(1, 100000));
    app.add_option("-m,--mode", mode, "")->
            check(CLI::IsMember({"T", "OMP"}));
    app.add_option("-t,--threads", n_threads, "")->
            check(CLI::Range(1, 8));
    CLI11_PARSE(app, argc, argv)

    auto start = std::chrono::high_resolution_clock::now();

    auto *A = new double[N * N];
    auto *B = new double[N * N];
    auto *C = new double[N * N];

    auto stop = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::nanoseconds>(stop - start);

    auto str = "Init time: \t" + std::to_string(duration.count() / 1e9);

    start = std::chrono::high_resolution_clock::now();
    {
        if (mode == "OMP") {
            matrix_vector_product_omp(A, B, C, N, n_threads);
        } else if (mode == "T") {

        }
    }
    stop = std::chrono::high_resolution_clock::now();
    duration = std::chrono::duration_cast<std::chrono::nanoseconds>(stop - start);

    str += " Time: \t" + std::to_string(duration.count() / 1e9) +
           " N: \t" + std::to_string(N) + '\n';
    std::cout << str;

    return 0;
}
