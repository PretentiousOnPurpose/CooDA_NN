#include <iostream>
#include <cmath>
#include <vector>
#include <smmintrin.h>
#include <immintrin.h>
#include <emmintrin.h>

using namespace std;

vector<vector<double>> eye(int N) {
    vector<vector<double>> mat(N, vector<double>(N, 0));

    for (int iter_d = 0; iter_d < N; iter_d++) {
        mat[iter_d][iter_d] = 1;
    }

    return mat;
}

void print_mat(vector<vector<double>> mat, int M, int N) {
    for (int iter_r = 0; iter_r < M; iter_r++) {
        for (int iter_c = 0; iter_c < N; iter_c++) {
            cout << mat[iter_r][iter_c] << " ";
        }

        cout << endl;
    }

    return;
}

double dot_product_avx_see(vector<double> v1, vector<double> v2) {
    int N = v1.size();
    // vector<double> res_t(N, 0);
    long double res_t = 0;

    for (int iter_n = 0; iter_n < N / 2; iter_n++) {

        __m128d v1_vec = _mm_set_pd(v1[2 * iter_n + 1], v1[2 * iter_n]);
        __m128d v2_vec = _mm_set_pd(v2[2 * iter_n + 1], v2[2 * iter_n]);

        __m128d res_vec = _mm_dp_pd(v1_vec, v2_vec, 0x3F);

        double res[2];

        _mm_store_pd(res, res_vec);

        res_t = res_t + res[0]; // + res[1];
    }

    return res_t;    
}

double dot_product_vanilla(vector<double> v1, vector<double> v2) {
    int N = v1.size();

    double res = 0;

    for (int iter_n = 0; iter_n < N; iter_n++) {
        res += v1[iter_n] * v2[iter_n];
    }

    return res;    
}

vector<double> get_column(vector<vector<double>> mat, int col) {
    int numRows = mat.size();

    vector<double> col_data(numRows, 0);

    for (int iter_r = 0; iter_r < numRows; iter_r++) {
        col_data[iter_r] = mat[iter_r][col];
    }

    return col_data;
}

vector<vector<double>> mat_mul_vanilla(vector<vector<double>> mat1, vector<vector<double>> mat2) {
    int numRows = mat1.size();
    int numCols = mat2[0].size();

    if (mat1[0].size() != mat2.size()) {
        cout << "Mat1 and Mat2 have incompatible dimensions" << endl;
        exit(0);
    }

    vector<vector<double>> res(numRows, vector<double>(numCols, 0));

    for (int iter_r = 0; iter_r < numRows; iter_r++) {
        for (int iter_c = 0; iter_c < numCols; iter_c++) {
            // dot_product_avx_see(mat1[iter_r], get_column(mat2, iter_c));
            res[iter_r][iter_c] = dot_product_vanilla(mat1[iter_r], get_column(mat2, iter_c));
        }
    }

    return res; 
}

vector<vector<double>> test_matrix_1() {
    vector<vector<double>> mat(4, vector<double>(4, 0));

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

vector<vector<double>> test_matrix_2() {
    vector<vector<double>> mat(4, vector<double>(4, 0));

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

vector<vector<double>> randn_mat(int M, int N) {
    vector<vector<double>> mat(M, vector<double>(N, 0));    
    
    for (int iter_m = 0; iter_m < M; iter_m++) {
        for (int iter_n = 0; iter_n < N; iter_n++) {
            mat[iter_m][iter_n] = rand() / RAND_MAX;
        }
    }

    return mat;
}
