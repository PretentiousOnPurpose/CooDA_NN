#include <iostream>


complex<double> ** matMul(complex<double> ** x, complex<double> ** y, int h_x, int w_x, int w_y, char * device) {
    if (device == "cpu") {
        complex<double> result[h_x][w_y];

        for (int row = 0; row < h_x; row++) {
            for (int col = 0; col < w_y; col++) {
                for (int dim = 0; dim < w_x; dim++) {
                    result[row][col] = result[row][col] + x[row][dim] * y[dim][col];
                }
            }
        }
        
        return result;
    }
}