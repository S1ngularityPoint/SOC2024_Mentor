#include "matrix/matrix.h"
#define E 1e15

typedef pair<unsigned long,unsigned long> __size;

class LinearRegression{
    private:
        unsigned long d; // The dimensions of the data. Each datapoint is a dx1 vector
        matrix weights; // The weights are a dx1 vector
        double bias; // The bias is a scalar
        double epsilon; 
    public:
        /*
            * Input is a matrix of dimensions d x n where each column of the matrix is a data point and there are n 
            * datapoints each of dimensions d x 1.
            * The true output values is another matrix of dimensions 1 x n 
        */
        LinearRegression(unsigned long);
        pair<matrix,matrix> split(matrix, float); // To split the input dataset into ttrain and test
        void l2loss(matrix,matrix); // Finds the loss given the weights vector, the input data set and the true output values
        void l2lossDerivative();
        void train();
        void test();
        matrix predict(matrix);
        void GD();
};

LinearRegression L;