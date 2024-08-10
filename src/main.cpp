#include <cmath>
#include <cmath>
#include <iostream>
#include "include/utils.hpp"
#include <chrono>
using namespace std::chrono;
using namespace std;

int main() {
    srand(0);

    vector<vector<double>> A1 = eye(8);
    vector<vector<double>> A2 = eye(8);

    auto start = high_resolution_clock::now();
    vector<vector<double>> Res = mat_mul_vanilla(A1, A2);
    auto stop = high_resolution_clock::now();

    print_mat(Res, 8, 8);

    auto duration = duration_cast<microseconds>(stop - start);
    cout << "Exec time: " << duration.count() << "us" << endl;

    // print_mat(A1, 4, 4);
    // print_mat(A2, 4, 4);

    return 0;
}