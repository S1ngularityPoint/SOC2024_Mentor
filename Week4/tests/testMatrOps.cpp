#include "../matrix/matrix.h"
extern matrix transpose(const matrix& a);
extern double determinant(const matrix& a);
/*

This file checks implementation and timing of the following functions : 
1]matmul
2]matrix inverse
3]matrix transpose
4]matrix determinant
It assumes basic operators and max,min,argmax,argmin as well as element wise functions are implemented correctly

*/
bool isIdentity(const matrix& m, double epsilon = 1e-9) {
    if (m.rows != m.cols) return false;
    for (unsigned long i = 0; i < m.rows; ++i) {
        for (unsigned long j = 0; j < m.cols; ++j) {
            if (i == j) {
                if (fabs(m(i, j) - 1.0) > epsilon) return false;
            } else {
                if (fabs(m(i, j)) > epsilon) return false;
            }
        }
    }
    return true;
}
void test_matrix_inverse() {
    // Define a test matrix
    matrix A(3, 3);
    A(0, 0) = 1; A(0, 1) = 2; A(0, 2) = 3;
    A(1, 0) = 0; A(1, 1) = 1; A(1, 2) = 4;
    A(2, 0) = 5; A(2, 1) = 6; A(2, 2) = 0;

    std::cout << "Matrix A:\n";
    A.printMatrix();

    try {
        matrix A_inv = inverse(A);
        std::cout << "\nInverse of A:\n";
        A_inv.printMatrix();

        // Verify the result by multiplying A by its inverse
        matrix I = matmul(A, A_inv);
        std::cout << "\nA * A_inv:\n";
        I.printMatrix();

        if (isIdentity(I)) {
            std::cout << "\nThe inverse function works correctly.\n";
        } else {
            std::cout << "\nThe inverse function did not produce the correct result.\n";
        }
    } catch (const std::runtime_error& e) {
        std::cerr << e.what() << '\n';
    }
}
void test_matrix_determinant() {
    // Define a test matrix
    matrix A(3, 3);
    A(0, 0) = 1; A(0, 1) = 2; A(0, 2) = 3;
    A(1, 0) = 3; A(1, 1) = 1; A(1, 2) = 4;
    A(2, 0) = 5; A(2, 1) = 6; A(2, 2) = 0;

    std::cout << "Matrix A:\n";
    A.printMatrix();

    try {
        double det_A = determinant(A);
        std::cout << "\nDeterminant of A: " << det_A << "\n";

        // Check the determinant value here, if needed
    } catch (const std::invalid_argument& e) {
        std::cerr << "Exception: " << e.what() << "\n";
    }
    cout << "\n";
}

void test_matrix_transpose() {
    // Define a test matrix
    matrix A(3, 2);
    A(0, 0) = 1; A(0, 1) = 2;
    A(1, 0) = 3; A(1, 1) = 4;
    A(2, 0) = 5; A(2, 1) = 6;

    std::cout << "Matrix A:\n";
    A.printMatrix();

    matrix A_trans = transpose(A);
    std::cout << "\nTranspose of A:\n";
    A_trans.printMatrix();
    cout << "\n";
}

int main () {
    test_matrix_inverse();
    test_matrix_transpose();
    test_matrix_determinant();
    matrix a(identity(2));
    std::cout<<"Printing a:\n";
    /*
    
    EXPECTED OUTPUT:
    1 0 
    0 1

    */
    a.printMatrix();
    
    matrix b = exp(a);
    std::cout<<"Printing b:\n";
    /*
    
    EXPECTED OUTPUT:
    e 1 
    1 e

    */
    b.printMatrix();


    matrix c = b+1;
    c = matmul(c,b);
    std::cout<<"Printing c:\n";
    /*
    
    EXPECTED OUTPUT:
    12.11 9.15 
    9.15 12.11

    */
    c.printMatrix();

}