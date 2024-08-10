#include <cmath>
#include <cmath>
#include <iostream>
#include "include/utils.hpp"

using namespace std;

int main() {

    vector<vector<double>> A1 = test_matrix_1();
    vector<vector<double>> A2 = test_matrix_2();

    vector<vector<double>> Res = mat_mul_vanilla(A1, A2);

    print_mat(Res, 4, 4);

    print_mat(A1, 4, 4);
    print_mat(A2, 4, 4);

    return 0;
}