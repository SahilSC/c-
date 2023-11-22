#include <iostream>
#include "Dog.h"


int main(){
    Dog d;
    Dog d2 = Dog();
    const int& ref = 3;
    std::cout << d << std::endl;
}