#include <iostream>
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
void makeStuff(Character* ptr) {
    cout << "Making stuff" << endl;
}

void uniqueinfo() {
    /*
     * UNIQUE POINTERS (Sole ownership (no copying allowed, copy ctor deleted)
     */

    /*
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
    unique_ptr<Character> unique_ptr {make_unique<Character>("Sam")};
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
     */

    /*
     * (no release)
     * 1. get()
     * 2. std::move()
     * 3. reset([new obj])
     * 4. swap()
     * 5. use_count() = number of owners
     * 6.
     */
    auto sharedptr{make_shared<Character>("Bibby")};
    auto other {sharedptr};
    cout << other.use_count() << endl; //2

}
/*
 * SMART POINTERS
 * Allocated on the stack and points to heap
 * Can dereference * and use -> like normal
 */
int main(){

//    uniqueinfo();
    sharedinfo();

}