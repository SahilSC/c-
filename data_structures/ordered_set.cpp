/*
 * Ordered Set in GNU C++ PBDS
 * It is a policy based data structure like set<T> in C++ that supports
 * all set<T> operations in log(n) as well as order statistics. Below are the log(n)
 * methods
 * - order_of_key(k) number of elements strictly less than k
 * - find_by_order(k) lth order in the set
 * -
 * Need to compile with gcc if you actually want to use
/*
 * Tutorial: https://www.geeksforgeeks.org/ordered-set-gnu-c-pbds/
 * Problem: https://cses.fi/problemset/submit/2162/
 */

//includes our tree
#include <ext/pb_ds/assoc_container.hpp>
//includes tree_order_statistics_node_update
#include <ext/pb_ds/tree_policy.hpp>

using namespace __gnu_pbds;
using namespace std;

/*
 * template<
 * 	  typename Key, // Key type
 * 	  typename Mapped, // Mapped-policy
 * 	  typename Cmp_Fn = std::less<Key>, // Key comparison functor
 * 	  typename Tag = rb_tree_tag, // Specifies which underlying data structure to use
 */
using ordered_set = tree<int, null_type, less<int>, rb_tree_tag, tree_order_statistics_node_update>

// Driver program to test above functions
int main()
{
    // Ordered set declared with name o_set
    ordered_set o_set;

    // insert function to insert in
    // ordered set same as SET STL
    o_set.insert(5);
    o_set.insert(1);
    o_set.insert(2);

    // Finding the second smallest element
    // in the set using * because
    //  find_by_order returns an iterator
    cout << *(o_set.find_by_order(1)) //2
         << endl;

    // Finding the number of elements
    // strictly less than k=4
    cout << o_set.order_of_key(4)
         << endl; //2

    // Finding the count of elements less
    // than or equal to 4 i.e. strictly less
    // than 5 if integers are present
    cout << o_set.order_of_key(5)
         << endl; //2

    // Deleting 2 from the set if it exists
    if (o_set.find(2) != o_set.end())
        o_set.erase(o_set.find(2));

    // Now after deleting 2 from the set
    // Finding the second smallest element in the set
    cout << *(o_set.find_by_order(1))
         << endl; //5

    // Finding the number of
    // elements strictly less than k=4
    cout << o_set.order_of_key(4)
         << endl; //1

    return 0;
}
