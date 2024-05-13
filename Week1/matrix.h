#include <iostream>
#include <thread>
#include <immintrin.h>
#include <chrono>
#include <iomanip>
#include <immintrin.h> // SIMD
#include <cstring>

class Matrix {
    private:
        int** M;
        int n, m;

    public:
        Matrix(int a, int b);
        ~Matrix();
        void initialiseMatrix();
        void inputMatrix();
        void displayMatrix();
        Matrix* multiplyMatrix(Matrix* N);
};