#include <iostream>
#include <cmath>
#include <vector>
#include <smmintrin.h>
#include <immintrin.h>
#include <emmintrin.h>

using namespace std;

double * init_mat(int M, int N) {
    double * mat = (double *)aligned_alloc(16, M * N * sizeof(double));

    // if (mat != NULL) {
    //     for (int iter_n = 0; iter_n < N; iter_n++) {
    //         mat[iter_n] = (double *)aligned_alloc(N, sizeof(double *));

    //     }
    // } else {
    //     cout << "Mem Allocation Error!" << endl;
    //     exit(1);
    // }

    return mat;
}

double * eye(int N) {
    double * mat = init_mat(N, N);

    for (int iter_d = 0; iter_d < N; iter_d++) {
        mat[iter_d * N + iter_d] = 1;
    }

    return mat;
}

void print_mat(double * mat, int M, int N) {
    for (int iter_r = 0; iter_r < M; iter_r++) {
        for (int iter_c = 0; iter_c < N; iter_c++) {
            cout << (int)mat[iter_r * M + iter_c] << " ";
        }

        cout << endl;
    }

    return;
}

double dot_product_avx_see(double * v1, double * v2, int N) {
    long double res_t = 0;

    for (int iter_n = 0; iter_n < N / 8; iter_n++) {
        __m128d v1_vec = _mm_load_pd(v1);
        __m128d v2_vec = _mm_load_pd(v2);

        __m128d res_vec = _mm_mul_pd(v1_vec, v2_vec);

        double * res = (double *)aligned_alloc(16, 4 * sizeof(double));

        _mm_store_pd(res, res_vec);

        res_t = res_t + res[0] + res[1] + res[2] + res[3]; //+ res[4] + res[5] + res[6] + res[7];
    }


    // for (int iter_n = 0; iter_n < N / 4; iter_n++) {
    //     __m256d v1_vec = _mm256_set_pd(v1[4 * iter_n + 3], v1[4 * iter_n + 2], v1[4 * iter_n + 1], v1[4 * iter_n]);
    //     __m256d v2_vec = _mm256_set_pd(v2[4 * iter_n + 3], v2[4 * iter_n + 2], v2[4 * iter_n + 1], v2[4 * iter_n]);

    //     __m256d res_vec = _mm256_mul_pd(v1_vec, v2_vec);

    //     double * res = (double *)aligned_alloc(16, 4 * sizeof(double));

    //     _mm256_store_pd(res, res_vec);

    //     res_t = res_t + res[0] + res[1] + res[2] + res[3];
    // }


    return res_t;    
}

double dot_product_vanilla(double * v1, double * v2, int N) {
    double res = 0;

    for (int iter_n = 0; iter_n < N; iter_n++) {
        res += v1[iter_n] * v2[iter_n];
    }

    return res;    
}

void get_column(double * mat, int numRows, int col, double * col_data) {

    for (int iter_r = 0; iter_r < numRows; iter_r++) {
        col_data[iter_r] = mat[iter_r * numRows + col];
    }

}

void get_row(double * mat, int numCols, int row, double * row_data) {

    for (int iter_r = 0; iter_r < numCols; iter_r++) {
        row_data[iter_r] = mat[row * numCols + iter_r];
    }

}

double * mat_mul_vanilla(double * mat1, double * mat2, int r1, int c1, int r2, int c2) {
    if (c1 != r2) {
        cout << "Incompatible Matrices!" << endl;
        exit(1);
    }

    double * res = init_mat(r1, c2);
    double * col_data = (double *)aligned_alloc(16, c1 * sizeof(double));
    double * row_data = (double *)aligned_alloc(16, c1 * sizeof(double));

    for (int iter_r = 0; iter_r < r1; iter_r++) {
        for (int iter_c = 0; iter_c < c2; iter_c++) {
            get_row(mat1, c2, iter_r, row_data);
            get_column(mat2, r1, iter_c, col_data);

            // res[iter_r * c1 + iter_c] = dot_product_vanilla(row_data, col_data, c1);
            res[iter_r * c1 + iter_c] = dot_product_avx_see(row_data, col_data, c1);

        }
    }

    return res; 
}

double * test_matrix_1() {
    double * mat = init_mat(4, 4);

    mat[0 * 4 + 0] = 1;
    mat[0 * 4 + 1] = 1;
    mat[1 * 4 + 0] = 2;
    mat[1 * 4 + 2] = 2;
    mat[1 * 4 + 3] = 5;
    mat[2 * 4 + 1] = 3;
    mat[2 * 4 + 2] = 4;
    mat[2 * 4 + 3] = 4;
    mat[3 * 4 + 0] = 5;
    mat[3 * 4 + 1] = 2;
    mat[3 * 4 + 2] = 4;
    mat[3 * 4 + 3] = 6;
    
    return mat;
}

double * test_matrix_2() {
    double * mat = init_mat(4, 4);

    mat[0 * 4 + 0] = -4;
    mat[0 * 4 + 1] = -1;
    mat[1 * 4 + 0] = 5;
    mat[1 * 4 + 2] = -4;
    mat[1 * 4 + 3] = 5;
    mat[2 * 4 + 1] = 2;
    mat[2 * 4 + 2] = 5;
    mat[2 * 4 + 3] = 1;
    mat[3 * 4 + 0] = 8;
    mat[3 * 4 + 1] = 4;
    mat[3 * 4 + 2] = -4;
    mat[3 * 4 + 3] = 7;
    
    return mat;
}

double * randn_mat(int M, int N) {
    double * mat = init_mat(M, N);
    
    for (int iter_m = 0; iter_m < M; iter_m++) {
        for (int iter_n = 0; iter_n < N; iter_n++) {
            mat[iter_m * M + iter_n] = (double)rand() / RAND_MAX;
        }
    }

    return mat;
}
