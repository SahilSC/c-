#include <iostream>
//rand()
#include <cstdlib>
//used from uniform_int_distribution
#include <random>

using namespace std;

/*
 * rand() = returns num from [0, 32767 (at least). limited random though
 * uniform_int_distribution<>(a, b) = returns number from [a, b] with equal probability
 */
int main() {
    int max = 20;
    for (int i = 0; i < 100; i++) {
        cout << rand() % 20 + 1 << endl;
    }

    random_device rd; //seed source
    mt19937 gen(rd()); //generates random numbers from seed
    uniform_int_distribution<> unigen(1, max);
    for (int i = 0; i < 100; i++) {
        cout << unigen(gen) << endl;
    }
}