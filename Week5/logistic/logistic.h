#ifndef LOGISTIC
#define LOGISTIC
#include "../matrix/matrix.h"
#include <random>
#include <algorithm>
#define EPS 1e-15
#define ETA 0.001

class LogisticRegression{

    private:
        uint64_t d; // The dimensions of the data. Each datapoint is a dx1 vector
        matrix weights; // The weights are a dx1 vector
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
            * Predictions are done as y_pred = sigmoid(x.T o w + b) 
            * For the entire dataset X, Y_pred = sigmoid(Xw + b)
        */
        LogisticRegression(uint64_t);
        matrix sigmoid(matrix);
        double logisticLoss(matrix, matrix); // Finds the loss given the weights vector, the input data set and the true output values
        pair<matrix,double> lossDerivative(matrix, matrix);
        void GD(matrix, matrix, double, uint64_t);
        void train(matrix, matrix, double, uint64_t);
        void test(matrix, matrix);
        matrix predict(matrix);
};

pair<pair<matrix, matrix>, pair<matrix, matrix>> test_train_split(matrix X, matrix Y, float ratio); // To split the input dataset into train and test
#endif