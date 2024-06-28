#include "logistic.h"

using namespace std;

// Function to generate linearly separable data for binary classification
pair<matrix, matrix> generate_binary_classification_data(uint64_t n, uint64_t d) {
    matrix X(n, d);
    matrix Y(n, 1);
    matrix w(d, 1);
    // Generate random weights for the hyperplane
    for (uint64_t j = 0; j < d; j++) {
        w(j, 0) = static_cast<double>(rand()) / RAND_MAX * 2 - 1; // Weights in range [-1, 1]
    }

    double b = static_cast<double>(rand()) / RAND_MAX * 2 - 1; // Bias term in range [-1, 1]

    for (uint64_t i = 0; i < n; i++) {
        double linear_combination = b;
        for (uint64_t j = 0; j < d; j++) {
            X(i, j) = static_cast<double>(rand()) / RAND_MAX * 2 - 1; // Features in range [-1, 1]
            linear_combination += X(i, j) * w(j, 0);
        }

        // Assign class based on the sign of the linear combination
        if (linear_combination >= 0) {
            Y(i, 0) = 1;
        } else {
            Y(i, 0) = 0;
        }
    }
    return make_pair(X, Y);
}


int main() {
    // Seed for random number generation
    srand(time(0));
    // Generate sample data
    uint64_t n = 1000; // Number of data points
    uint64_t d = 10;   // Dimensions of each data point
    auto data = generate_binary_classification_data(n, d);
    matrix X = data.first;
    matrix Y = data.second;
    // Split the data into training and testing sets
    float split_ratio = 0.8;
    auto split_data = test_train_split(X, Y, split_ratio);
    matrix X_train = split_data.first.first;
    matrix Y_train = split_data.first.second;
    matrix X_test = split_data.second.first;
    matrix Y_test = split_data.second.second;
    // Create and train the linear regression model
    LogisticRegression lg(d);
    double learning_rate = 0.0001;
    uint64_t limit = 10000;
    lg.train(X_train, Y_train, learning_rate, limit);
    // Test the model
    lg.test(X_test, Y_test);

    return 0;
}
