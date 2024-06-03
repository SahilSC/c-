#include <iostream>
#include <queue>
#include <vector>
#include <stack>
#include <set>
#include <list>
#include <deque>

using namespace std;

template<typename T>

void print(queue<T> t, string s = "") {
    if (!s.empty())
        cout << s << ": ";
    while (!t.empty()) {
        cout << t.front() << " ";
        t.pop();
    }
    cout << endl;
}

int main() {
    /*
     * CONSTRUCTORS
     */

    //1 - default constructor. can specify what container to use (deque/list). deque is default
    queue<int> q1;
    queue<int, deque<int>> qdeque;
    queue<int, list<int>> qlist;

    //2 - copy constructor from container
    vector<int> v1{1, 2, 3};
    list<int> l1{1, 2, 3};
    queue<int, list<int>> q2(l1);
    queue<int> q3(deque<int>{1, 2, 3});
    //queue<int> q4{1, 2, 3}; //doesn't work because queue is a adapter container. must use {{}} instead.
    queue<int> q5{{1, 2, 3}};

    //3 - copy constructor of another queue
    queue<int> q4(q3);
    print(q4);

    //6 - queue(InputIt begin, InputIt last) - creates queue with contents [begin, last)
    queue<int, list<int>> q7(l1.begin(), l1.end());

    /*
     * INSERTION/DELETION
     * push(Value v)/emplace(constructor args)
     * void pop(int v)
     */
    //push
    queue<int> qi{{2, 0, -1}};
    qi.push(-10);
    print(qi, "should be {2, 0, -1, -10}");

    //pop
    queue<int> qi2{{-1, 10, 20}};
    qi2.pop();
    print(qi2, "should be {10, 20}");

    /*
     * SELECTION
     * front()
     * back()
     */
    //front/back
    queue<int> qs{{1, 2, 3}};
    cout << qs.front() << endl; //1
    cout << qs.back() << endl; //3

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