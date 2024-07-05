#include <iostream>
#include <queue>
#include <vector>
#include <stack>
#include <set>
#include <list>
#include <deque>

using namespace std;

template<typename T, typename Container = std::vector<T>, typename Compare = std::less<T>>
void print(std::priority_queue<T, Container, Compare> pq, const std::string &s = "") {
    if (!s.empty()) std::cout << s << ": ";
    while (!pq.empty()) {
        std::cout << pq.top() << ", ";
        pq.pop();
    }

    std::cout << std::endl;
}

struct Pair {
    int x, y;

    bool operator<(const Pair &b) const {
        return this->x != b.x ? this->x < b.x : this->y < b.y;
    }

    friend ostream &operator<<(ostream &os, const Pair &p1) {
        os << "{" << p1.x << " " << p1.y << "}";
        return os;
    }
};

struct compare {
    bool operator()(Pair &a, Pair &b) {
        return a.x != b.x ? a.x < b.x : a.y < b.y;
    }
};

int main() {
    /*
     * CONSTRUCTORS
     * - Note: no pretty way to insert elements w initializer list
     * - need to specify all 3 parameters when creating custom comparator
     * - priority_queue retrieves MAX element
     */

    //1 - default constructor. can specify what container to use (vector/queue). vector is default
    priority_queue<int> pq1;
    priority_queue<int, deque<int>> pq;
    priority_queue<Pair> pq3a;
    pq3a.push({1, 2});

    //2 - custom comparators
    priority_queue<Pair, vector<Pair>, compare> pq3;
    //mostly the same, except the above one requires no-argument constructor
    priority_queue<Pair, vector<Pair>, compare> pq4{compare{}};
    pq3.push({1, 3});
    pq3.push({-1, 3});
    pq3.push({7, -1});
    print(pq3, "pq3");

    //3 - priority_queue(Compare compare, Container c)
    vector<int> v1{1, 2, 3};
    priority_queue<int, vector<int>, less<>> pq5a(less<>{}, v1);
    print(pq5a, "pq5a");

    //5 - copy constructor
    priority_queue<int, vector<int>, less<>> pq6{pq5a};

    //7 - priority_queue(InputIt first, InputIt second, Compare comp = Compare())
    vector<int> v2{1, 2, 3, 4};
    priority_queue<int> pq7(v2.begin(), v2.end());
    priority_queue<int, vector<int>, greater<>> pq8(v2.begin(), v2.end(), greater<>{});
    print(pq7, "pq7");
    print(pq8, "pq8");

    /*
     * INSERTION/DELETION
     * push(Value v)/emplace(constructor args)
     * void pop(int v)
     */
    priority_queue<int> pqi;
    pqi.push(-10);

    //pop
    pqi.pop();

    /*
     * SELECTION
     * top()
     */
    //front/back
    priority_queue<int> qs;
    qs.push(1);
    qs.push(2);
    print(qs, "2");

    /*
     * USEFUL METHODS
     * empty()
     * size()
     */
/*
     * SORTING
     * a) functor
     */

    //a) functor
    priority_queue<Pair, vector<Pair>, compare> pqv;
    pqv.push({1, 4});
    pqv.push({2, 5});
    pqv.push({-1, 4});
    print(pqv, "pqv");


    //b) lambda
    auto cmp = [](const Pair &a, const Pair &b) {
        return a.x != b.x ? a.x < b.x : a.y < b.y;
    };
    priority_queue<Pair, vector<Pair>, decltype(cmp)> pqv2(cmp);
    pqv2.push({1, 4});
    pqv2.push({2, 5});
    pqv2.push({-1, 4});
    print(pqv2, "pqv2");

    //c) using class operator<
    priority_queue<Pair> pqv3;
    pqv3.push({1, 4});
    pqv3.push({2, 5});
    pqv3.push({-1, 4});
    print(pqv3, "pqv3");

    /*
     * MISC
     *
     */
}
