#include "matrix/matrix.h"

class LinearRegression{
    public:
        unsigned long d; // The dimensions of the data. The input is a 1xd vector
        matrix weights; // The weights are a dx1 vector
        double bias;
        LinearRegression(unsigned long);
        void loss();
        void GD();

};
