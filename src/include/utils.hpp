#include <iostream>
#include <complex>
using namespace std;

complex<double> ** matMul(complex<double> ** x, complex<double> ** y, char * device);
complex<double> * dotProduct(complex<double> * x, complex<double> * y, char * device);
complex<double> ** strassenMatMul(complex<double> ** x, complex<double> ** y, char * device);
complex<double> * FFT(complex<double> * x, int N, char * device);
complex<double> * primeFFT(complex<double> * x, int N, char * device);
complex<double> * conv1D(complex<double> * x, complex<double> * y, char * device);
complex<double> * conv2D(complex<double> * x, complex<double> * y, char * device);
complex<double> * xcorr1D(complex<double> * x, complex<double> * y, char * device);
complex<double> * xcorr2D(complex<double> * x, complex<double> * y, char * device);
