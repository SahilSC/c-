#include <iostream>
#include <vector>
#include <map>

using namespace std;

template<typename Key, typename Value, typename Cmp>
std::ostream &operator<<(std::ostream &os, const map<Key, Value, Cmp> &mp1) {
    os << "{ ";
    for (auto [a, b]: mp1) {
        os << a << ": " << b << ", ";
    }
    os << "}";
    return os;
}

struct Pair {
    int x, y;

    friend std::ostream &operator<<(std::ostream &os, const Pair &p) {
        os << "{" << p.x << ", " << p.y << "}";
        return os;
    }
};

struct PairCmp {

    //returns true if a < b
    bool operator()(const Pair &a, const Pair &b) const {
        return a.x - b.x != -1 ? a.x < b.x : a.y - b.y;
    }
};

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

    //2 - custom key function 1
    map<Pair, int, PairCmp> pairs1{{{1,  1},  2},
                                   {{11, 1},  {5}},
                                   {{-1, 10}, -1},
                                   {{10, 4},  7}};
    cout << "pairs1: " << pairs1 << endl; //{ {-1, 10}: -1, {1, 1}: 2, {10, 4}: 7, {11, 1}: 5, }

    //3 - custom key function 2
    auto lmbda = [](const Pair &a, const Pair &b) {
        return a.x - b.x != -1 ? a.x < b.x : a.y - b.y;
    };
    map<Pair, int, decltype(lmbda)> pairs2(lmbda);
    pairs2.insert({{1, 1}, 2});
    pairs2.insert({{11, 1}, 5});
    pairs2.insert({{-1, 10}, -1});
    pairs2.insert({{10, 4}, 7});
    cout << "pairs2: " << pairs2 << endl; //{ {-1, 10}: -1, {1, 1}: 2, {10, 4}: 7, {11, 1}: 5, }


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
    map<string, int> mymap{{"Dog",    2},
                           {"Monkey", 3}};

    //1) insert({key, value}) - returns [iterator: to start, bool: success]
    auto [it, inserted] = mymap.insert({"Money", 3});
    cout << "*it: " << it->first << ", " << it->second << " inserted: " << inserted
         << endl; //*it2: Money, 3 inserted2: 0
    cout << "mymap: " << mymap << endl; //{ Dog: 2, Money: 3, Monkey: 3, }
    auto [it2, inserted2] = mymap.insert({"Money", 3});
    cout << "*it2: " << it2->first << ", " << it2->second << " inserted2: " << inserted2
         << endl; //*it2: Money, 3 inserted2: 0

    //2) insert(Iterator start, Iterator end) - doesn't insert if exists
    map<string, int> anotherMap{{"Apple",  2},
                                {"Banana", 3},
                                {"Orange", 2}};
    anotherMap.insert(mymap.begin(), mymap.end());
    anotherMap.insert({"Apple", 5});

    cout << "anotherMap: " << anotherMap
         << endl; //anotherMap: { Apple: 2, Banana: 3, Dog: 2, Money: 3, Monkey: 3, Orange: 2, }

    //3) insert_or_assign({Key k, Value v})
    cout << "anotherMap: " << anotherMap
         << endl; //anotherMap: { Apple: 6, Banana: 3, Dog: 2, Money: 3, Monkey: 3, Orange: 2, }

    //4) emplace(...) - passes elements to constructor (doesn't insert if exists)
    map<string, int> hinata{{"hin",  1},
                            {"anat", 2}};
    hinata.emplace("Ya", 1);

    //5) [] syntax inserts if DNE
    mymap["Donkey"] = 5;

    /*
     * SELECTION
     */

    //- at() - has bounds checking
    cout << grades.at("John") << endl; //10

    //- [] syntax - no bounds checking but adds element to the list if DNE
    cout << grades["Jane"] << endl; //20
    cout << grades["asd"] << endl; //0
    cout << grades << endl; // { Jane: 20, John: 10, Sally: 30, asd: 0, }

    /*
     * DELETION
     */

    //1) erase(Iterator it)
    map<string, int> mm{{"a", 1},
                        {"b", 2}};
    mm.erase(mm.begin());
    cout << "mm: " << mm << endl; //mm: { b: 2, }

    //2) erase(Key k)
    mm.erase("b");
    cout << "mm: " << mm << endl; //mm:


    /*
     * USEFUL METHODS
     */
    /*
     * Find an element
     * - find() (better) -> iterator to item or end
     * - count() -> int
     * - contains() -> bool (C++20)
     */
    map<string, int> nn{{"a", 1}};
    cout << "count a " << nn.count("a") << endl; //1
    cout << "finding a " << (nn.find("a") == nn.begin()) << endl; //1
    cout << "finding b " << (nn.find("b") == nn.begin()) << endl; //1
    cout << "contains a  " << nn.contains("a") << endl;  //0

    /*
     * Size/Empty
     * - size()
     * - empty()
     * - reserve(size_t count)- reserves enough buckets so at least count entries could be placed
     */
    cout << "size: " << nn.size() << endl; //1
    cout << "is empty?: " << nn.empty() << endl; //0

    /*
     * Bounding
     * - lower_bound(Key k) -> iterator: first item not less than key or end()
     * - upper_bound(Key k) -> iterator: first item greater than key or end()
     */
    map<int, int> sorted{{1,  1},
                         {3,  2},
                         {7,  3},
                         {10, 4}};
    cout << sorted.lower_bound(7)->first << endl; //7
    cout << sorted.lower_bound(8)->first << endl; //10
    cout << sorted.upper_bound(7)->first << endl; //10

    /*
     * Starting & End Iterators
     * - begin() -> iterator: beginning
     * - end() -> iterator: end
     */

    /*
     * MISC
     * - bidirectional iterators
     * - to reverse sort a map, pass in std::greater<Key k> as third param
     */
}