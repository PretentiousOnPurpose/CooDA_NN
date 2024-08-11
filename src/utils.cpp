#include <iostream>
#include <cmath>
#include <vector>
#include <smmintrin.h>
#include <immintrin.h>
#include <emmintrin.h>

using namespace std;

double ** init_mat(int M, int N) {
    double ** mat = (double **)malloc(M * sizeof(double *));

    if (mat != NULL) {
        for (int iter_n = 0; iter_n < N; iter_n++) {
            mat[iter_n] = (double *)malloc(N * sizeof(double *));
        }
    } else {
        cout << "Mem Allocation Error!" << endl;
        exit(1);
    }

    return mat;
}

double ** eye(int N) {
    double ** mat = init_mat(N, N);

    for (int iter_d = 0; iter_d < N; iter_d++) {
        mat[iter_d][iter_d] = 1;
    }

    return (double **)mat;
}

void print_mat(double ** mat, int M, int N) {
    for (int iter_r = 0; iter_r < M; iter_r++) {
        for (int iter_c = 0; iter_c < N; iter_c++) {
            cout << mat[iter_r][iter_c] << " ";
        }

        cout << endl;
    }

    return;
}

double dot_product_avx_see(double * v1, double * v2, int N) {
    long double res_t = 0;

    // for (int iter_n = 0; iter_n < N / 2; iter_n++) {

    //     __m128d v_sum = _mm_set_pd(0.0, 0.0);

    //     __m128d v1_vec = _mm_set_pd(v1[2 * iter_n + 1], v1[2 * iter_n]);
    //     __m128d v2_vec = _mm_set_pd(v2[2 * iter_n + 1], v2[2 * iter_n]);

    //     __m128d res_vec = _mm_mul_pd(v1_vec, v2_vec);
    //     res_vec = _mm_add_pd(res_vec, v_sum);

    //     double res[2];

    //     _mm_store_pd(res, res_vec);

    //     res_t = res_t + res[0] + res[1];
    // }

    for (int iter_n = 0; iter_n < N / 4; iter_n++) {
        // __m256d v1_vec = _mm256_load_pd(v1 + 4 * (iter_n + 1));
        // __m256d v2_vec = _mm256_load_pd(v2 + 4 * (iter_n + 1));

        __m256d v1_vec = _mm256_set_pd(v1[4 * iter_n + 3], v1[4 * iter_n + 2], v1[4 * iter_n + 1], v1[4 * iter_n]);
        __m256d v2_vec = _mm256_set_pd(v2[4 * iter_n + 3], v2[4 * iter_n + 2], v2[4 * iter_n + 1], v2[4 * iter_n]);

        __m256d res_vec = _mm256_mul_pd(v1_vec, v2_vec);

        double res[4];

        _mm256_storeu_pd(res, res_vec);

        res_t = res_t + res[0] + res[1] + res[2] + res[3];
    }


    return res_t;    
}

double dot_product_vanilla(double * v1, double * v2, int N) {
    double res = 0;

    for (int iter_n = 0; iter_n < N; iter_n++) {
        res += v1[iter_n] * v2[iter_n];
    }

    return res;    
}

double * get_column(double ** mat, int numRows, int col) {
    double * col_data = (double *)malloc(numRows * sizeof(double));

    for (int iter_r = 0; iter_r < numRows; iter_r++) {
        col_data[iter_r] = mat[iter_r][col];
    }

    return col_data;
}

double * get_row(double ** mat, int numCols, int row) {
    double * col_data = (double *)malloc(numCols * sizeof(double));

    for (int iter_r = 0; iter_r < numCols; iter_r++) {
        col_data[iter_r] = mat[row][iter_r];
    }

    return col_data;
}

double ** mat_mul_vanilla(double ** mat1, double ** mat2, int r1, int c1, int r2, int c2) {
    if (c1 != r2) {
        cout << "Incompatible Matrices!" << endl;
        exit(1);
    }

    double ** res = init_mat(r1, c2);

    for (int iter_r = 0; iter_r < r1; iter_r++) {
        for (int iter_c = 0; iter_c < c2; iter_c++) {
            // dot_product_avx_see(mat1[iter_r], get_column(mat2, iter_c));
            res[iter_r][iter_c] = dot_product_vanilla(get_row(mat1, c2, iter_r), get_column(mat2, r1, iter_c), c1);
            // res[iter_r][iter_c] = dot_product_avx_see(get_row(mat1, c2, iter_r), get_column(mat2, r1, iter_c), c1);
        }
    }

    return res; 
}

double ** test_matrix_1() {
    double ** mat = init_mat(4, 4);

    mat[0][0] = 1;
    mat[0][1] = 1;
    mat[1][0] = 2;
    mat[1][2] = 2;
    mat[1][3] = 5;
    mat[2][1] = 3;
    mat[2][2] = 4;
    mat[2][3] = 4;
    mat[3][0] = 5;
    mat[3][1] = 2;
    mat[3][2] = 4;
    mat[3][3] = 6;
    
    return mat;
}

double ** test_matrix_2() {
    double ** mat = init_mat(4, 4);

    mat[0][0] = -4;
    mat[0][1] = -1;
    mat[1][0] = 5;
    mat[1][2] = -4;
    mat[1][3] = 5;
    mat[2][1] = 2;
    mat[2][2] = 5;
    mat[2][3] = 1;
    mat[3][0] = 8;
    mat[3][1] = 4;
    mat[3][2] = -4;
    mat[3][3] = 7;
    
    return mat;
}

double ** randn_mat(int M, int N) {
    double ** mat = init_mat(M, N);
    
    for (int iter_m = 0; iter_m < M; iter_m++) {
        for (int iter_n = 0; iter_n < N; iter_n++) {
            mat[iter_m][iter_n] = rand() / RAND_MAX;
        }
    }

    return mat;
}
