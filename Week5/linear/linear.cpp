#include "linear.h"

LinearRegression::LinearRegression(uint64_t D){
    d = D;
    weights = zeros(d,1);
    weights_ = zeros(d,1);
    epsilon = EPS;
    eta = ETA;
}

double LinearRegression::l2loss(matrix X, matrix Y){
    matrix Y_pred = matmul(X,weights);
    __size d1 = Y.shape(), d2 = Y_pred.shape();
    if (d1 != d2){
        throw std::invalid_argument("Cannot compute loss of vectors with dimensions ( "+to_string(d1.first)+" , "
        +to_string(d1.second)+" ) and ( "+to_string(d2.first)+" , "+to_string(d2.second)+" ) do not match");
    }
    uint64_t n = max(d1.first,d1.second);
    double loss = norm(Y_pred - Y);
    loss *= loss;
    loss /= n;
    return loss;
}

matrix LinearRegression::l2lossDerivative(matrix X, matrix Y){
    matrix Y_pred = matmul(X,weights);
    __size d1 = Y.shape(), d2 = Y_pred.shape();
    if (d1 != d2){
        throw std::invalid_argument("Cannot compute loss derivative of vectors with dimensions ( "+to_string(d1.first)+" , "
        +to_string(d1.second)+" ) and ( "+to_string(d2.first)+" , "+to_string(d2.second)+" ) do not match");
    }
    matrix Xt = X.transpose();
    matrix Z = matmul(Xt,X);
    matrix dw = 2*(matmul(Z,weights)) - 2*(matmul(Xt,Y));
    return dw;
}

matrix LinearRegression::predict(matrix X){
    return matmul(X,weights);
}  

void LinearRegression::GD(matrix X, matrix Y,double learning_rate, uint64_t limit){
    eta = learning_rate;
    double old_loss = 0,loss = l2loss(X,Y);
    train_loss.PB(loss);
    uint64_t iteration = 0;
    max_iterations = limit;
    while (fabs(loss - old_loss) > epsilon && iteration < max_iterations){
        old_loss = loss;
        weights = weights - eta*l2lossDerivative(X,Y);
        loss = l2loss(X,Y);
        train_loss.PB(loss);
        iteration++;
    }
}

void LinearRegression::train(matrix X,matrix Y,double learning_rate, uint64_t limit){
    matrix Xt = X.transpose();
    matrix Z = matmul(Xt,X);
    weights_ = matmul((Z.inverse()),matmul(Xt,Y));
    GD(X,Y,learning_rate,limit);
    cout << "Training Loss\n";
    for (uint64_t i = 0; i < train_loss.size() ; i++){
        cout << train_loss[i] << "\n";
    }
}

void LinearRegression::test(matrix X,matrix Y){
    matrix Y_pred = predict(X);
    uint64_t n = X.shape().first;
    matrix Y_closed = matmul(X,weights_);
    cout << "Predictions(GD) \t Predictions(C) \t True Value\n"; 
    for (uint64_t i = 0 ; i < n ; i++){
        cout << Y_pred(i,0) << "\t\t\t "<< Y_closed(i,0) << "\t\t\t " << Y(i,0) << "\n";
    }
    cout << "Testing loss " << l2loss(X,Y) << "\n";

}

pair<pair<matrix, matrix>, pair<matrix, matrix>> test_train_split(matrix X, matrix Y, float ratio) {
    if (ratio < 0 || ratio > 1) {
        throw std::invalid_argument("Ratio must be between 0 and 1");
    }

    uint64_t n = X.shape().first;
    uint64_t train_size = static_cast<uint64_t>(n * ratio);
    uint64_t test_size = n - train_size;

    std::vector<uint64_t> indices(n);
    std::iota(indices.begin(), indices.end(), 0);
    std::random_device rd;
    std::mt19937 g(rd());
    std::shuffle(indices.begin(), indices.end(), g);

    matrix X_train(train_size, X.shape().second);
    matrix Y_train(train_size, 1);
    matrix X_test(test_size, X.shape().second);
    matrix Y_test(test_size, 1);

    for (uint64_t i = 0; i < train_size; ++i) {
        for (uint64_t j = 0; j < X.shape().second; ++j) {
            X_train(i, j) = X(indices[i], j);
        }
        Y_train(i, 0) = Y(indices[i], 0);
    }

    for (uint64_t i = 0; i < test_size; ++i) {
        for (uint64_t j = 0; j < X.shape().second; ++j) {
            X_test(i, j) = X(indices[train_size + i], j);
        }
        Y_test(i, 0) = Y(indices[train_size + i], 0);
    }

    return {{X_train, Y_train}, {X_test, Y_test}};
}