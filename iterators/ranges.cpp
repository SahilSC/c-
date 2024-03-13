#include <iostream>
#include <vector>
#include <algorithm>
#include <string>
using namespace std;
/*
 * Ranges are important for iterating through containers (many STL containers have it)
 * A range is any type with a begin() and end() method. With them, we can
 *    - use a range-based for loop
 *
 * We will examine how to implement our very own iterator
 */

//1. Expose iterator from underlying container that implements iterator
class Child{
public:
    Child(string name) : myName(name) {

    }

    string getName() const {
        return myName;
    }
private:
    string myName;
};

class Family {

public:
    void addChild(const Child& c) {
        list.push_back(c);
    };
    void removeChild() {};
    auto begin() {
        return list.begin();
    }
    auto end() {
        return list.end();
    }
private:
    std::vector<Child> list;
};

int main(){
    /*
     * RANGE CATEGORIES
     * Similar to iterators, a bidirectional range is a forward range, and a random-access range is
     * a bidirectional range
     */

    //TODO
    /*
     * RANGE CONCEPTS (63)
     */

    //TODO
    /*
     * RANGE ASSERTION (64)
     *
     */
    Child c1{"Sadge"};
    Child c2{"Monkey"};
    Child c3{"Sid"};
    Family f1;
    f1.addChild(c1);
    f1.addChild(c2);
    f1.addChild(c3);
    for (const auto &Child: f1) {
        cout << Child.getName() << endl;
    }
}