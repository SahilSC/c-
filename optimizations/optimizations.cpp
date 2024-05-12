#include <iostream>
#include <vector>
#include <chrono>

using namespace std;

const int N = 10000;
int arr[N][N];
int arr2[N][N];

int main() {
    auto start = chrono::high_resolution_clock::now();
    int inc = 1;
    for (int i = 0; i < N; i += inc) {
        for (int j = 0; j < N; j += inc) {
            arr[i][j] = 10;
        }
    }
    auto end = chrono::high_resolution_clock::now();
    cout << chrono::duration_cast<chrono::nanoseconds>(end - start).count() << endl;


    //Measure time
    auto start1 = chrono::high_resolution_clock::now();
    int inc2 = inc;
    for (int i = 0; i < N; i += inc2) {
        for (int j = 0; j < N; j += inc2) {
            arr2[i][j] *= 10;
        }
    }
    auto end1 = chrono::high_resolution_clock::now();
    cout << chrono::duration_cast<chrono::nanoseconds>(end1 - start1).count() << endl;


}