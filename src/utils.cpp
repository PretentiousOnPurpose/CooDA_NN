#include <iostream>
#include <cmath>
#include <vector>
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