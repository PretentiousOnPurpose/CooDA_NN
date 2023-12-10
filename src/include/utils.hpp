#include <iostream>


float ** matMul(float ** x, float ** y, char * device);
float ** strassenMatMul(float ** x, float ** y, char * device);
float * FFT(float * x, int N, char * device);
float * primeFFT(float * x, int N, char * device);
float * conv1D(float * x, float * y, char * device);
float * conv2D(float * x, float * y, char * device);
float * xcorr1D(float * x, float * y, char * device);
float * xcorr2D(float * x, float * y, char * device);
