#include <iostream>
#include "CLI11.hpp"

void DGEMM(const double *a, const double *b, double *c, int n) {
    int i, j, k;

    for (i = 0; i < n; i++) {
        for (j = 0; j < n; j++) {
            for (k = 0; k < n; k++) {
                *(c + i * n + j) += *(a + i * n + k) * *(b + k * n + j);
            }
        }
    }
}

void DGEMM_opt_1(const double *a, const double *b, double *c, int n) {
    int i, j, k;

    for (i = 0; i < n; i++) {
        for (k = 0; k < n; k++) {
            for (j = 0; j < n; j++) {
                *(c + i * n + j) += *(a + i * n + k) * *(b + k * n + j);
            }
        }
    }
}

void DGEMM_opt_2(double *a, double *b, double *c, int n, int BS) {
    int i, j, k;
    int i0, j0, k0;
    double *a0, *b0, *c0;

    for (i = 0; i < n; i += BS) {
        for (j = 0; j < n; j += BS) {
            for (k = 0; k < n; k += BS) {
                for (i0 = 0, c0 = (c + i * n + j),
                     a0 = (a + i * n + k); i0 < BS;
                     ++i0, c0 += n, a0 += n) {
                    for (k0 = 0, b0 = (b + k * n + j);
                         k0 < BS; ++k0, b0 += n) {
                        for (j0 = 0; j0 < BS; ++j0) {
                            c0[j0] += a0[k0] * b0[j0];
                        }
                    }
                }
            }
        }
    }
}

void init_matrix(double *a, double *b, double *c, int n) {

    int i, j;

    for (i = 0; i < n; i++) {
        for (j = 0; j < n; j++) {
                *(a + i * n + j) = 1.1;
                *(b + i * n + j) = 2.2;
                *(c + i * n + j) = 0.0;
        }
    }
}

void matrix_print(double matrix[], const int n) {
    printf("\nMatrix:\n");
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            printf("%.2lf ", *(matrix + i * n + j));
        }
        printf("\n");
    }
    printf("\n");
}

int main(int argc, char *argv[]) {
    int N = 1000;
    int block_size = 1;

    CLI::App app("DGEMM");
    app.add_option("-s,--size", N, "launch count\nin the range 10 to 1000000\ndefault 10")->
            check(CLI::Range(1, 100000));
    app.add_option("-b,--block-size", block_size, "launch count\nin the range 10 to 1000000\ndefault 10")->
            check(CLI::Range(0, 1024))->
            check(CLI::IsMember({0, 1, 2, 4, 8, 16, 32, 64, 128, 256, 512, 1024}));
    CLI11_PARSE(app, argc, argv)

    auto start = std::chrono::high_resolution_clock::now();

    auto *A = new double[N * N];
    auto *B = new double[N * N];
    auto *C = new double[N * N];
    {
        init_matrix(A, B, C, N);
    }
    auto stop = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::nanoseconds>(stop - start);

    auto str = "Init time: ;" + std::to_string(duration.count() / 1e9);

    start = std::chrono::high_resolution_clock::now();
    {
        if (block_size == 0) {
            DGEMM(A, B, C, N);
        } else if (block_size == 1) {
            DGEMM_opt_1(A, B, C, N);
        } else {
            DGEMM_opt_2(A, B, C, N, block_size);
        }
    }
    stop = std::chrono::high_resolution_clock::now();
    duration = std::chrono::duration_cast<std::chrono::nanoseconds>(stop - start);

    str += ";Time: ;" + std::to_string(duration.count() / 1e9) +
           "; N: ;" + std::to_string(N) + "; BS: ;" + std::to_string(block_size) + '\n';

    std::cout << str;
    
    //matrix_print(C, N);


    return 0;
}
