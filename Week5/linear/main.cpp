#include "linear.h"

using namespace std;

// Function to generate a linearly fittable dataset
pair<matrix, matrix> generate_linear_data(uint64_t n, uint64_t d) {
    matrix X(n, d);
    matrix Y(n, 1);
    matrix w(d, 1);

    // Generate random weights
    for (uint64_t j = 0; j < d; j++) {
        w(j, 0) = static_cast<double>(rand()) / RAND_MAX;
    }

    double b = static_cast<double>(rand()) / RAND_MAX; // Bias term

    for (uint64_t i = 0; i < n; i++) {
        double y = b;
        for (uint64_t j = 0; j < d; j++) {
            X(i, j) = static_cast<double>(rand()) / RAND_MAX;
            y += X(i, j) * w(j, 0);
        }
        y += static_cast<double>(rand()) / RAND_MAX * 0.1; // Adding some noise
        Y(i, 0) = y;
    }

    return make_pair(X, Y);
}

int main() {
    // Seed for random number generation
    srand(time(0));

    // Generate sample data
    uint64_t n = 1000; // Number of data points
    uint64_t d = 10;   // Dimensions of each data point
    auto data = generate_linear_data(n, d);
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
    LinearRegression lr(d);
    double learning_rate = 0.0001;
    uint64_t limit = 10000;
    lr.train(X_train, Y_train, learning_rate, limit);

    // Test the model
    lr.test(X_test, Y_test);

    return 0;
}
