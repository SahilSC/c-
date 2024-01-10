#include <iostream>
using namespace std;

/*
 * Two main types of casting
 * Named casts : static_cast (build time), dynamic_cast, reinterpret_cast
 * C-style casts (should be avoided as they don't check for errors at compile-time)
 */
struct A{};
int main(){
    float f{4.1};
    int x{static_cast<int>(f)};
    int y = (int) f;

    int i = 10;
    A* a;
    a = (A*) (&i); //BOGUS!
    //a = static_cast<A*>(&i); caught by compiler!
}