#include <iostream>

int main(){

    /*
     * CONST
     * 1. Have to be initialized at assignment
     * 2. For pointers, only relative position of const to * matters
     */

    /*
     * REFERENCES
     * Note: int& const ref is illegal
     */
    int num1 = 10;
    const int& ref1 = num1;
    //int& const ref2 = num1; is wrong format
    num1 = 0;
    //ref1 = 0; is illegal.

    /*
     * POINTERS (3 types of const)
     * 1. const int* ptr (int const* ptr) = ptr can be modified but value pointed to cannot
     * 2. int* const ptr = ptr cannot be modified but value pointed to can
     * 3. const int* const ptr = ptr cannot be modified and nor can the value pointed to
     */

    //1.
    int x = 4;
    const int *constptr{&x};
    //(*constptr)++; not allowed
    constptr = nullptr;

    //2.
    int* const ptrconst{&x};
    //ptrconst = nullptr; illegal
    (*ptrconst)++;

    //3.
    const int* const constptrconst{&x};
    //constptrconst = nullptr; illegal
    //(*constptrconst)++; illegal
}