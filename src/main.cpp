#include <cmath>
#include <cmath>
#include <iostream>
#include "include/utils.hpp"
#include <chrono>
using namespace std::chrono;
using namespace std;

int main() {

    int M = 512;
    int N = M;

    // double ** A1 = test_matrix_1();
    // double ** A2 = test_matrix_2();

    double ** A1 = randn_mat(M, N);
    double ** A2 = randn_mat(M, N);


    auto start = high_resolution_clock::now();
    double ** Res = mat_mul_vanilla(A1, A2, M, N, M, N);
    auto stop = high_resolution_clock::now();

    // print_mat(A1, M, N);

    auto duration = duration_cast<microseconds>(stop - start);
    cout << "Exec time: " << duration.count() << "us" << endl;

    return 0;
}