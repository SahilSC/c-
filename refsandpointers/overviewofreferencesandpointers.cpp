#include <iostream>

using namespace std;

void increment_ref(int &x) {
    x++;
}

void increment_ptr(int* ptr) {
    (*ptr)++;
}

int main() {

    /*
     * REFERENCES
     */

    /*
     * Ref = exactly like an alias (whenever ref is encountered,
     * replaced with memory address of i). It's unknown whether
     * ref's even have their own memory address (unlike pointers)
     *
     * 1. Must initialize reference when declaring it;
     * Something like int& ref doesn't work
     *
     */

    int num = 5;
    int& ref = num;

    cout << &num << endl;
    cout << ref << endl; //5
    cout << &ref << endl; //Both &num and &ref have same memory address

    int num2 = 6;
    ref = num2;

    //2. Can't reassign the memory address. &ref still same as before
    cout << ref << endl; //6
    cout << &ref << endl; //Same as before
    cout << num << endl; //6

    //3. Must initialize references in member initialization list bc 2.
    struct Character {
        int& reference;
        Character(int& ref) : reference(ref) {};
    };

    /*
     * POINTERS
     */

    /*
     * & = address-of operator. When used in declaration, it creates
     * reference. When used next to a value with a memory address,
     * it returns a POINTER to that memory address. (can't assign
     * reference to something you used & on)
     */
    int num3 = 7;
    int* ptr;
    ptr = &num3;

    //1. Unlike references, they store the memory address of the pointed to thing
    cout << ptr << endl;
    //2. To get the thing stored as the memory address in a pointer, use * (same type as pointer)
    cout << *ptr << endl; //7


    /* Order of operations with pointers.
     * *ptr++ = *(ptr++). This will increase the memory address ptr has and then deference that.
     * Likely not wanted.
     */
    int num4 = 0;
    int* ptr2{&num4};

    cout << (*ptr2)++ << endl; //increments value of num4 to 1
    cout << num4 << endl; //1

    //Arrow operator. Same as ptr->method/field = (*ptr).method/field
    struct Goblin {
        int age;
    };
    Goblin gobo{13};
    Goblin* gobgob{&gobo};
    gobgob->age = 20;
    cout << gobo.age << endl; //20

    //Nullptr. Never should dereference (error)
    int* null{nullptr};


    /*
     * REFERENCES VS POINTERS
     * 1. Pointers don't need to be initialized
     * 2. Pointers can have a null value (nullptr)
     * 3. Pointers can the memory address pointed to
     * 4. Pointers directly store the memory address, whereas refs store the value
     * 5. Arrow operator only works for pointers
     */

    //Slightly different syntax for passing into function.
    int myNum = 5;
    increment_ptr(&myNum);
    increment_ref(myNum);

}