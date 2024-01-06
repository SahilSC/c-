#include <iostream>
#include <utility>

using namespace std;


struct Goblin {
    int age;
    string name;
};

int main(){
    int myArray[3] = {1, 2, 3};

    pair<int, int> p{1, 2};

    /*
     * Structured binding.
     * 1. Must use auto keyword
     * 2. Must unpack all
     * 3. For user-defined classes, only works if all fields public
     */
    auto [first, second, third] = myArray;
    auto [age, name] = Goblin();
}