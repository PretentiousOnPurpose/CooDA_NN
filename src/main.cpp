#include <cmath>
#include <cmath>
#include <iostream>
#include "include/utils.hpp"
#include <chrono>
using namespace std::chrono;
using namespace std;

int main() {

    int M = 5 * 8;
    int N = 5 * 8;

    double * A1 = randn_mat(M, N);
    double * A2 = randn_mat(N, M);


    auto start = high_resolution_clock::now();
    double * Res = mat_mul_vanilla(A1, A2, M, N, M, N);
    auto stop = high_resolution_clock::now();

    print_mat(Res, M, M);

    auto duration = duration_cast<microseconds>(stop - start);
    cout << "Exec time: " << duration.count() << "us" << endl;

    return 0;
}