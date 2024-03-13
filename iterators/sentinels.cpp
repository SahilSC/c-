#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

/*
 * We can define a range ending with sentinels rather than .end(). This may be preferred in cases
 * where we do not KNOW where .end() should point (.end() requires a specific return beforehand), like
 * in the case where you want to end when you first hit a negative number in a list.
 *
 * Sentinels have to be comparable to iterators with ==. If true, algo stops.
 *   - Sentinels define != before C++20, but with C++20, expression rewriting deems this unnecessary
 */

template <typename T>
struct Sentinel {
    bool operator==(T currentIterator) {
        return currentIterator == containerEnd || *currentIterator < 0;
    }

    T containerEnd;
};
void Log(int x){
    cout << x << endl;
}
int main(){

    /*
     * ITERATOR VS RANGE-BASED ALGOS
     * Consider
     *    - std::ranges::for_each(R.begin(), R.end(), Log)
     *    - std::        for_each(R.begin(), R.end(), Log)
     *    These do exactly the same
     * The difference is iterator-based algos require ending to be ITERATOR, whilst range-based algos
     * require ending to be SENTINEL (can be iterator but doesn't have to be)
     *
     */
    vector v1{1, 2, 3, 4, -1, 3};

    //it says CTAD would allow template deduction, but it doesn't work for some reason
    Sentinel s{v1.end()};

    for (auto it = v1.begin(); it != s; it++) {
        cout << *it << endl;
    }
    //TODO: Class template type deduction isn't working for line 41 and below even though it should
    ranges::for_each(v1.begin(), Sentinel<vector<int>::iterator>{v1.end()}, Log);

}
