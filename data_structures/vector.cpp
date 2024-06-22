
#include <iostream>
#include <numeric>
#include <vector>
#include <algorithm>
#include <unordered_map>

using namespace std;

template<typename T>
void print(vector<T> v, string s = "") {
    if (!s.empty())
        cout << s << ": ";
    for_each(v.begin(), v.end(), [](T a) { cout << a << " "; });
    cout << endl;
}

struct Pair {
    int x;
    int y;

    friend ostream &operator<<(ostream &o, Pair p) {
        o << "{" << p.x << ", " << p.y << "}";
        return o;
    }
};

struct cmp {
    bool operator()(Pair a, Pair b) {
        if (a.x != b.x) return b.x < a.x;
        return b.y < a.y;
    }
};

struct Interval {
    int x;
    int y;

    friend ostream &operator<<(ostream &o, Interval p) {
        o << "{" << p.x << ", " << p.y << "}";
        return o;
    }

    bool operator<(Interval p2) const {
        if (this->x != p2.x) return this->x - p2.x;
        return this->y != p2.y;
    }
};

int main() {
    /*
     * CONSTRUCTORS
     */

    //1. Default constructor
    vector<int> defv;

    //2. Range constructor
    int myints[] = {10, 10, 10, 20, 20, 20, 30, 30};
    vector<int> v(myints, myints + 8);
    vector<int> v2(defv.begin(), defv.end());

    //3. Copy constructor
    vector<int> cpy1{v};
    vector<int> cpy3(v);

    //4. Copy elements N times
    vector<std::string> words4(5, "Mo"); //Mo Mo Mo Mo Mo
    print(words4);

    //5. Reserve size of vector and default initialization
    vector<int> alrsized(17);
    cout << "sized: " << alrsized.capacity() << endl; //17
    print(alrsized);

    //6. Reserve size and initialize all contents of vector with second elemengt
    vector<int> sizeAndInit(17, 1);
    print(sizeAndInit);

    //7. Initializer List
    vector<int> a{1, 2, 3};
    print(a); //1 2 3

    //8. Copy initialization
    vector<int> b = vector(a);

    /*
     * INSERTION
     */

    vector<int> temp{1, 10, 100, 1000};

    //1. push_back(Value v) - adds to end
    temp.push_back(5);
    print(temp);

    //2. emplace_back - passes constructor arguments
    temp.emplace_back(10);

    //3. insert(Iterator it, Value v) - inserts v at value after +;
    temp.insert(temp.begin(), 5);
    print(temp); // 5 is at beginning

    //4. insert(Iterator it, size_t count, Value v) - inserts count of v before it
    temp.insert(temp.begin(), 10, -1);
    print(temp);

    //4. insert(const_iterator pos, InputIt first, InputIt last) - inserts contents of [first, last) before pos
    vector<int> tempinsert{1, -1, 2, -2};
    temp.insert(temp.begin() + 2, tempinsert.begin(), tempinsert.end());
    print(temp);


    /*
     * DELETION
     * erase(input it)/erase(input first, input second) - erases elements at it or from [first, second)
     * pop_back() - delete last element
     */
    vector<int> ea1{1, 2, 3, 4};
    ea1.erase(ea1.begin(), ea1.end() - 2);
    cout << "erase! ";
    print(ea1);


    /*
     * ALGORITHMS
     * sort(RandomIt st, RandomIt end)/sort(RandomIt st, RandomIt end, Compare comp)
     */

    //sort
    sort(v.begin(), v.end());
    print(v, "increasing sorted vector");

    //less (default) uses <, greater uses >
    sort(v.begin(), v.end(), greater<>());

    vector<Pair> pv{{1,  5},
                    {1,  3},
                    {-1, 10}};
    //sort using lambda
    sort(pv.begin(), pv.end(), [](const Pair &p1, const Pair &p2) {
        if (p1.x != p2.x) return p1.x - p2.x;
        else return p1.y - p2.y;
    });
    print(pv, "pairs sorted");

    //sort using operator<
    vector<Interval> interval{{1,  5},
                              {1,  3},
                              {-1, 10}};
    sort(interval.begin(), interval.end());
    print(interval, "interval sorted");

    //sort using custom struct
    vector<Pair> pv2{{1, -5},
                     {2, -1},
                     {1, 0}};
    sort(pv2.begin(), pv2.end(), cmp{});
    print(pv2, "interval sorted via struct");

    /*
     * Upperbound = iterator to element in range [start, end) that is greater than val or last if
     * not found
     * Lowerbound = iterator to element in
     * @param start = iterator begin, end = iterator end (exclusive), val = to search for
     */
    vector<int> cpy2 = vector(v);
    vector<int>::iterator it2 = upper_bound(cpy2.begin(), cpy2.end(), 10);
    cout << it2 - cpy2.begin() << endl; //3
    vector<int>::iterator it3 = lower_bound(cpy2.begin(), cpy2.end(), 20);
    cout << it3 - cpy2.begin() << endl; //3

    /*
     * USEFUL METHODS
     * - assign(count, value)/assign(input it, input end)/assign(initializer list) - REPLACES contents
     * - resize(count)/resize(count, Value val) - does nothing or shortens if count < v.size(), otherwise adds
     *      default-initialized values or v
     * - reserve(count) - changes capacity to count (BUT SIZE IS UNCHANGED) so vector doesn't have to resize as much
     * - clear() - clear vectors (capacity unchanged)
     * - iota(InputIt st, InputIt end, Value v) - fills [st, end) with v,v+1, etc.
     */
    //assign
    vector<int> a1;
    a1.assign(10, 100);
    print(a1);

    //resize
    vector<int> a2;
    a2.resize(10);
    a2.push_back(4);
    cout << "a2 size " << a2.size() << endl; //ADDS to size of vector!
    a2.resize(1, -999); //a2 is unchanged
    print(a2);

    //reserve
    a2.reserve(10000); //size is unchanged
    cout << "a2 size after reserve: " << a2.size() << endl; //ADDS to size of vector!

    //iota
    vector<int> viota(10);
    iota(viota.begin(), viota.end(), 0);
    cout << "viota has values from 0 to 9: ";
    print(viota);


}



