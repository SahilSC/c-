#include <iostream>
#include <vector>
#include <list>
#include <stack>

using namespace std;

template<typename T>

void print(stack<T> t, string s = "") {
    if (!s.empty())
        cout << s << ": ";
    cout << "TOP: ";
    while (!t.empty()) {
        cout << t.top() << " ";
        t.pop();
    }
    cout << endl;
}

int main() {
    /*
     * CONSTRUCTORS
     */

    //1 - default constructor. can specify what container to use (deque/list/vector). deque is default
    stack<int> st;
    stack<int, deque<int>> stdeque;
    stack<int, list<int>> stlist;

    //2 - copy constructor from container
    vector<int> v1{1, 2, 3};
    list<int> l1{1, 2, 3};
    stack<int, list<int>> s2(l1);
    stack<int> s3(deque<int>{1, 2, 3});
    //stack<int> s4{1, 2, 3}; //doesn't work because stack is a adapter container. must use {{}} instead.
    stack<int> s5{{1, 2, 3}};

    //3 - copy constructor of another stack
    stack<int> s4(s3);
    print(s4);

    //6 - stack(InputIt begin, InputIt last) - creates stack with contents [begin, last)
    stack<int, list<int>> s7(l1.begin(), l1.end());

    /*
     * INSERTION/DELETION
     * push(Value v)
     * void pop(int v)
     */
    //push
    stack<int> qi{{2, 0, -1}};
    qi.push(-10);
    print(qi, "should be {-10, -1, 0, 2}");

    //pop
    stack<int> sig{{-1, 10, 20}};
    sig.pop();
    print(sig, "should be {10, -1}");

    /*
     * SELECTION
     * top()
     */
    stack<int> stop;
    stop.push(10);
    stop.push(3);
    cout << "top: " << stop.top() << endl; //3

    /*
     * USEFUL METHODS
     * empty()
     * size()
     */

    /*
     * MISC
     * - no provided iterator
     */
}