#include <iostream>

using namespace std;

struct Dog {
    int age;

    Dog(int age) : age(age) {}

    int dogAge() { return age; };

    /*
     * [=]/[this] - captures this
     *   inside, this->var and var are the same
     */
    auto getAge() {
        return [=] { return age; };
    }
};

/*
 * LAMBDA FUNCTIONS
 */
int main() {
    Dog a(3);
    auto getAgeFunction = a.getAge();
    cout << getAgeFunction() << endl;
}