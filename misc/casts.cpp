#include <iostream>
#include <memory>
using namespace std;

/*
 * Two main types of casting
 * Named casts : static_cast (build time), dynamic_cast, reinterpret_cast
 * C-style casts (should be avoided as they don't check for errors at compile-time)
 */
struct A{};
struct Character{
    virtual void Fight() {
        cout << "Character fight" << endl;
    }
};
struct Goblin : public Character{
    int level = {0};
    void Fight() override {
        cout << "Goblin fight!" << endl;
    }
    void Enrage() {
        cout << "Goblin MAD! Level: " << level << endl;
    }
};

void doStuff(Character& c) {
    c.Fight();

    /*
     * STATIC CASTING vs. DYNAMIC CASTING
     * compile            runtime
     *
     * static_cast<Child>(Parent) only checks if Parent is actually a parent of Child. Does NOT
     * check if the Parent is actually convertible to a Child
     *
     * static_cast<Goblin*>(&c)->Enrage(); runs as a result in doStuff, even if it shouldn't
     *
     * using dynamic_cast<Child>(Parent) either converts Parent to Child correctly
     * or returns nullptr
     *
     * Note: dynamic_cast only works if the type in () is polymorphic (a.k.a has a
     * virtual function). If it doesn't, it's common to set destructor to
     *
     * virtual ~SomeType() = default;
     */

    //static_cast<Goblin*>(&c)->Enrage(); Undefined behavior
    Goblin* g = dynamic_cast<Goblin*>(&c);
    if (g) {
        cout << "Yo this was a Goblin!" << endl;
    }
    else {
        cout << "Not a goblin..." << endl;
    }

}

void pointerStuff(shared_ptr<Character> c) {

    /*
     * SMART POINTERS
     * 1. Use static_pointer_cast and dynamic_pointer_cast, which return shared_ptrs instead of raw
     */

    shared_ptr<Goblin> gob {dynamic_pointer_cast<Goblin>(c)};
    if (gob) {
        cout << "Yo this was a Goblin!" << endl;
    }
    else {
        cout << "Not a goblin..." << endl;
    }
}


int main(){
    float f{4.1};
    int x{static_cast<int>(f)};
    int y = (int) f;

    int i = 10;
    A* a;
    //a = (A*) (&i); BOGUS!
    //a = static_cast<A*>(&i); caught by compiler!

    /*
     * DOWNCASTING: use static_cast<Child>(Parent)
     * If you downcast 'incorrectly', undefined behavior results
     */
    Character c;
    Goblin g;
    //doStuff(c); prints Goblin Mad! Level: [junk]. This is undefined behavior
    doStuff(g);
    doStuff(c);

    /*
     * Works with smart pointers too
     */
    auto character{make_shared<Character>()};
    auto goblin{make_shared<Goblin>()};

    pointerStuff(character);
    pointerStuff(goblin);
}