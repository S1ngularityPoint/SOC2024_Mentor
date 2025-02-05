#include "logistic.h"
#include "../matrix/matrix.h"

LogisticRegression::LogisticRegression(uint64_t D){
    d = D;
    weights = zeros(d,1);
    bias = 0;
    epsilon = EPS;
    eta = ETA;
}

matrix LogisticRegression::sigmoid(matrix z){
    matrix Z = -z;
    matrix g = 1.0*ones(z.rows,1);
    g = g/(g + exp(Z));
    return g;
}

double LogisticRegression::logisticLoss(matrix X, matrix Y){
    matrix Y_pred = sigmoid((matmul(X,weights) + bias));
    __size d1 = Y.shape(), d2 = Y_pred.shape();
    if (d1 != d2){
        throw std::invalid_argument("Cannot compute loss of vectors with dimensions ( "+to_string(d1.first)+" , "
        +to_string(d1.second)+" ) and ( "+to_string(d2.first)+" , "+to_string(d2.second)+" ) do not match");
    }
    uint64_t n = max(d1.first,d1.second);
    matrix Yt = Y.transpose();
    matrix Y_ = 1 - Y_pred;
    matrix Y__ = 1 - Yt;
    double loss = -(dot(Yt,(log(Y_pred))) + dot(Y__,(log(Y_))));
    loss /= n;
    return loss;
}

pair<matrix, double> LogisticRegression::lossDerivative(matrix X, matrix Y){
    matrix Y_pred = sigmoid((matmul(X,weights) + bias));
    __size d1 = Y.shape(), d2 = Y_pred.shape();
    if (d1 != d2){
        throw std::invalid_argument("Cannot compute loss derivative of vectors with dimensions ( "+to_string(d1.first)+" , "
        +to_string(d1.second)+" ) and ( "+to_string(d2.first)+" , "+to_string(d2.second)+" ) do not match");
    }
    uint64_t n = X.shape().first;
    matrix Xt = X.transpose();
    matrix diff = (Y_pred - Y);
    matrix dw = (matmul(Xt,diff))/n; 
    double db = (dot(ones(1,n),diff))/n;
    return {dw,db};
}

matrix LogisticRegression::predict(matrix X){
    matrix Y_pred = sigmoid(matmul(X,weights) + bias);
    uint64_t n = Y_pred.shape().first;
    for (uint64_t i = 0 ; i < n ; i++){
        if (Y_pred(i,0) >= 0.5) Y_pred(i,0) = 1;
        else Y_pred(i,0) = 0;
    }
    return Y_pred;
}  

void LogisticRegression::GD(matrix X, matrix Y,double learning_rate, uint64_t limit){
    eta = learning_rate;
    double old_loss = 0,loss = logisticLoss(X,Y);
    train_loss.PB(loss);
    uint64_t iteration = 0;
    max_iterations = limit;
    while (fabs(loss - old_loss) > epsilon && iteration < max_iterations){
        old_loss = loss;
        auto[dw,db] = lossDerivative(X,Y);
        weights = weights - eta*dw;
        bias = bias - eta*db;
        loss = logisticLoss(X,Y);
        train_loss.PB(loss);
        iteration++;
    }
}

void LogisticRegression::train(matrix X,matrix Y,double learning_rate, uint64_t limit){
    GD(X,Y,learning_rate,limit);
    cout << "Training Loss\n";
    for (uint64_t i = 0; i < train_loss.size() ; i++){
        cout << train_loss[i] << "\n";
    }
}

void LogisticRegression::test(matrix X,matrix Y){
    matrix Y_pred = predict(X);
    uint64_t n = X.shape().first;
    cout << "Predictions(GD) \t True Value\n"; 
    for (uint64_t i = 0 ; i < n ; i++){
        cout << Y_pred(i,0) <<  "\t\t\t " << Y(i,0) << "\n";
    }
    cout << "Testing loss " << logisticLoss(X,Y) << "\n";
    cout << "Testing accuracy " << accuracy(Y_pred,Y) << "\n";

}

double LogisticRegression::accuracy(matrix Y_pred, matrix Y){
    double acc = 0;
    uint64_t n = Y.shape().first;
    for (uint64_t i = 0 ; i < n ; i++){
        acc += (Y(i,0) == Y_pred(i,0));
    }
    acc = acc/n;
    return acc;
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