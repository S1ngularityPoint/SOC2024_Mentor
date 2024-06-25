#include "linear.h"

LinearRegression::LinearRegression(unsigned long D){
    d = D;
    weights = zeros(d,1);
    bias = 0;
    epsilon = E;
}

void LinearRegression::l2loss(matrix X, matrix Y){
    __size d1 = X.shape(), d2 = Y.shape();
    if (d1.first != d2.first || d2.second != 1){

    }
}

void LinearRegression::GD(){

}