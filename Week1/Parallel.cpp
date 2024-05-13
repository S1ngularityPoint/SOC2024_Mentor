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
int** Matrix::T(){
    int** MT = new int*[this->m];
    Loop(i,0,m) MT[i] = new int[this->n];
    Loop(i,0,m){
        Loop(j,0,n){
            MT[i][j] = this->M[j][i];
        }
    }
    return MT;
}

void dot(int* A, int* B, int n, int* r){
    Loop(i,0,n){
        *r += A[i]*B[i];
        // cout << i << " " << A[i]*B[i] << endl;
    } 
    // cout << "This is r " << *r << endl;
}

Matrix* Matrix::multiplyMatrix(Matrix* N) {
    // cout << "Hello there" << endl; 
    int** NT = N->T();
    Matrix* P = new Matrix(this->n,N->m);
    thread* t = new thread[P->n*P->m];
    // cout << "hmm" << endl;
    Loop(i,0,P->n*P->m){
        int a = i/(P->n), b = i%(P->n);
        // cout << i << " hmm " << endl;
        t[i] = thread(dot,this->M[a],NT[b],this->m,&P->M[a][b]);
    }
    Loop(i,0,P->n*P->m) t[i].join();
    delete [] t;
    Loop(i,0,N->m) delete [] NT[i];
    delete [] NT;
    return P;
}