#include <iostream>
//necessary to use smart pointers
#include <memory>
#include <utility>

using namespace std;

struct Character {
    string name;

    Character(string name = "Bob") : name(name) {
        cout << name << " created" << endl;
    }

    ~Character() {
        cout << name << " deleted" << endl;
    }
};

void doStuff(unique_ptr<Character> ptr) {
    cout << "Doing stuff" << endl;
}

void makeStuff(Character *ptr) {
    cout << "Making stuff" << endl;
}

void uniqueinfo() {
    /*
     * UNIQUE POINTERS (Sole ownership (no copying allowed, copy ctor deleted, no copy assignment)
     */

    /*
     * METHODS
     * 1. get() = gets underlying raw pointer
     * 2. std::move() transfers ownership. Note this is one of the few times c++ makes assertions
     * about the moved away object, as you can do .get() on the original pointer and get nullptr
     * 3. release() = doesn't delete resource but rather "gives up" the raw pointer to us. Turns
     * into nullptr after & need to manually delete resource.
     * 4. reset([new obj]) = deletes resource and sets the pointer = nullptr or points to new obj
     * (however, note make_unique is exception-safe and preferred)
     * 5. swap() = swaps pointers
     */

    //Note Bob is deleted after Sam
    auto uniqueptr{make_unique<Character>("Bob")};
    unique_ptr<Character> unique_ptr{make_unique<Character>("Sam")};
    //auto uniqueptrcopy = uniqueptr; not allowed
    //doStuff(unique_ptr); can't copy by value

    makeStuff(unique_ptr.get()); //Making Stuff
    doStuff(std::move(unique_ptr)); //Doing Stuff
    //cout << unique_ptr->name << endl; //crash
    cout << unique_ptr.get() << endl; //note c++ actually states that this will be nullptr

    Character *rawuniqueptr{uniqueptr.release()};
    cout << uniqueptr.get() << endl; //becomes nullptr
    delete rawuniqueptr;

    auto newunique = make_unique<Character>("Frodo");
    newunique.reset();
    cout << newunique.get() << endl; // nullptr

    auto anotheruniq = make_unique<Character>("Bozo");
    anotheruniq.reset(new Character{"Sus"}); //Sus created, Bozo deleted

    auto sammy = make_unique<Character>("Sammy");
    auto hobble = make_unique<Character>("Hobble");
    cout << sammy->name << endl; //Sammy
    cout << hobble->name << endl; //Hobble
    sammy.swap(hobble);
    cout << sammy->name << endl; //Hobble
    cout << hobble->name << endl; //Sammy
    /*
     * PITFALLS
     * 1. Only use unique_ptr with free store/heap
     * 2. Don't make two unique_ptrs point to the same thing (ex. Pointer1.reset(Pointer2.get())
     */
}

void sharedinfo() {
    /*
     * SHARED POINTERS (allow multiple owners & deleted after last shared pointer deleted)
     * Downside: Keeping track of references and if something is a last reference takes more time,
     */

    /*
     * METHODS
     * (no release)
     * 1. get()
     * 2. std::move()
     * 3. reset([new obj]): Note this may not actually delete the underlying resource
     *    if a lot it has other owners
     * 4. swap()
     * 5. use_count() = number of owners
     * 6.
     */

    //3
    auto shared1 = make_shared<Character>("Sahil");
    auto shared2 = shared1;
    cout << "Shared count should be 2: " << shared2.use_count() << endl;
    shared2.reset();
    cout << "Underlying object still exists! The count of shared1 should be 1: " <<
         shared1.use_count() << endl;

    //5
    auto sharedptr{make_shared<Character>("Bibby")};
    auto other{sharedptr};
    cout << other.use_count() << endl;

    /*
     * Aliasing Constructor = share ownership with an object, but points to something different
     * shared_ptr(object to own, address of object to point at)
     *
     * Useful when
     *  - Want to only manipulate a single field of a shared object, but need the shared object to
     *  not be destroyed whilst in use (hence the addition of another ref_count through another
     *  shared_ptr)
     */
    shared_ptr<int> obj{make_shared<int>(1)};
    int two{2};
    shared_ptr<int> aliased{obj, &two};
    cout << "Should be 2: " << aliased.use_count() << endl;
    cout << "Points to value of 2: " << *aliased << endl;

    /*
     * PITFALLS
     * 1. Not copying shared pointers (e.g. shared_ptr<int> p1/p2 = {&x}; instead of copy assignment)
     */

}

void weakinfo() {
    /*
     * WEAK POINTERS
     * - Closely used with shared_pointers except do not actively participate in memory management.
     *   Similar to a view. If all shared_pointers to an object destroyed, a weak pointer is
     *   basically an empty pointer
     *
     * LOCKING:
     *   Because weak_pointers don't own the object they point to, they might have expired by the
     *   time we plan to use them. We must thus lock a weak pointer by first creating a shared
     *   pointer out of it and using that. It is a protection for multithreaded environments that
     *   may drop use_count to 0.
     *
     * USE CASES:
     * 1) Breaking circular references (e.g. two objects have a shared pointer to the other)
     * 2) Handling dangling pointers
     * 3) Caching mechanisms
     */

    /*
     * METHODS
     * 1) reset() - no parameters as weak pointers shouldn't manage memory anyways
     * 2) swap()
     * 3) use_count() - returns the number of shared_ptr references (doesn't act on weakptr)
     * 4) expired() - same as use_count() == 0. checks if underlying shared_pointer doesn't exist
     */

    //Often constructed with shared_ptr
    auto sharedptr{make_shared<Character>("Sam")};
    weak_ptr<Character> weak{sharedptr};

    //Can omit the type as it can be deduced from shared_ptr
    weak_ptr weakptr{sharedptr};
    weakptr.use_count();
    cout << "Should be 1: " << weakptr.use_count() << endl;

    //4
    if (!weakptr.expired()) {
        cout << "not expired" << endl;
    }
    sharedptr.reset();
    if (weakptr.expired()) {
        cout << "expired" << endl;
    }

    //Accessing a weak pointer using LOCKING
    auto sharedptr2{make_shared<int>(1)};
    weak_ptr weakptr2{sharedptr2};
    auto sharedptrforlock{weakptr2.lock()};
    if (sharedptrforlock) {
        cout << "Useable. Value should be 1: " << *sharedptrforlock << endl;
    }
    sharedptr2.reset();
    sharedptrforlock.reset();
    sharedptrforlock = {weakptr2.lock()};
    if (!sharedptrforlock) {
        cout << "Use count is 0." << endl;
    }
}

/*
 * SMART POINTERS
 * Allocated on the stack and points to heap
 * Can dereference * and use -> like normal
 */
int main() {

//    uniqueinfo();
//    sharedinfo();
    weakinfo();

}

/*
 * General tips:
 * Prefer unique_ptr > shared_ptr if you can because its faster
 */