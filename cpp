#include <iostream>
#include <vector>
#include <algorithm>
#include <limits>
#include <cstring> // for memset

using namespace std;

void dfs(int node, int parent, int depth, vector<vector<int>>& adjList, vector<int>& depths) {
    depths[node] = depth;
    for (int child : adjList[node]) {
        if (child != parent && depths[child] == -1) { // Ensure the node is unvisited
            dfs(child, node, depth + 1, adjList, depths);
        }
    }
}

int maxDepth(const vector<int>& depths) {
    int maxD = 0;
    for (int d : depths) {
        maxD = max(maxD, d);
    }
    return maxD;
}

vector<int> updateValues(int i, vector<int>& vals, const vector<int>& depths) {
    vector<int> newVals = vals; // Create a copy of vals
    for (int j = 0; j < vals.size(); j++) {
        if (depths[j] == i) {
            newVals[j] *= 2;
        } else if (depths[j] == i + 1) {
            newVals[j] /= 2;
        }
    }
    return newVals;
}

int main() {
    int n;
    cin >> n;

    // Get initial values of each node
    vector<int> vals(n);
    for (int i = 0; i < n; i++) {
        cin >> vals[i];
    }

    // Build adjacency list
    vector<vector<int>> adjList(n);
    for (int i = 0; i < n - 1; i++) {
        int u, v;
        cin >> u >> v;
        u--; v--; // Adjust indices to 0-based
        adjList[u].push_back(v);
        adjList[v].push_back(u);
    }

    // Calculate the depth of each node using DFS
    vector<int> depths(n, -1);
    dfs(0, -1, 1, adjList, depths);

    // Calculate differences after each operation
    vector<long> diffs;
    for (int i = 1; i < maxDepth(depths); i++) {
        vector<int> tempVals = vals; // Make a temporary copy of vals
        vector<int> newVals = updateValues(i, tempVals, depths);

        // Calculate the difference
        long minVal = numeric_limits<long>::max();
        long maxVal = numeric_limits<long>::min();
        for (int val : newVals) {
            minVal = min(minVal, static_cast<long>(val));
            maxVal = max(maxVal, static_cast<long>(val));
        }
        diffs.push_back(maxVal - minVal);
    }

    for (size_t i = 0; i < diffs.size(); i++) {
        cout << diffs[i];
        if (i != diffs.size() - 1) cout << " ";
    }

    return 0;
}
