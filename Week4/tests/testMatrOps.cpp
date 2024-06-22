#include "../matrix/matrix.h"

/*

This file checks implementation and timing of the following functions : 
1]matmul
2]matrix inverse
It assumes basic operators and max,min,argmax,argmin as well as element wise functions are implemented correctly

*/

int main () {

    matrix a(identity(2));
    std::cout<<"Printing a:\n";
    /*
    
    EXPECTED OUTPUT:
    1 0 
    0 1

    */
    a.printMatrix();
    
    matrix b = exp(a);
    std::cout<<"Printing b:\n";
    /*
    
    EXPECTED OUTPUT:
    e 1 
    1 e

    */
    b.printMatrix();


    matrix c = b+1;
    c = matmul(c,b);
    std::cout<<"Printing c:\n";
    /*
    
    EXPECTED OUTPUT:
    12.11 9.15 
    9.15 12.11

    */
    c.printMatrix();

}