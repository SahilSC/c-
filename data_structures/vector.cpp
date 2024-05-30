#include <iostream>
#include <unordered_map>

using namespace std;

template<typename T>
void print(vector<T> v) {
    for_each(v.begin(), v.end(), [](T a) { cout << a << " "; });
    cout << endl;

}

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

    //2. emplace_back
    temp.emplace_back(10);

    //3. insert(Iterator it, Value v) -


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