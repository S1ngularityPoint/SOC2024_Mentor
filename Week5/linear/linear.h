#ifndef LINEAR // This is a header guard. This makes sure that you do not get an error if linear.h is included multiple times
#define LINEAR
#include "../matrix/matrix.h" // This imports the file which has all the definitions regarding matrices. 
#include <random> 
#include <algorithm>
#define EPS 1e-15 // Some constants. This is a threshold value
#define ETA 0.001 // This is the default learning rate
/*
    * Linear Regression
*/
class LinearRegression{
    private:
        uint64_t d; // The dimensions of the data. Each datapoint is a dx1 vector
        matrix weights; // The weights are a dx1 vector
        matrix weights_;
        double bias;
        double epsilon; 
        double eta;
        uint64_t max_iterations;
        vector<double> train_loss;
        vector<double> test_loss;

    public:
        /*
            * Input is a matrix of dimensions n x d where each row of the matrix is a data point and there are n 
            * datapoints each of dimensions d x 1.
            * The true output values is another matrix of dimensions n x 1 
            * Predictions are done as y_pred = x.T o w 
            * For the entire dataset X, Y_pred = Xw
        */
        LinearRegression(uint64_t);
        double l2loss(matrix, matrix); // Finds the loss given the weights vector, the input data set and the true output values
        pair<matrix,double> l2lossDerivative(matrix, matrix);
        void GD(matrix, matrix, double, uint64_t);
        void train(matrix, matrix, double, uint64_t);
        void test(matrix, matrix);
        matrix predict(matrix);
        double accuracy(matrix,matrix);
};

pair<pair<matrix, matrix>, pair<matrix, matrix>> test_train_split(matrix X, matrix Y, float ratio); // To split the input dataset into train and test
#endif