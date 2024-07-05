/*
 * Dijkstra
 * Find shortest path from src to every other vertex in directed, non-negative graph
 * N = size of list
 * Time complexity : O((|V| + |E| log (|V|)
 * Space complexity : O(|V|)
 *
 * 0) Initialize dp[i][i] = 0
 * 1) At every phase, update DP[i][j] = distance from i to j so that you only use nodes 0, 1, ..., k
 */

/*
 * Tutorial: https://cp-algorithms.com/graph/all-pair-shortest-path-floyd-warshall.html
 * Problem: https://cses.fi/problemset/task/1672
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

void floyd_warshall(vector<vector<pair<int, ll>>> &adj, vector<vector<ll>> &dp) {
    int n = adj.size();
    dp.assign(n, vector<ll>(n, INF));
    for (int i = 0; i < n; i++) dp[i][i] = 0;
    for (int v = 0; v < n; v++) {
        for (auto [to, len]: adj[v])
            dp[v][to] = min(dp[v][to], len);
    }
    for (int k = 0; k < n; k++) {
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                if (dp[i][k] != INF && dp[k][j] != INF)
                    //sets dp[i][j] == -1 if in negative cycle
                    dp[i][j] = max(-1LL, min(dp[i][j], dp[i][k] + dp[k][j]));
            }
        }
    }

    //All paths that have an arbitrarily small path are set to -INF
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            for (int t = 0; t < n; t++) {
                if (dp[i][t] < INF && dp[t][t] < 0 && dp[t][j] < INF)
                    dp[i][t] = -INF;
            }
        }
    }
}