#include <iostream>
#include <cmath>
#include <vector>
using namespace std;

double dot_product_vanilla(double * v1, double * v2);
double dot_product_avx_sse(double * v1, double * v2, int N);
double * mat_mul_vanilla(double * mat1, double * mat2, int r1, int c1, int r2, int c2);
double * eye(int N);
void print_mat(double * mat, int M, int N);
double * get_column(double * mat, int numRows, int col);
double * get_row(double * mat, int numCols, int row);
double * test_matrix_1();
double * test_matrix_2();
double * randn_mat(int M, int N);
double * init_mat(int M, int N);

