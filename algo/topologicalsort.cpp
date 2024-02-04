#include <vector>
#include <iostream>
#include <queue>
using namespace std;

int main(){
    /*
     * Topological sort.
     * 1) Create adjacency list
     * 2) Create degree list
     * 3) Initalize queue with sources
     * 4) BFS and process adj vertices to sources. If children have degree = 0, add to queue
     */
    ios::sync_with_stdio(false);
    cin.tie(0);
    int courses, prereqs;
    cin >> courses >> prereqs;
    vector<int> adj[courses + 1];
    vector<int> deg(courses + 1);
    for (int i = 0; i < prereqs; i++) {
        int parent, child;
        cin >> parent >> child;
        adj[parent].push_back(child);
        deg[child]++;
    }
    queue<int> source; //represents 0 degree vertices
    for (int i = 1; i <= courses; i++) {
        if (deg[i] == 0) {
            source.push(i);
        }
    }
    vector<int> sorted;
    //Remove all outgoing edges from sources and add current vertices to order
    while (!source.empty()) {
        int parent = source.front();
        source.pop();
        sorted.push_back(parent);
        for (int children: adj[parent]) {
            deg[children]--;
            if (deg[children] == 0) {
                source.push(children);
            }
        }
    }
    if (sorted.size() != courses) {
        cout << "IMPOSSIBLE";
    }
    else {
        for (int i = 0; i < sorted.size() - 1; i++) {
            cout << sorted[i] << " ";
        }
        cout << sorted[courses - 1];
    }
}