#include "regression.h"

using namespace std;

// Function to generate polynomial fittable dataset
pair<matrix, matrix> generate_polynomial_data(uint64_t n, uint64_t polynomial_degree) {
    matrix X(n,1);
    matrix Y(n,1);
    
    srand(time(0)); // Seed for random number generation
    
    // Generate random coefficients for polynomial terms
    vector<double> w(polynomial_degree + 1);
    for (uint64_t j = 0; j <= polynomial_degree; j++) {
        w[j] = static_cast<double>(rand()) / RAND_MAX;
    }

    // Generate data points
    for (uint64_t i = 0; i < n; i++) {
        double x = static_cast<double>(rand()) / RAND_MAX; // Random x in [0, 1)
        
        // Calculate Y value using polynomial equation
        double y = 0.0;
        for (uint64_t j = 0; j <= polynomial_degree; j++) {
            y += w[j] * pow(x, j);
        }
        
        // Add some noise
        y += 0.1 * static_cast<double>(rand()) / RAND_MAX;

        X(i,0) = x;
        Y(i,0) = y;
    }
    
    return make_pair(X, Y);
}

int main() {
    // Seed for random number generation
    srand(time(0));

    // Generate sample polynomial data
    uint64_t n = 10000;               // Number of data points
    uint64_t polynomial_degree = 10;  // Degree of polynomial (e.g., cubic polynomial)
    auto data = generate_polynomial_data(n,polynomial_degree);
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
    Regression r(polynomial_degree);
    double learning_rate = 0.0001;
    uint64_t limit = 10000;
    r.train(X_train, Y_train, learning_rate, limit);

    // Test the model
    r.test(X_test, Y_test);

    return 0;
}
