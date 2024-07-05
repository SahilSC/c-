/*
 * Bellman_Ford
 * Find shortest dist from src to dest given directed edges with any negative/positive weights
 * N = size of list
 * Time complexity : O(VE)
 * Space complexity : O(V)
 *
 * 1) Continuously relax edges |V| - 1 times. By induction, you can prove that if the shortest
 * path from the origin to a vertex is of length k, then after the kth relaxation, you will find it.
 * Assuming first loop is k = 1.
 */

/*
 * Tutorial: https://cp-algorithms.com/graph/bellman_ford.html
 * Problem: https://cses.fi/problemset/task/1197/
 */

#include <cstdio>
#include <vector>
#include <iostream>
#include <filesystem>
#include <algorithm>
#include <string>

#define all(a) a.begin(), a.end()
#define sz(a) static_cast<int>(a.size())
#define pb(a) push_back(a)
#define FOR(i, a) for(int i = 0; i < a; i++)
#define f first
#define s second

using namespace std;
using ll = long long;
using pi = pair<int, int>;

ll INF = 1e15;
struct Edge {
    int a, b;
    ll cost;
};

void bellman_ford(vector<Edge> &edges, vector<ll> &d, vector<int> &p) {
    int n = edges.size();
    int x;
    for (int i = 0; i < n; i++) {
        x = -1;
        for (Edge e: edges) {
            if (d[e.b] > d[e.a] + e.cost) {
                p[e.b] = e.a;
                d[e.b] = max(-INF, d[e.a] + e.cost);
                x = e.b;
            }
        }
    }
    if (x != -1) {
        cout << "NEGATIVE CYCLE" << endl;
        vector<int> path;
        for (int i = 0; i < n; i++, x = p[x]);
        for (int i = x; i != x || path.size() <= 1; i = p[i]) {
            path.pb(i);
        }
        if (path.back() != x)
            path.pb(x);
        reverse(all(path));
        for_each(all(path), [](int a) { cout << a << " "; });
    } else {
        cout << "NO NEGATIVE CYCLE" << endl;
    }
}

int main() {
    int n, m;
    cin >> n >> m;
    vector<Edge> adj(m);
    vector<int> p(n + 1);
    vector<ll> d(n + 1);
    for (int i = 0; i < m; i++) {
        int a, b, c;
        cin >> a >> b >> c;
        adj.push_back({a, b, c});
    }
    bellman_ford(adj, d, p);
}
