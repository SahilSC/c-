#include <iostream>
#include <vector>
#include <forward_list>
#include <list>
#include <vector>
#include <array>

using namespace std;

void increment(int &x) {
    x++;
}

void Log(int &x) {
    cout << x << endl;
}

void Log2(int const &x) {
    cout << x << endl;
}

/*
 * Iterators look like
 * - std::vector<int>::iterator A;
 * - std::vector<int>::const_iterator A;
 */
int main() {

    /*
     * ITERATOR TYPES
     * 1. Forward = advance one step forward at a time (++ postfix/prefix)
     *    - forward_list
     * 2. Bidirectional = advance one step forward/backward (++/-- postfix/prefix)
     *    - list
     *    - map
     * 3. Random Access Iterator= advance forward/backward any distance (++/-- postfix/prefix, +=/-=)
     *    - array
     *    - vector
     * Iterator hierarchy: 2 is 1, 3 is 2 and 1
     */

    //1. Forward
    forward_list<int> flist{1, 2, 3};
    auto st1 = flist.begin();
    st1++;
    //st1--; //all 3 below not allowed
    //st1+=;
    //st2-=;

    //2. Bidirectional
    list<int> blist{1, 2, 3};
    auto st2 = blist.begin();
    st2++;
    st2--;
    //st2+=1; //both not allowed
    //st2-=1;

    //3. Random Access
    array<int, 5> alist{1, 2, 3, 4, 5};
    vector<int> v1{1, 2, 3, 4, 5};
    auto st3 = alist.begin();
    auto st4 = alist.begin();
    //can add or subtract any amount
    st3++;
    st4 += 2;
    st3 -= 1;
    st3--;

    /*
     * TRAVERSAL
     * 1) next(iterator start, offset) - returns iterator to start + offset
     *   - Forward/bidirectional = O(N), random access = O(1)
     *   - undefined for negative numbers for forward
     * 2) distance(iterator start, iterator end) - return ptrdiff_t = end - start
     *   - Distance works for all types of iterators
     *   (note that using subtraction (endit - startit) only defined for RAI)
     */

    auto blist1 = blist.begin();
    auto blist2 = blist.begin();
    auto flist1 = flist.begin();
    auto flist2 = flist1;
    auto alist1 = alist.begin();

    //1.
    cout << *next(flist1, 2) << endl; //3
    cout << *next(next(flist1, 2), -2) << endl; // 1

    //2.
    ptrdiff_t ptrdif = distance(flist.begin(), flist.end());
    cout << "pointer diff " << ptrdif << endl; // 3
    long dif = alist1 - alist1;
    //long dif2 = flist2 - flist1; //not allowed to use for forward iterators
    //long dif3 = blist2 - blist1; //not allowed to use for bidirectional iterators

    /*
     * CONSTANT ITERATORS - append c to iterator
     */
    for_each(flist.begin(), flist.end(), Log);
    //for_each(flist.cbegin(), flist.cend(), Log);//only works if Log takes a const ref
    for_each(flist.cbegin(), flist.cend(), Log2);

    /*
     * REVERSE ITERATORS - append r
     * - Can combine const & reverse w/ crbegin
     */
    for_each(blist.rbegin(), blist.rend(), Log);

    /*
     * ITERATOR INVALIDATION
     * - Should be intuitive (e.g. resizing), but might need to reference documentation
     */
    vector<int> v2{1, 2, 3};
    auto vit2 = v2.begin();
    v2.resize(100);
    //cout << *vit2; //undefined behavior

    /*
     * ITERATOR TYPES
     * - useful with decltype
     */
    vector<int> v3{3, 4, 5};
    using myIterator = decltype(v3)::const_iterator;
    myIterator myIt = v3.begin();
    cout << *myIt; //3

    //TODO
    /*
     * ITERATORS WITH TEMPLATES
     */

}