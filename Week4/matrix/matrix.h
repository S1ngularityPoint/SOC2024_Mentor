#include <iostream>
#include <vector>
#include <cmath>
using namespace std;

class matrix{
    public:
        unsigned long rows; // number of rows of the matrix

        unsigned long cols; // number of columns of the matrix 

        vector<double> data; // the data that the matrix has i.e. matrix itself

        matrix(unsigned long rowNum, unsigned long colNum); // constructor

        matrix(unsigned long size); // 1D matrix constructor

        void printMatrix() // utility function to print matrix 
        { 
            for (int i=0; i<rows; i++) {
                for (int j=0; j<cols; j++) {
                    std::cout<<data[i*cols+j]<<" ";
                }
                std::cout<<"\n";
            }
        }

        double& operator()(unsigned long row_i, unsigned long col_i)  // access function 
        {
            if(row_i>=rows ||col_i>=cols) throw std::out_of_range("Index out of bounds");
            else return data[row_i*cols+col_i];
        }

        const double& operator()(unsigned long row_i, unsigned long col_i)  // constant access function 
        const{
            if(row_i>=rows ||col_i>=cols) throw std::out_of_range("Index out of bounds");
            else return data[row_i*cols+col_i];
        }

        double& operator()(unsigned long i) // 1D matrix access function
        {
            if (cols != 1) throw std::invalid_argument("Use 2D indexer for 2D arrays");
            return (*this)(i, 0);
        }

        const double& operator()(unsigned long i) // 1D matrix constant access function
        const{
            if (cols != 1) throw std::invalid_argument("Use 2D indexer for 2D arrays");
            return (*this)(i, 0);
        }

        pair<unsigned long,unsigned long> shape() // function to get shape of matrix 
        const{
            return make_pair(rows,cols);
        }

        matrix(const matrix& other); // copy constructor

        matrix& operator=(const matrix& other); // equality operator

        friend matrix operator+(const matrix& first, const matrix& second); // elementwise addition operator

        friend matrix operator-(const matrix& first, const matrix& second); // elementwise subtraction operator

        friend matrix operator*(const matrix& first, const matrix& second); // elementwise multiplication operator

        friend matrix operator*(const matrix&first, const double t);

        friend matrix operator/(const matrix& first, const matrix& second); // elementwise division operator
};

matrix matmul(const matrix& first, const matrix& second); // matmul function, A = first*second

matrix zeros(unsigned long rows, unsigned long cols); // zeros function : A = np.zeros((rows,cols))

matrix zeros(unsigned long size); // 1D zeros function : A = np.zeros((size,1))

matrix eye(unsigned long size); // 1D eye function : A = I(size) where I(x) is identity matrix with dimensions x

matrix eye(unsigned long rows, unsigned long cols); // eye function : A = I(min(rows,cols)):zeros

matrix ones(unsigned long rows, unsigned long cols); // ones function : A = np.ones((rows,cols))

matrix identity(unsigned long size); // identity matrix function : A = I(size)

matrix max(matrix &arr,int axis); // specific max function : A = np.max(arr,axis)

matrix argmax(matrix &arr,int axis); // specific argmax function : A = np.argmax(arr,axis)

matrix max(matrix &arr); // general max function : A = np.max(arr,0)

matrix argmax(matrix &arr); // general argmax function : A = np.argmax(arr,0)

matrix min(matrix &arr,int axis); // specific min function : A = np.min(arr,axis)

matrix argmin(matrix &arr,int axis); // specific argmin function : A = np.argmin(arr,axis)

matrix min(matrix &arr); // general min function : A = np.min(arr,0)

matrix argmin(matrix &arr); // general argmin function : A = np.argmin(arr,0)

matrix tanh(matrix &a); // elementwise tanh function : matr[i][j] = tanh(matr[i][j])

matrix fabs(matrix &a); // elementwise fabs function : matr[i][j] = fabs(matr[i][j])

matrix exp(matrix &a); // elementwise exponentiator : matr[i][j] = fabs(matr[i][j])

matrix log(matrix &a,double logbase); // elementwise log operator : matr[i][j] = log_{logbase}(matr[i][j])