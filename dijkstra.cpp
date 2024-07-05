/*
 * Dijkstra
 * Find shortest path from src to every other vertex in directed, non-negative graph
 * N = size of list
 * Time complexity : O((|V| + |E| log (|V|)
 * Space complexity : O(|V|)
 *
 * 1) Set all dist but src to infinity. Then, keep choosing shortest distance.
 */

/*
 * Tutorial: https://cp-algorithms.com/graph/dijkstra_sparse.html
 * Problem: https://cses.fi/problemset/task/1671
 */

#include <cstdio>
#include <cmath>
#include <set>
#include <climits>
#include <vector>
#include <iostream>
#include <filesystem>
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

const ll INF = 1e18;

/*
 * Finds shortest path from src to dest vertex given non-negative weights in a directed graph
 * Time Complexity: O((|V| + |E|)log|V|) (insert/remove vertices and update at most E times for logV/operation)
 * Space complexity: O(|V|) (stores only each vertex at most once in priority queue)
 */
void
dijkstra(int src, int dest, vector<vector<pair<int, int>>> &adj, vector<int> &p, vector<ll> &d) {
    int n = adj.size();
    p.assign(n, -1);
    d.assign(n, INF);
    set<pair<ll, int>> q; //to be processed

    d[src] = 0;
    q.insert({0, src});
    while (!q.empty()) {
        int v = q.begin()->second;
        q.erase(q.begin());
        for (auto [to, len]: adj[v]) {
            if (d[v] + len < d[to]) {
                q.erase({d[to], to});
                d[to] = d[v] + len;
                p[to] = v;
                q.insert({d[to], to});
            }
        }
    }
}