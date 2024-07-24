/*
 * Rabin Karp
 * Find number of occurrences of a pattern P string in a given text T
 *
 * O(|P| + |T|)
 * Space complexity : O(|T|)
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

template<typename T>
void print(string s, T a) {
    if (!s.empty())
        cout << s << ": ";
    cout << a << endl;
}

template<typename T>
void print(T a) {
    print("", a);
}

template<typename T>
void printV(string s, vector<T> &v) {
    if (!s.empty())
        cout << s << ": ";
    for (auto t: v) {
        cout << t << " ";
    }
    cout << endl;
}

template<typename T>
void printV(vector<T> &v) {
    printV("", v);
}

template<typename T>
void setGraph(vector<vector<int>> &adjacent, vector<T> &visited, int vertices, int edges) {
    adjacent.resize(vertices + 1);
    visited.resize(vertices + 1);
    for (int i = 0; i < edges; i++) {
        int p, q;
        cin >> p >> q;
        adjacent[p].pb(q);
        adjacent[q].pb(p);
    }
}

void io() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    filesystem::path cwd = filesystem::current_path();
    bool mysys = cwd.string() == "/Users/sahils/Desktop/cses.fi";
    if (mysys)
        freopen("/Users/sahils/Desktop/cses.fi/input.in", "r", stdin);
}

//returns number of times p(attern) matches t(ext)
//uses prefix hash
int rabin_karp(string &p, string &t) {
    int P = p.size(), T = t.size();
    if (P > T) return 0;

    int prime = 103;
    int MOD = 1e9 + 9;

    vector<ll> v(T);
    vector<ll> pow(T);
    vector<ll> prefixh(T + 1);
    pow[0] = 1;

    ll phash = 0;
    int ans = 0;

    for (int i = 1; i < T; i++)
        pow[i] = pow[i - 1] * prime % MOD;

    for (int i = 0; i < P; i++)
        phash = (phash + pow[i] * (p[i] - 'a' + 1)) % MOD;

    for (int i = 0; i < T; i++)
        prefixh[i + 1] = (prefixh[i] + (t[i] - 'a' + 1) * pow[i]) % MOD;

    for (int i = 0; i + P - 1 < T; i++) {
        ll subhash = (MOD + prefixh[i + P] - prefixh[i]) % MOD;
        if (subhash == phash * pow[i] % MOD)
            ans++;
    }
    return ans;
}

int main() {
    string t, p;
    cin >> t >> p;
    cout << rabin_karp(p, t);
}
