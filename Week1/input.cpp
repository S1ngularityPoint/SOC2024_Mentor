#include <iostream>

#define Loop(i,a,b) for (int i = a ; i < b ; i++)
#define MAX 1000
using namespace std;

int main(int argc, char* argv[]){
    int n = stoi(argv[1]), m = stoi(argv[2]), p = stoi(argv[3]);
    cout << n << " " << m << " " << p << "\n";
    Loop(i,0,n) {
        Loop(j,0,m) cout << rand()%MAX << " ";
        cout << "\n";
    }
    Loop(i,0,m) {
        Loop(j,0,p) cout << rand()%MAX << " ";
        cout << "\n";
    }    
}
