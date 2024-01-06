#include <iostream>
#include "smartpointer.h"

void testpointer() {
    smartpointer<int> a(new int(3));
    a.getReferenceCount();
    smartpointer<int> b(a);
    a.getReferenceCount();
    b.getReferenceCount();
    smartpointer<int> c(new int(5));
    c.getReferenceCount();
    cout << endl;
    c = a;
    a.getReferenceCount();
    b.getReferenceCount();
    c.getReferenceCount();
//    b = a;

}

int main(){
//    std::cout << "a";
    testpointer();
}