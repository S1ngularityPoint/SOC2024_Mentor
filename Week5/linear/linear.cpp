#include "linear.h"

LinearRegression::LinearRegression(unsigned long D){
    d = D;
    weights = zeros(d,1);
    bias = 0;
}

void LinearRegression::GD(){

}