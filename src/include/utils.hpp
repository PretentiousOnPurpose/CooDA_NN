#include <iostream>
#include <cmath>
#include <vector>
using namespace std;

double dot_product_vanilla(vector<double> v1, vector<double> v2);
double dot_product_avx_sse(vector<double> v1, vector<double> v2);
vector<vector<double>> mat_mul_vanilla(vector<vector<double>> mat1, vector<vector<double>> mat2);
vector<vector<double>> eye(int N);
void print_mat(vector<vector<double>> mat, int M, int N);
vector<double> get_column(vector<vector<double>> mat, int col);
vector<vector<double>> test_matrix_1();
vector<vector<double>> test_matrix_2();
