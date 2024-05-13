#include <iostream>

#define Loop(i,a,b) for (int i = a ; i < b ; i++)

using namespace std;

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

Matrix::Matrix(int a, int b) {
    this->n = a;
    this->m = b;
    this->M = new int*[a];
    Loop(i, 0, n) this->M[i] = new int[b];
    this->initialiseMatrix();
}

Matrix::~Matrix() {
    Loop(i, 0, this->n) delete[] this->M[i];
    delete[] this->M;
}

void Matrix::initialiseMatrix(){
    Loop(i, 0, this->n) {
        Loop(j, 0, this->m) this->M[i][j] = 0;
    }
}

void Matrix::inputMatrix() {
    Loop(i, 0, this->n) {
        Loop(j, 0, this->m) cin >> this->M[i][j];
    }
}

void Matrix::displayMatrix() {
    Loop(i, 0, this->n) {
        Loop(j, 0, this->m) cout << this->M[i][j] << " ";
        cout << "\n";
    }
}

Matrix* Matrix::multiplyMatrix(Matrix* N) {
    Matrix* P = new Matrix(this->n,N->m);
    Loop(i,0,P->n){
        Loop(j,0,P->m){
            Loop(k,0,this->m)
            P->M[i][j] += this->M[i][k]*N->M[k][j];
        }
    }
    return P;
}

int main(int argc, char* argv[]) {
    int n, m, p;
    cin >> n >> m >> p;
    Matrix* A = new Matrix(n,m);
    Matrix* B = new Matrix(m,p);
    A->inputMatrix();
    B->inputMatrix();
    Matrix* C = A->multiplyMatrix(B);
    C->displayMatrix();
    A->~Matrix();
    B->~Matrix();
    C->~Matrix();
    return 0;
}
