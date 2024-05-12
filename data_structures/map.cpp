#include <iostream>
#include <map>

using namespace std;

template<typename Key, typename Value, typename Cmp>
std::ostream &operator<<(std::ostream &os, map<Key, Value, Cmp> mp1) {
    os << "{ ";
    for (auto [a, b]: mp1) {
        os << a << ": " << b << ", ";
    }
    os << "}";
    return os;
}

int main() {
    /*
     * CONSTRUCTORS
     */

    //1 - default constructor
    map<string, int> mp1;
    mp1["a"] = 1;
    mp1["b"] = 2;
    mp1["c"] = 3;
    mp1["d"] = 4;
    cout << "mp1: " << mp1 << endl; // mp1: { a: 1, b: 2, c: 3, d: 4, }

    //4 - range constructor
    map<string, int> mp4{++mp1.begin(), mp1.find("d")};
    cout << "mp4: " << mp4 << endl; // mp4: { b: 2, c: 3, }

    //6 - copy constructor
    map<string, int> mp6{mp1};
    cout << "mp6: " << mp6 << endl; // mp6: { a: 1, b: 2, c: 3, d: 4, }

    //8 - move constructor
    map<string, int> temp;
    temp["Lee"] = 1;
    map<string, int> moved{std::move(temp)}; //invalid state
    cout << "new moved: " << moved << endl; // new moved: { Lee: 1, }

    //10 - initializer list constructor
    map<string, int> grades
            {
                    {"John",  10},
                    {"Jane",  20},
                    {"Sally", 30}
            };
    cout << "grades: " << grades << endl; //grades: { Jane: 20, John: 10, Sally: 30, }


    /*
     * INSERTION
     */


    /*
     * SELECTION
     */

    /*
     * DELETION
     */

    /*
     * MISC
     *
     */


    /*
     * USEFUL METHODS
     */



}