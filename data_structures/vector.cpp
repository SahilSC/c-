#include <iostream>
#include <unordered_map>

using namespace std;

int main() {
    /*
     * CONSTRUCTORS
     */

    //1. Range constructor
    int myints[] = {10, 10, 10, 20, 20, 20, 30, 30};
    vector<int> v(myints, myints + 8);

    //2. Copy constructor
    vector<int> cpy1 = vector(v);

    /*
     * ALGORITHMS
     */
    sort(v.begin(), v.end());

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

}