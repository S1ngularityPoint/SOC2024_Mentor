#include "matrix.h"
#define Loop(i,a,b) for (int i = a ; i < b ; i++)
using namespace std;

Matrix::Matrix(int a, int b) { // generate a matrix (2D array) of dimensions a,b
    this->n = a;
    this->m = b;
    this->M = new int*[a];
    Loop(i, 0, n) this->M[i] = new int[b];
    this->initialiseMatrix();
}

Matrix::~Matrix() { // cleanup heap memory
    Loop(i, 0, this->n) delete[] this->M[i];
    delete[] this->M;
}

void Matrix::initialiseMatrix(){ // initialise entries to 0
    Loop(i, 0, this->n) {
        Loop(j, 0, this->m) this->M[i][j] = 0;
    }
}

void Matrix::inputMatrix() { // take input
    Loop(i, 0, this->n) {
        Loop(j, 0, this->m) cin >> this->M[i][j];
    }
}

void Matrix::displayMatrix() { // print matrix
    Loop(i, 0, this->n) {
        Loop(j, 0, this->m) cout << this->M[i][j] << " ";
        cout << "\n";
    }
}

Matrix* Matrix::multiplyMatrix(Matrix* N) { // naive matrix multiplication
    Matrix* P = new Matrix(this->n,N->m);
    Loop(i,0,P->n){
        Loop(j,0,P->m){
            Loop(k,0,this->m)
            P->M[i][j] += this->M[i][k]*N->M[k][j];
        }
    }
    return P;
}

