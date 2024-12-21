#include <iostream>

using namespace std;

struct A {

    A() = default;

    // Converting constructor
    A(int a) {
        cout << "Converted" << endl;
    }

    // Overloading typecast operator
    operator bool() const {
        return true;
    }
};

void typecastOperator(int A) {
    cout << "overloading typecast" << endl;
}

void convertingConstructor(A obj) {
    cout << "called converting constructor" << endl;
}

int main() {
    A a;

    // Overloading typecast operator
    typecastOperator(a);

    // Converting constructor
    convertingConstructor(3);
}