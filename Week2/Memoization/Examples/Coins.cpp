#include <iostream>
#include <algorithm>

#define Loop(i,a,b) for (int i = a ; i < b ; i++)
#define MOD 1000000007

typedef long long int ll;

using namespace std;

/*
    * INTRO :
    * After seeing the Fibonacci example most of you must have thought it is quite easy to come up with a way to minimise
    * the number of recursive calls to a function. 
    * The easiest way to do that would of course be to do it iteratively where f(n) = f(n - 1) + f(n - 2) and the results
    * could be stored in just two additional variables.
    * However in more general cases, we would be needing the results of various subproblems that are not exactly pertaining
    * to n - 1 or n - 2.
    * Here you will be able to appreciate the speedup due to memoization 
    
    * THE PROBLEM:
    * Consider a money system consisting of n coins. Each coin has a positive integer value. 
      Your task is to calculate the number of distinct ways you can produce a money sum x using the available coins.
      For example, if the coins are {2,3,5} and the desired sum is 9, there are 8 ways:
        2+2+5
        2+5+2
        5+2+2
        3+3+3
        2+2+2+3
        2+2+3+2
        2+3+2+2
        3+2+2+2
    * Input:
        The first input line has two integers n and x: the number of coins and the desired sum of money.
        The second line has n distinct integers c1,c2,...,c_n: the value of each coin.
    * Output
        Print one integer: the number of ways modulo 10^9+7.
    Example
        Input:
        3 9
        2 3 5
    Output:
        8
    * From CSES/Dynamic_Programming/Coin_Combinations_1
*/

void solution(){

}

int main(){

}